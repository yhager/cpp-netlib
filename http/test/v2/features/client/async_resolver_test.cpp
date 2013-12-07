// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/tcp_resolver.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(async_resolver) {

  void SetUp() {
    // An HTTP server must be running on 127.0.0.1:80
    // maybe execute a script

    io_service_.reset(new boost::asio::io_service);
    resolver_.reset(new http::tcp_resolver(*io_service_));
  }

  It(resolves_localhost) {
    resolver_->async_resolve("127.0.0.1", 80,
                             [&] (const boost::system::error_code &ec,
                                  http::async_resolver::resolver_iterator endpoint_iterator) {
                               Assert::That(ec, Equals(boost::system::error_code()));
                               if (endpoint_iterator !=
                                   http::async_resolver::resolver_iterator()) {
                                 tcp::endpoint endpoint = *endpoint_iterator;
                                 Assert::That(endpoint.address().to_string(), Equals("127.0.0.1"));
                                 Assert::That(endpoint.port(), Equals(80));
                         }
                       });
    io_service_->run_one();
  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<http::async_resolver> resolver_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
