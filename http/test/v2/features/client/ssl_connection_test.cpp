// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <thread>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/ssl_connection_delegate.hpp"
#include "network/http/v2/client/request.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(https_connection) {

  void SetUp() {
    io_service_.reset(new boost::asio::io_service);
    resolver_.reset(new tcp::resolver(*io_service_));
    options_.reset(new http::client_options);
    connection_.reset(new http::ssl_connection_delegate(*io_service_, *options_));
    socket_.reset(new tcp::socket(*io_service_));
  }

  void TearDown() {
    socket_->close();
  }

  It(connects_to_localhost) {
    // Resolve the host.
    boost::system::error_code ec;
    tcp::resolver::query query("127.0.0.1", "80");
    auto it = resolver_->resolve(query, ec);
    Assert::That(ec, Equals(boost::system::error_code()));

    // Make sure that the connection is successful.
    tcp::endpoint endpoint(it->endpoint());
    connection_->async_connect(endpoint, "127.0.0.1",
                               [&ec] (const boost::system::error_code &ec_) {
                                 ec = ec_;
                               });
    io_service_->run_one();
    Assert::That(ec, Equals(boost::system::error_code()));
  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<tcp::resolver> resolver_;
  std::unique_ptr<http::client_options> options_;
  std::unique_ptr<http::connection_delegate> connection_;
  std::unique_ptr<tcp::socket> socket_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
