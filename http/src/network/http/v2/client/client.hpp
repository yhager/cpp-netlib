// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__
#define __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__

#include <network/http/v2/client/request.hpp>
#include <network/http/v2/client/response.hpp>
#include <future>

namespace network {
  namespace http {
    namespace v2 {
      class client {

      public:

	client();
	client(client const &) = delete;
	client(client &&) = delete;

	std::future<response> get(const request &req);

	std::future<response> post(const request &req);

	std::future<response> put(const request &req);

	std::future<response> delete_(const request &req);

	std::future<response> head(const request &req);

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__
