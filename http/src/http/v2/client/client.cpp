// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <future>
#include <boost/asio/strand.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/algorithm/find_first_of.hpp>
#include <network/uri.hpp>
#include <network/config.hpp>
#include <network/http/v2/client/client.hpp>
#include <network/http/v2/method.hpp>
#include <network/http/v2/client/request.hpp>
#include <network/http/v2/client/response.hpp>
#include <network/http/v2/client/connection/tcp_resolver.hpp>
#include <network/http/v2/client/connection/normal_connection.hpp>

namespace network {
  namespace http {
    namespace v2 {
      using boost::asio::ip::tcp;

      struct client::impl {

	explicit impl(client_options options);

	~impl() noexcept;

        void connect(const boost::system::error_code &ec,
                     tcp::resolver::iterator endpoint_iterator);

        void write_request(const boost::system::error_code &ec);

        void read_response(const boost::system::error_code &ec,
                           std::size_t bytes_written);

        void read_response_status(const boost::system::error_code &ec,
                                  std::size_t bytes_written,
                                  std::shared_ptr<response> res);

        void read_response_headers(const boost::system::error_code &ec,
                                   std::size_t bytes_read,
                                   std::shared_ptr<response> res);

        void read_response_body(const boost::system::error_code &ec,
                                std::size_t bytes_read,
                                std::shared_ptr<response> res);

	std::future<response> do_request(method method_, request request_, request_options options);

	client_options options_;
	boost::asio::io_service io_service_;
        boost::asio::io_service::strand strand_;
        std::unique_ptr<client_connection::async_resolver> resolver_;
        std::unique_ptr<client_connection::async_connection> connection_;
	std::unique_ptr<boost::asio::io_service::work> sentinel_;
	std::thread lifetime_thread_;

        std::promise<response> response_promise_;
        boost::asio::streambuf request_;
        boost::asio::streambuf response_;

        // promise
        // future response

      };

      client::impl::impl(client_options options)
	: options_(options)
        , strand_(io_service_)
	, resolver_(new client_connection::tcp_resolver(io_service_, options.cache_resolved()))
        , connection_(new client_connection::normal_connection(io_service_))
	, sentinel_(new boost::asio::io_service::work(io_service_))
	, lifetime_thread_([=] () { io_service_.run(); }) {

      }

      client::impl::~impl() noexcept {
	sentinel_.reset();
	lifetime_thread_.join();
      }

      void client::impl::connect(const boost::system::error_code &ec,
                                 tcp::resolver::iterator endpoint_iterator) {
        if (ec) {
          if (endpoint_iterator == tcp::resolver::iterator()) {
            response_promise_.set_exception(std::make_exception_ptr(
                                              client_exception(client_error::host_not_found)));
            return;
          }

          response_promise_.set_exception(std::make_exception_ptr(
                                            std::system_error(ec.value(), std::system_category())));
          return;
        }

        tcp::endpoint endpoint(*endpoint_iterator);
        connection_->async_connect(endpoint,
                                     strand_.wrap(
                                     [=] (const boost::system::error_code &ec) {
                                       write_request(ec);
                                     }));
      }

      void client::impl::write_request(const boost::system::error_code &ec) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                              std::system_error(ec.value(), std::system_category())));
          return;
        }

        connection_->async_write(request_,
                                 strand_.wrap(
                                   [=] (const boost::system::error_code &ec,
                                        std::size_t bytes_written) {
                                     read_response(ec, bytes_written);
                                   }));
      }

      void client::impl::read_response(const boost::system::error_code &ec, std::size_t) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                            std::system_error(ec.value(), std::system_category())));
          return;
        }

        std::shared_ptr<response> res(new response{});
        connection_->async_read_until(response_,
                                      "\r\n",
                                      strand_.wrap(
                                        [=] (const boost::system::error_code &ec,
                                             std::size_t bytes_read) {
                                          read_response_status(ec, bytes_read, res);
                                        }));
      }

      void client::impl::read_response_status(const boost::system::error_code &ec,
                                              std::size_t,
                                              std::shared_ptr<response> res) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                            std::system_error(ec.value(), std::system_category())));
          return;
        }

        std::istream is(&response_);
        string_type version;
        is >> version;
        unsigned int status;
        is >> status;
        string_type message;
        std::getline(is, message);

        res->set_version(version);
        res->set_status(network::http::v2::status::code(status));
        res->set_status_message(boost::trim_copy(message));

        connection_->async_read_until(response_,
                                      "\r\n\r\n",
                                      strand_.wrap(
                                        [=] (const boost::system::error_code &ec,
                                             std::size_t bytes_read) {
                                          read_response_headers(ec, bytes_read, res);
                                        }));
      }

      void client::impl::read_response_headers(const boost::system::error_code &ec,
                                               std::size_t,
                                               std::shared_ptr<response> res) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                            std::system_error(ec.value(), std::system_category())));
          return;
        }

        // fill headers
        std::istream is(&response_);
        string_type header;
        while (std::getline(is, header) && (header != "\r")) {
          auto delim = boost::find_first_of(header, ":");
          string_type key(std::begin(header), delim);
          while (*++delim == ' ') { }
          string_type value(delim, std::end(header));
          res->add_header(key, value);
        }

        connection_->async_read(response_,
                                strand_.wrap(
                                  [=] (const boost::system::error_code &ec,
                                       std::size_t bytes_read) {
                                    read_response_body(ec, bytes_read, res);
                                  }));
      }

      namespace {
        std::istream &getline_with_newline(std::istream &is, std::string &line) {
          line.clear();

          std::istream::sentry se(is, true);
          std::streambuf *sb = is.rdbuf();

          while (true) {
            int c = sb->sbumpc();
            switch (c) {
            case EOF:
              if (line.empty()) {
                is.setstate(std::ios::eofbit);
              }
              return is;
            default:
              line += static_cast<char>(c);
            }
          }
        }
      } // namespace

      void client::impl::read_response_body(const boost::system::error_code &ec,
                                            std::size_t bytes_read,
                                            std::shared_ptr<response> res) {
        if (bytes_read == 0) {
          response_promise_.set_value(*res);
          return;
        }

        std::istream is(&response_);
        string_type line;
        while (!getline_with_newline(is, line).eof()) {
          res->append_body(line);
        }

        connection_->async_read(response_,
                                strand_.wrap(
                                  [=] (const boost::system::error_code &ec,
                                       std::size_t bytes_read) {
                                    read_response_body(ec, bytes_read, res);
                                  }));
      }

      std::future<client::response> client::impl::do_request(method met,
						     request req,
						     request_options options) {
        std::future<response> res = response_promise_.get_future();

	req.method(met);
        std::ostream request_stream(&request_);
        request_stream << req;
        if (!request_stream) {
          response_promise_.set_exception(std::make_exception_ptr(
                                            client_exception(client_error::invalid_request)));
        }

        // HTTP 1.1
        auto it = std::find_if(std::begin(req.headers()), std::end(req.headers()),
                               [] (const std::pair<uri::string_type, uri::string_type> &header) {
                                 return (boost::iequals(header.first, "host"));
                               });
        if (it == std::end(req.headers())) {
          // set error
          response_promise_.set_value(response());
          return res;
        }

        uri_builder builder;
        builder
          .authority(it->second)
          ;

        auto auth = builder.uri();
        auto host = auth.host()?
          uri::string_type(std::begin(*auth.host()), std::end(*auth.host())) : uri::string_type();
        auto port = auth.port<std::uint16_t>()? *auth.port<std::uint16_t>() : 80;

	resolver_->async_resolve(host, port,
                                 strand_.wrap(
                                   [=](const boost::system::error_code &ec,
                                       tcp::resolver::iterator endpoint_iterator) {
                                     connect(ec, endpoint_iterator);
                                   }));

	return res;
      }

      client::client(client_options options)
	: pimpl_(new impl(options)) {

      }

      client::~client() noexcept {
	delete pimpl_;
      }

      std::future<client::response> client::get(request req, request_options options) {
	return pimpl_->do_request(method::GET, req, options);
      }

      std::future<client::response> client::post(request req, request_options options) {
	return pimpl_->do_request(method::POST, req, options);
      }

      std::future<client::response> client::put(request req, request_options options) {
	return pimpl_->do_request(method::PUT, req, options);
      }

      std::future<client::response> client::delete_(request req, request_options options) {
	return pimpl_->do_request(method::DELETE, req, options);
      }

      std::future<client::response> client::head(request req, request_options options) {
	return pimpl_->do_request(method::HEAD, req, options);
      }

      std::future<client::response> client::options(request req, request_options options) {
	return pimpl_->do_request(method::OPTIONS, req, options);
      }
    } // namespace v2
  } // namespace http
} // namespace network
