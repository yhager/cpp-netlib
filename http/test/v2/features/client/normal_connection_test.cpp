// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/normal_connection_delegate.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(normal_http_connection) {

  //void SetUp() {
  //  io_service_.reset(new boost::asio::io_service);
  //  connection_.reset(new normal_http_connection(io_service));
  //
  //  // resolve endpoints
  //}

  It(connects_to_localhost) {
    //auto ec = connection_.connect(endpoint_, "127.0.0.1");
    // ec
  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<http::connection_delegate> connection_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
