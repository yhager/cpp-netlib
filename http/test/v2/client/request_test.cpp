// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/client/request.hpp>

namespace http = network::http::v2;


TEST(request_test, constructor_url) {
  ASSERT_NO_THROW(http::request{network::uri{"http://www.example.com/"}});
}

TEST(request_test, constructor_https_url) {
  ASSERT_NO_THROW(http::request{network::uri{"https://www.example.com/"}});
}

TEST(request_test, constructor_invalid_url) {
  ASSERT_THROW(http::request{network::uri{"mailto:john.doe@example.com"}},
	       http::invalid_scheme);
}

TEST(request_test, constructor_empty_uri) {
  ASSERT_THROW(http::request{network::uri{}},
	       http::invalid_scheme);
}

TEST(request_test, constructor_uri_no_scheme) {
  network::uri_builder builder;
  builder.host("www.example.com").path("/");
  ASSERT_THROW(http::request{builder.uri()},
	       http::invalid_scheme);
}

TEST(request_test, stream) {
  http::request instance{network::uri{"http://www.example.com/"}};
  instance.set_version("1.1");
  instance.set_method("GET");
  instance.append_header("Connection", "close");
  instance.append_header("User-Agent", "request_test");
  std::ostringstream oss;
  oss << instance;
  ASSERT_EQ("GET / HTTP/1.1\r\n"
	    "Host: http://www.example.com\r\n"
	    "Connection: close\r\n"
	    "User-Agent: request_test\r\n\r\n", oss.str());
}

TEST(request_test, stream_2) {
  http::request instance{network::uri{"http://www.example.com/path/to/resource/index.html"}};
  instance.set_version("1.1");
  instance.set_method("GET");
  instance.append_header("Connection", "close");
  instance.append_header("User-Agent", "request_test");
  std::ostringstream oss;
  oss << instance;
  ASSERT_EQ("GET /path/to/resource/index.html HTTP/1.1\r\n"
	    "Host: http://www.example.com\r\n"
	    "Connection: close\r\n"
	    "User-Agent: request_test\r\n", oss.str());
}

TEST(request_test, read_headers) {
  http::request instance{network::uri{"http://www.example.com/path/to/resource/index.html"}};
  instance.set_version("1.1");
  instance.set_method("GET");
  instance.append_header("Connection", "close");
  instance.append_header("User-Agent", "request_test");

  auto headers = instance.headers();
  auto headers_it = std::begin(headers);
  ASSERT_EQ("Connection", headers_it->first);
  ASSERT_EQ("close", headers_it->second);
  ++headers_it;
  ASSERT_EQ("User-Agent", headers_it->first);
  ASSERT_EQ("request_test", headers_it->second);
}

TEST(request_test, clear_headers) {
  http::request instance{network::uri{"http://www.example.com/path/to/resource/index.html"}};
  instance.set_version("1.1");
  instance.set_method("GET");
  instance.append_header("Connection", "close");
  instance.append_header("User-Agent", "request_test");
  instance.clear_headers();
  auto headers = instance.headers();
  ASSERT_TRUE(std::begin(headers) == std::end(headers));
}

TEST(request_test, remove_headers) {
  http::request instance{network::uri{"http://www.example.com/path/to/resource/index.html"}};
  instance.set_version("1.1");
  instance.set_method("GET");
  instance.append_header("Connection", "close");
  instance.append_header("User-Agent", "request_test");
  instance.remove_header("User-Agent");

  auto headers = instance.headers();
  auto headers_it = std::begin(headers);

  ASSERT_EQ("Connection", headers_it->first);
  ASSERT_EQ("close", headers_it->second);
  ++headers_it;
  ASSERT_TRUE(headers_it == std::end(headers));
}

TEST(request_test, remove_duplicate_headers) {
  http::request instance{network::uri{"http://www.example.com/path/to/resource/index.html"}};
  instance.set_version("1.1");
  instance.set_method("GET");
  instance.append_header("Connection", "close");
  instance.append_header("User-Agent", "request_test");
  instance.append_header("User-Agent", "request_test_2");
  instance.remove_header("User-Agent");

  auto headers = instance.headers();
  auto headers_it = std::begin(headers);

  ASSERT_EQ("Connection", headers_it->first);
  ASSERT_EQ("close", headers_it->second);
  ++headers_it;
  ASSERT_TRUE(headers_it == std::end(headers));
}
