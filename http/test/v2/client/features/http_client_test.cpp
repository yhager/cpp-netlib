// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <igloo/igloo_alt.h>
#include "network/http/v2/client.hpp"

using namespace igloo;
namespace http = network::http::v2;

Describe(http_client) {

  void SetUp() {
    client_.reset(new http::client{});
  }

  void TearDown() {

  }

  It(gets_a_header_response) {
    http::client::request request{network::uri{"http://www.boost.org/"}};
    request
      .method(http::method::get)
      .path("/LICENSE_1_0.txt")
      .version("1.1")
      .append_header("Host", "www.boost.org")
      .append_header("User-Agent", "cpp-netlib client_test")
      .append_header("Connection", "close");
    auto future_response = client_->head(request);
    auto response = future_response.get();

    Assert::That(response.version(), Equals("HTTP/1.1"));
    Assert::That(response.status(), Equals(http::status::code::ok));
    Assert::That(response.status_message(), Equals("OK"));

    auto headers = response.headers();
    Assert::That(std::begin(headers)->first, Equals("Date"));
  }

  std::unique_ptr<http::client> client_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
