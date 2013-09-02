// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/client/client.hpp>
#include <network/http/v2/method.hpp>
#include <network/http/v2/client/connection/async_resolver_delegate.hpp>

namespace network {
  namespace http {
    namespace v2 {
      client::client(client_options options)
	: options_(options) {

      }

      std::future<response> client::get(request request_, request_options options) {
	return do_request(method::GET, request_, options);
      }

      std::future<response> client::post(request request_, request_options options) {
	return do_request(method::POST, request_, options);
      }

      std::future<response> client::put(request request_, request_options options) {
	return do_request(method::PUT, request_, options);
      }

      std::future<response> client::delete_(request request_, request_options options) {
	return do_request(method::DELETE, request_, options);
      }

      std::future<response> client::head(request request_, request_options options) {
	return do_request(method::HEAD, request_, options);
      }

      std::future<response> client::options(request request_, request_options options) {
	return do_request(method::OPTIONS, request_, options);
      }

      std::future<response> client::do_request(method method_, request request_, request_options options) {
	request_.set_method(method_);

	boost::asio::io_service io_service;
	async_resolver_delegate resolver(io_service, async_resolver_delegate::cache_resolved());
	resolver.resolve(request_.host(), request_.port(),
			 [=] (const boost::system::error_code &ec, boost::iterator_range<async_resolver_delegate::resolver_iterator> resolvers) {
			   if (ec) {
			     return;
			   }

			   // make TCP connection
			 });
	io_service.run();

	return std::future<response>();
      }
    } // namespace v2
  } // namespace network
} // namespace network
