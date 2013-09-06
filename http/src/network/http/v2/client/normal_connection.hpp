// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef __NETWORK_HTTP_V2_CLIENT_NORMAL_CONNECTION_INC__
#define __NETWORK_HTTP_V2_CLIENT_NORMAL_CONNECTION_INC__

#include <memory>
#include <functional>
#include <boost/utility/string_ref.hpp>

namespace network {
  namespace http {
    namespace v2 {

      class response;
      class request;
      class request_options;

      class normal_connection {

      public:

	typedef std::function<void (boost::string_ref, boost::system::error_code)> callback_type;

	normal_connection() = default;

	normal_connection(const normal_connection &) = delete;

	normal_connection &operator = (const normal_connection &) = delete;

	virtual ~normal_connection() noexcept;

	virtual response send_request(std::string method,
				      request req,
				      bool get_body,
				      callback_type callback,
				      request_options);

	virtual void reset();

      };
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __NETWORK_HTTP_V2_CLIENT_NORMAL_CONNECTION_INC__
