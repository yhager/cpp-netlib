// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/client/client.hpp>

namespace network {
  namespace http {
    namespace v2 {
      client::client(client_options options)
	: options_(options) {

      }

      std::future<response> client::get(request req, request_options options) {
	return do_request("GET", req, options);
      }

      std::future<response> client::post(request req, request_options options) {
	return do_request("POST", req, options);
      }

      std::future<response> client::put(request req, request_options options) {
	return do_request("PUT", req, options);
      }

      std::future<response> client::delete_(request req, request_options options) {
	return do_request("DELETE", req, options);
      }

      std::future<response> client::head(request req, request_options options) {
	return do_request("HEAD", req, options);
      }

      std::future<response> client::options(request req, request_options options) {
	return do_request("OPTIONS", req, options);
      }

      std::future<response> client::do_request(string_type method, request req, request_options options) {
	return std::future<response>();
      }
    } // namespace v2
  } // namespace network
} // namespace network
