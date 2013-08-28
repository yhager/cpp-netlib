// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/constants.hpp>
#include <unordered_map>

std::string message(int status_code) {
  static std::unordered_map<int, std::string> status_messages{
    std::make_pair(100, "Continue"),
    std::make_pair(101, "Switching Protocols"),
    std::make_pair(200, "OK"),
    std::make_pair(201, "Created"),
    std::make_pair(202, "Accepted"),
    std::make_pair(203, "Non-Authoritative Information"),
    std::make_pair(204, "No Content"),
    std::make_pair(205, "Reset Content"),
    std::make_pair(206, "Partial Content"),
    std::make_pair(300, "Multiple Choices"),
    std::make_pair(301, "Moved Permanently"),
    std::make_pair(302, "Found"),
    std::make_pair(303, "See Other"),
    std::make_pair(304, "Not Modified"),
    std::make_pair(305, "Use Proxy"),
    std::make_pair(307, "Temporary Redirect"),
    std::make_pair(400, "Bad Request"),
    std::make_pair(401, "Unauthorized"),
    std::make_pair(402, "Payment Required"),
    std::make_pair(403, "Forbidden"),
    std::make_pair(404, "Not Found"),
    std::make_pair(405, "Method Not Allowed"),
    std::make_pair(406, "Not Acceptable"),
    std::make_pair(407, "Proxy Authentication Required"),
    std::make_pair(408, "Request Timeout"),
    std::make_pair(409, "Conflict"),
    std::make_pair(410, "Gone"),
    std::make_pair(411, "Length Required"),
    std::make_pair(412, "Precondition Failed"),
    std::make_pair(413, "Request Entity Too Large"),
    std::make_pair(414, "Request Uri Too Long"),
    std::make_pair(415, "Unsupported Media Type"),
    std::make_pair(416, "Request Range Not Satisfiable"),
    std::make_pair(417, "Expectation Failed"),
    std::make_pair(500, "Internal Error"),
    std::make_pair(501, "Not Implemented"),
    std::make_pair(502, "Bad Gateway"),
    std::make_pair(503, "Service Unavailable"),
    std::make_pair(504, "Gateway Timeout"),
    std::make_pair(505, "HTTP Version Not Supported"),
      };

  auto it = status_messages.find(status_code);
  if (it != status_messages.end()) {
    return it->second;
  }
  return "Invalid Status Code";
}
