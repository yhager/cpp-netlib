// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__
#define __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__

#include <network/http/v2/client/client_options.hpp>
#include <network/http/v2/client/request.hpp>
#include <network/http/v2/client/request_options.hpp>
#include <network/http/v2/client/response.hpp>
#include <future>

namespace network {
  namespace http {
    namespace v2 {
      class client {

      public:

	typedef request::string_type string_type;

	explicit client(client_options options = client_options());
	client(client const &) = delete;
	client(client &&) = delete;

	std::future<response> get(request request_, request_options options = request_options());

	std::future<response> post(request request_, request_options options = request_options());

	std::future<response> put(request request_, request_options options = request_options());

	std::future<response> delete_(request request_, request_options options = request_options());

	std::future<response> head(request request_, request_options options = request_options());

	std::future<response> options(request request_, request_options options = request_options());

      private:

	std::future<response> do_request(method method_, request request_, request_options options);

	client_options options_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__
