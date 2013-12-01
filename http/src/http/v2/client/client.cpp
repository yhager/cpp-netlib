// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <future>
#include <network/uri.hpp>
#include <network/config.hpp>
#include <network/http/v2/client/client.hpp>
#include <network/http/v2/method.hpp>
#include <network/http/v2/client/request.hpp>
#include <network/http/v2/client/response.hpp>
#include <network/http/v2/client/connection/async_resolver.hpp>
#include <network/http/v2/client/connection/normal_connection.hpp>

namespace network {
  namespace http {
    namespace v2 {
      using boost::asio::ip::tcp;

      //struct request_helper {
      //
      //  request_helper() {
      //
      //  }
      //
      //  void connect(client::string_type host,
      //               const boost::system::error_code &ec,
      //               tcp::resolver::iterator endpoint_iterator);
      //
      //  void write_request(const boost::system::error_code &ec);
      //
      //  void read_response_status(const boost::system::error_code &ec,
      //                            std::size_t bytes_written);
      //
      //  void read_response_headers(const boost::system::error_code &ec,
      //                             std::size_t bytes_read);
      //
      //  client::string_type host_;
      //  boost::asio::streambuf request_;
      //  std::promise<response> response_promise_;
      //  boost::asio::streambuf response_;
      //
      //};

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
	async_resolver resolver_;
        normal_connection connection_;
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
	, resolver_(io_service_, options.cache_resolved())
        , connection_(io_service_)
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
        std::cout << "Resolved " << endpoint << std::endl;
        //connection_.async_connect(endpoint,
        //                          [=] (const boost::system::error_code &ec) {
        //                            if (ec) {
        //                              return;
        //                            }
        //
        //                            std::cout << "Oh." << std::endl;
        //                            //response_promise_.set_value(v2::response());
        //                            //write_request(ec);
        //                          });
      }

      void client::impl::write_request(const boost::system::error_code &ec) {
        if (ec) {
          return;
        }

        connection_.async_write(request_,
                                [=] (const boost::system::error_code &ec,
                                     std::size_t bytes_written) {
                                  read_response_status(ec, bytes_written);
                                });
      }

      void client::impl::read_response_status(const boost::system::error_code &ec,
                                              std::size_t) {
        if (ec) {
          return;
        }

        connection_.async_read_until(response_,
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
          return;
        }

        connection_.async_read_until(response_,
                                     "\r\n\r\n",
                                     [=] (const boost::system::error_code &ec,
                                          std::size_t bytes_read) {
                                       // um...
                                     });
        }

      std::future<response> client::impl::do_request(method met,
						     request req,
						     request_options options) {
        std::future<response> response = response_promise_.get_future();

	req.method(met);
        std::ostream request_stream(&request_);
        request_stream << req;
        if (!request_stream) {
          // set error
          //response_promise_.set_value(response());
          return response;
        }

        uri_builder builder;
        for (auto header : req.headers()) {
          // boost::iequals(header.first, "host")
          if ((header.first == "Host") || (header.first == "host")) {
            builder
              .authority(header.second)
              ;
            break;
          }
        }
        auto auth = builder.uri();
        auto host = auth.host()?
          uri::string_type(std::begin(*auth.host()), std::end(*auth.host())) : uri::string_type();
        auto port = auth.port<std::uint16_t>()? *auth.port<std::uint16_t>() : 80;

	resolver_.async_resolve(host, port,
                                [=](const boost::system::error_code &ec,
                                    tcp::resolver::iterator endpoint_iterator) {
                                  if (ec) {
                                    if (endpoint_iterator == tcp::resolver::iterator()) {
                                      return;
                                    }
                                    return;
                                  }

                                  connect(ec, endpoint_iterator);
                                });

	return response;
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
