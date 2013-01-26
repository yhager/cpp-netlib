// Copyright 2012 Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/include/http/client.hpp>

namespace http = network::http;
namespace net = network;

TEST(client_test, constructor) {
  // Here's the simplest way to construct a client.
  http::client instance;

  // The next way we're supporting is actually to construct an options object
  // that allows you to set options. This class replaces the Boost.Parameter
  // based approach to a much simpler model that scales better.
  http::client_options options;
  boost::asio::io_service io_service;
  options.io_service(&io_service).follow_redirects().cache_resolved()
      .add_openssl_certificate_path("/dev/zero")
      .add_openssl_verify_path("/dev/null");
  http::client instance2(options);
}

TEST(client_test, get_different_port) {
  http::request request_("http://www.boost.org:80/");
  http::client client_;
  http::response response_ = client_.get(request_);
  net::headers_wrapper::container_type const& headers_ = headers(response_);
  ASSERT_TRUE(!headers_.empty());
  ASSERT_GT(body(response_).size(), 0);
}

struct body_handler {
  explicit body_handler(std::string& body) : body(body) {}

  NETWORK_HTTP_BODY_CALLBACK(operator(), range, error) {
    body.append(boost::begin(range), boost::end(range));
  }

  std::string& body;
};

TEST(client_test, get_streaming_test) {
  http::client::request request("http://www.boost.org");
  http::client::response response;
  std::string body_string;
  std::string dummy_body;
  body_handler handler_instance(body_string);
  {
    http::client client_;
    ASSERT_NO_THROW(response = client_.get(request, handler_instance));
    net::headers_wrapper::container_type const& headers_ = headers(response);
    ASSERT_TRUE(!boost::empty(headers_));
    ASSERT_EQ(body(response).size(), 0u);
    std::string version_, status_message_;
    boost::uint16_t status_;
    version_ = version(response);
    status_ = status(response);
    status_message_ = status_message(response);
    ASSERT_EQ(version_.substr(0, 7), std::string("HTTP/1."));
    ASSERT_EQ(status_, 200u);
    ASSERT_EQ(status_message_, std::string("OK"));
    dummy_body = body(response);
  }
  ASSERT_TRUE(dummy_body == std::string());
}

TEST(client_test, http_get_test) {
  http::client::request request("http://www.google.com/");
  request << net::header("Connection", "close");
  http::client client_;
  http::client::response response;
  ASSERT_NO_THROW(response = client_.get(request));
  std::multimap<std::string, std::string> headers_ = net::headers(response);
  ASSERT_TRUE(!boost::empty(headers_));
  ASSERT_NO_THROW(ASSERT_TRUE(body(response).size() != 0));
  std::string version_, status_message_;
  response.get_version(version_);
  uint16_t status_;
  response.get_status(status_);
  response.get_status_message(status_message_);
  ASSERT_EQ(version_.substr(0, 7), "HTTP/1.");
  ASSERT_TRUE(status_ == 302u || status_ == 200u);
  ASSERT_TRUE(status_message_ == std::string("Found") ||
              status_message_ == std::string("OK"));
}

#ifdef NETWORK_ENABLE_HTTPS

TEST(client_test, https_get_test) {
  http::client::request request("https://www.google.com");
  request << net::header("Connection", "close");
  http::client client_;
  http::client::response response;
  ASSERT_NO_THROW(response = client_.get(request));
  std::multimap<std::string, std::string> headers_ = net::headers(response);
  ASSERT_TRUE(!boost::empty(headers_));
  ASSERT_NO_THROW(ASSERT_TRUE(body(response).size() != 0));
  std::string version_, status_message_;
  response.get_version(version_);
  uint16_t status_;
  response.get_status(status_);
  response.get_status_message(status_message_);
  ASSERT_EQ(version_.substr(0, 7), "HTTP/1.");
  ASSERT_TRUE(status_ == 302u || status_ == 200u);
  ASSERT_TRUE(status_message_ == std::string("Found") ||
              status_message_ == std::string("OK"));
}

#endif

TEST(client_test, http_get_test_timeout_1_0) {
  http::client::request request("http://localhost:12121/");
  http::client::response response_;
  http::client client_;
  boost::uint16_t port_ = port(request);
  std::string temp;
  ASSERT_EQ(12121, port_);
  ASSERT_THROW(response_ = client_.get(request); temp = body(response_);,
               std::exception);
}

