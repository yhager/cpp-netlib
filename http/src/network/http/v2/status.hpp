// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_STATUS_INC__
#define __NETWORK_HTTP_V2_STATUS_INC__

/**
 * \file
 * \brief Constants for the HTTP error status.
 */

#include <string>
#include <unordered_map>
#include <functional>

namespace network {
  namespace http {
    namespace v2 {
      namespace status {
        enum class code {
          // informational
          CONTINUE = 100,
          SWITCH_PROTOCOLS = 101,

          // successful
          OK = 200,
          CREATED = 201,
          ACCEPTED = 202,
          NON_AUTH_INFO = 203,
          NO_CONTENT = 204,
          RESET_CONTENT = 205,
          PARTIAL_CONTENT = 206,

          // redirection
          MULTIPLE_CHOICES = 300,
          MOVED_PERMANENTLY = 301,
          FOUND = 302,
          SEE_OTHER = 303,
          NOT_MODIFIED = 304,
          USE_PROXY = 305,
          TEMPORARY_REDIRECT = 307,

          // client error
          BAD_REQUEST = 400,
          UNAUTHORIZED = 401,
          PAYMENT_REQUIRED = 402,
          FORBIDDEN = 403,
          NOT_FOUND = 404,
          METHOD_NOT_ALLOWED = 405,
          NOT_ACCEPTABLE = 406,
          PROXY_AUTH_REQUIRED = 407,
          REQUEST_TIMEOUT = 408,
          CONFLICT = 409,
          GONE = 410,
          LENGTH_REQUIRED = 411,
          PRECONDITION_FAILED = 412,
          REQUEST_ENTITY_TOO_LARGE = 413,
          REQUEST_URI_TOO_LONG = 414,
          UNSUPPORTED_MEDIA_TYPE = 415,
          REQUEST_RANGE_NOT_SATISFIABLE = 416,
          EXPECTATION_FAILED = 417,

          // server error
          INTERNAL_ERROR = 500,
          NOT_IMPLEMENTED = 501,
          BAD_GATEWAY = 502,
          SERVICE_UNAVAILABLE = 503,
          GATEWAY_TIMEOUT = 504,
          HTTP_VERSION_NOT_SUPPORTED = 505,
        };
      } // namespace status
    } // namespace v2
  } // namespace http
} // namespace network

namespace std {
  template <>
  struct hash<network::http::v2::status::code> {
    std::size_t operator()(network::http::v2::status::code status_code) const {
      hash<std::uint16_t> hasher;
      return hasher(static_cast<std::uint16_t>(status_code));
    }
  };
} // namespace std

namespace network {
  namespace http {
    namespace v2 {
      namespace status {
        inline
        std::string message(code status_code) {
          static std::unordered_map<code, std::string> status_messages{
            {code::CONTINUE, "Continue"},
            {code::SWITCH_PROTOCOLS, "Switching Protocols"},
            {code::OK, "OK"},
            {code::CREATED, "Created"},
            {code::ACCEPTED, "Accepted"},
            {code::NON_AUTH_INFO, "Non-Authoritative Information"},
            {code::NO_CONTENT, "No Content"},
            {code::RESET_CONTENT, "Reset Content"},
            {code::PARTIAL_CONTENT, "Partial Content"},
            {code::MULTIPLE_CHOICES, "Multiple Choices"},
            {code::MOVED_PERMANENTLY, "Moved Permanently"},
            {code::FOUND, "Found"},
            {code::SEE_OTHER, "See Other"},
            {code::NOT_MODIFIED, "Not Modified"},
            {code::USE_PROXY, "Use Proxy"},
            {code::TEMPORARY_REDIRECT, "Temporary Redirect"},
            {code::BAD_REQUEST, "Bad Request"},
            {code::UNAUTHORIZED, "Unauthorized"},
            {code::PAYMENT_REQUIRED, "Payment Required"},
            {code::FORBIDDEN, "Forbidden"},
            {code::NOT_FOUND, "Not Found"},
            {code::METHOD_NOT_ALLOWED, "Method Not Allowed"},
            {code::NOT_ACCEPTABLE, "Not Acceptable"},
            {code::PROXY_AUTH_REQUIRED, "Proxy Authentication Required"},
            {code::REQUEST_TIMEOUT, "Request Timeout"},
            {code::CONFLICT, "Conflict"},
            {code::GONE, "Gone"},
            {code::LENGTH_REQUIRED, "Length Required"},
            {code::PRECONDITION_FAILED, "Precondition Failed"},
            {code::REQUEST_ENTITY_TOO_LARGE, "Request Entity Too Large"},
            {code::REQUEST_URI_TOO_LONG, "Request Uri Too Long"},
            {code::UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type"},
            {code::REQUEST_RANGE_NOT_SATISFIABLE, "Request Range Not Satisfiable"},
            {code::EXPECTATION_FAILED, "Expectation Failed"},
            {code::INTERNAL_ERROR, "Internal Error"},
            {code::NOT_IMPLEMENTED, "Not Implemented"},
            {code::BAD_GATEWAY, "Bad Gateway"},
            {code::SERVICE_UNAVAILABLE, "Service Unavailable"},
            {code::GATEWAY_TIMEOUT, "Gateway Timeout"},
            {code::HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported"},
          };

          auto it = status_messages.find(status_code);
          if (it != status_messages.end()) {
            return it->second;
          }
          return "Invalid Status Code";
        }
      } // namespace status
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __NETWORK_HTTP_V2_CONSTANTS_INC__
