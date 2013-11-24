// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <future>
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

      struct request_helper {

        request_helper(boost::asio::io_service &io_service) {

        }

        boost::asio::streambuf request_;
        std::promise<response> response_promise_;
        boost::asio::streambuf response_;

      };

      struct client::impl {

	explicit impl(client_options options);

	~impl() noexcept;

        void connect(const boost::system::error_code &ec);

        void write_request(const boost::system::error_code &ec, std::size_t bytes_written);

        void read_response_status(const boost::system::error_code &ec, std::size_t bytes_written);

        void read_response_headers(const boost::system::error_code &ec, std::size_t bytes_written);

	std::future<response> do_request(method method_, request request_, request_options options);

	client_options options_;
	boost::asio::io_service io_service_;
	std::unique_ptr<boost::asio::io_service::work> sentinel_;
	std::thread lifetime_thread_;
	async_resolver resolver_;
        normal_connection connection_;

        boost::asio::streambuf request_;
        std::promise<response> response_promise_;
        boost::asio::streambuf response_;

        // promise
        // future response

      };

      client::impl::impl(client_options options)
	: options_(options)
	, sentinel_(new boost::asio::io_service::work(io_service_))
	, lifetime_thread_([=] () { io_service_.run(); })
	, resolver_(io_service_, options.cache_resolved())
        , connection_(io_service_) {

      }

      client::impl::~impl() noexcept {
	sentinel_.reset();
	lifetime_thread_.join();
      }

      void client::impl::connect(const boost::system::error_code &ec) {
        if (ec) {
          return;
        }

        // endpoint!
        // host!

        //connection_.async_connect(endpoint, reques
      }

      void client::impl::write_request(const boost::system::error_code &ec,
                                       std::size_t bytes_written) {
        if (ec) {
          return;
        }

        // request!
      }

      void client::impl::read_response_status(const boost::system::error_code &ec,
                                              std::size_t bytes_read) {
        if (ec) {
          return;
        }

        // response
      }

      void client::impl::read_response_headers(const boost::system::error_code &ec,
                                               std::size_t bytes_read) {
        if (ec) {
          return;
        }

        // response
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
          return response;
        }

	//auto endpoints = resolver_.async_resolve(req.host(), req.port(),
        //                                         [=](const boost::system::error_code &ec) {
        //                                           if (ec) {
        //                                             // promise set error
        //                                             return;
        //                                           }
        //                                           this->connect(ec);
        //                                         });

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
