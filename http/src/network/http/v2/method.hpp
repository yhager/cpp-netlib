// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_METHOD_INC__
#define __NETWORK_HTTP_V2_METHOD_INC__

#include <string>
#include <ostream>

namespace network {
  namespace http {
    namespace v2 {
      enum class method { GET, POST, PUT, DELETE, HEAD, OPTIONS, TRACE, CONNECT, MERGE, PATCH, };

      inline
      std::ostream &operator << (std::ostream &os, method m) {
	  switch (m) {
	  case method::GET:
	    return os << "GET";
	  case method::POST:
	    return os << "POST";
	  case method::PUT:
	    return os << "PUT";
	  case method::DELETE:
	    return os << "DELETE";
	  case method::HEAD:
	    return os << "HEAD";
	  case method::OPTIONS:
	    return os << "OPTIONS";
	  case method::TRACE:
	    return os << "TRACE";
	  case method::CONNECT:
	    return os << "CONNECT";
	  case method::MERGE:
	    return os << "MERGE";
	  case method::PATCH:
	    return os << "PATCH";
	  }
	  return os;
      }
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __NETWORK_HTTP_V2_METHOD_INC__
