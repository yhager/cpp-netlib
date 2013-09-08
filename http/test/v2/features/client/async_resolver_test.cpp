// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include <boost/range/empty.hpp>
#include "network/http/v2/client/connection/async_resolver_delegate.hpp"

using namespace igloo;
namespace http = network::http::v2;

Describe(async_resolver) {

  void SetUp() {
    io_service_.reset(new boost::asio::io_service);
    resolver_.reset(new http::async_resolver_delegate(*io_service_));
  }

  It(resolves_localhost) {
    // An HTTP server must be running on 127.0.0.1:80
    // maybe execute a script

    auto endpoints = resolver_->resolve("127.0.0.1", 80);
    io_service_->run_one();
    auto result = endpoints.get();
    Assert::That(result.first, Equals(boost::system::error_code()));
    for (auto endpoint : result.second) {
      Assert::That(endpoint.endpoint().address().to_string(), Equals("127.0.0.1"));
      Assert::That(endpoint.endpoint().port(), Equals(80));
    }
  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<http::async_resolver_delegate> resolver_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
