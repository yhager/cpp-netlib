// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/client/client.hpp>

namespace network {
  namespace http {
    namespace v2 {
      client::client() {

      }

      std::future<response> client::get(const request &req) {
	return std::future<response>();
      }

      std::future<response> client::post(const request &req) {
	return std::future<response>();
      }

      std::future<response> client::put(const request &req) {
	return std::future<response>();
      }

      std::future<response> client::delete_(const request &req) {
	return std::future<response>();
      }

      std::future<response> client::head(const request &req) {
	return std::future<response>();
      }
    } // namespace v2
  } // namespace network
} // namespace network
