// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <future>
#include <boost/algorithm/string/predicate.hpp>
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

        void read_response_status(const boost::system::error_code &ec,
                                  std::size_t bytes_written);

        void read_response_headers(const boost::system::error_code &ec,
                                   std::size_t bytes_read);

	std::future<response> do_request(method method_, request request_, request_options options);

	client_options options_;
	boost::asio::io_service io_service_;
        std::unique_ptr<async_resolver> resolver_;
        std::unique_ptr<async_connection> connection_;
	std::unique_ptr<boost::asio::io_service::work> sentinel_;
	std::thread lifetime_thread_;

        boost::asio::streambuf request_;
        std::promise<response> response_promise_;
        boost::asio::streambuf response_;

        // promise
        // future response

      };

      client::impl::impl(client_options options)
	: options_(options)
	, resolver_(new tcp_resolver(io_service_, options.cache_resolved()))
        , connection_(new normal_connection(io_service_))
	, sentinel_(new boost::asio::io_service::work(io_service_))
	, lifetime_thread_([=] () { io_service_.run(); }) {

      }

      client::impl::~impl() noexcept {
	sentinel_.reset();
	lifetime_thread_.join();
      }

      void client::impl::connect(const boost::system::error_code &ec,
                                 tcp::resolver::iterator endpoint_iterator) {
        tcp::endpoint endpoint(*endpoint_iterator);
        //connection_.async_connect(endpoint,
        //                          [=] (const boost::system::error_code &ec) {
        //                            if (ec) {
        //                              return;
        //                            }
        //
        //                            //response_promise_.set_value(v2::response());
        //                            //write_request(ec);
        //                          });
      }

      void client::impl::write_request(const boost::system::error_code &ec) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                              boost::system::system_error(ec)));
          return;
        }

        connection_->async_write(request_,
                                 [=] (const boost::system::error_code &ec,
                                      std::size_t bytes_written) {
                                   read_response_status(ec, bytes_written);
                                 });
      }

      void client::impl::read_response_status(const boost::system::error_code &ec,
                                              std::size_t) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                              boost::system::system_error(ec)));
          return;
        }

        connection_->async_read_until(response_,
                                      "\r\n",
                                      [=] (const boost::system::error_code &ec,
                                           std::size_t bytes_read) {
                                        // fill headers
                                        read_response_headers(ec, bytes_read);
                                      });
      }

      void client::impl::read_response_headers(const boost::system::error_code &ec,
                                               std::size_t) {
        if (ec) {
          response_promise_.set_exception(std::make_exception_ptr(
                                              boost::system::system_error(ec)));
          return;
        }

        connection_->async_read_until(response_,
                                      "\r\n\r\n",
                                      [=] (const boost::system::error_code &ec,
                                           std::size_t bytes_read) {
                                        // um...
                                      });
        }

      std::future<response> client::impl::do_request(method met,
						     request req,
						     request_options options) {
        std::future<response> res = response_promise_.get_future();

	req.method(met);
        std::ostream request_stream(&request_);
        request_stream << req;
        if (!request_stream) {
          // set error
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

	//resolver_->async_resolve(host, port,
        //                         [=](const boost::system::error_code &ec,
        //                             tcp::resolver::iterator endpoint_iterator) {
        //                           std::cout << "!!!" << std::endl;
        //                           if (ec) {
        //                             if (endpoint_iterator == tcp::resolver::iterator()) {
        //                               response_promise_.set_exception(
        //                                  std::make_exception_ptr(
        //                                      connection_error(client_error::host_not_found)));
        //                               return;
        //                             }
        //
        //                             std::cout << "!!!" << std::endl;
        //                             //response_promise_.set_exception(
        //                             //    std::make_exception_ptr(
        //                             //        boost::system::system_error(ec)));
        //                             return;
        //                           }
        //
        //                           connect(ec, endpoint_iterator);
        //                         });

        response_promise_.set_exception(std::make_exception_ptr(
                                            connection_error(client_error::host_not_found)));
	return res;
      }

      client::client(client_options options)
	: pimpl_(new impl(options)) {

      }

      client::~client() noexcept {
	delete pimpl_;
      }

      std::future<response> client::get(request req, request_options options) {
	return pimpl_->do_request(method::GET, req, options);
      }

      std::future<response> client::post(request req, request_options options) {
	return pimpl_->do_request(method::POST, req, options);
      }

      std::future<response> client::put(request req, request_options options) {
	return pimpl_->do_request(method::PUT, req, options);
      }

      std::future<response> client::delete_(request req, request_options options) {
	return pimpl_->do_request(method::DELETE, req, options);
      }

      std::future<response> client::head(request req, request_options options) {
	return pimpl_->do_request(method::HEAD, req, options);
      }

      std::future<response> client::options(request req, request_options options) {
	return pimpl_->do_request(method::OPTIONS, req, options);
      }
    } // namespace v2
  } // namespace network
} // namespace network
