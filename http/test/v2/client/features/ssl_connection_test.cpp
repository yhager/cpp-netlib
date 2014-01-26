// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <thread>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/ssl_connection.hpp"
#include "network/http/v2/client/request.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(https_connection) {

  void SetUp() {
    io_service_.reset(new boost::asio::io_service);
    resolver_.reset(new tcp::resolver(*io_service_));
    options_.reset(new http::client_options);
    connection_.reset(new http::client_connection::ssl_connection(*io_service_, *options_));
  }

  void TearDown() {

  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<tcp::resolver> resolver_;
  std::unique_ptr<http::client_options> options_;
  std::unique_ptr<http::client_connection::async_connection> connection_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
