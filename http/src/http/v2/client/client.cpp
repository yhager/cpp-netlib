// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/client/client.hpp>
#include <network/http/v2/method.hpp>
#include <network/http/v2/client/connection/async_resolver_delegate.hpp>
#include <thread>

namespace network {
  namespace http {
    namespace v2 {
      struct client::impl {

	explicit impl(client_options options);

	~impl() noexcept;

	std::future<response> do_request(method method_, request request_, request_options options);

	client_options options_;
	boost::asio::io_service io_service_;
	std::unique_ptr<boost::asio::io_service::work> sentinel_;
	std::thread lifetime_thread_;
	async_resolver_delegate resolver_;

      };

      client::impl::impl(client_options options)
	: options_(options)
	, sentinel_(new boost::asio::io_service::work(io_service_))
	, lifetime_thread_([=] () { io_service_.run(); })
	, resolver_(io_service_, options.cache_resolved()) {

      }

      client::impl::~impl() noexcept {
	sentinel_.reset();
	lifetime_thread_.join();
      }

      std::future<response> client::impl::do_request(method method_,
						     request request_,
						     request_options options) {
	request_.set_method(method_);

	std::future<response> response;
	auto endpoints = resolver_.resolve(request_.host(), request_.port());
	return response;
      }

      client::client(client_options options)
	: pimpl_(new impl(options)) {

      }

      client::~client() noexcept {
	delete pimpl_;
      }

      std::future<response> client::get(request request_, request_options options) {
	return pimpl_->do_request(method::GET, request_, options);
      }

      std::future<response> client::post(request request_, request_options options) {
	return pimpl_->do_request(method::POST, request_, options);
      }

      std::future<response> client::put(request request_, request_options options) {
	return pimpl_->do_request(method::PUT, request_, options);
      }

      std::future<response> client::delete_(request request_, request_options options) {
	return pimpl_->do_request(method::DELETE, request_, options);
      }

      std::future<response> client::head(request request_, request_options options) {
	return pimpl_->do_request(method::HEAD, request_, options);
      }

      std::future<response> client::options(request request_, request_options options) {
	return pimpl_->do_request(method::OPTIONS, request_, options);
      }
    } // namespace v2
  } // namespace network
} // namespace network
