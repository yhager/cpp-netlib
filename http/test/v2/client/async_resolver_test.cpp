// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/async_resolver_delegate.hpp"
#include <iostream>

namespace http = network::http::v2;

TEST(async_resolver_test, resolve_localhost) {
  // server must be running on 127.0.0.1:80

  boost::asio::io_service io_service;
  http::async_resolver_delegate resolver(io_service, false);
  resolver.resolve("127.0.0.1", 80,
		   [] (const boost::system::error_code &ec,
		       const boost::iterator_range<http::async_resolver_delegate::resolver_iterator> &endpoints) {
		     for (auto endpoint : endpoints) {
		       std::cout << "Endpoint" << std::endl;
		     }
		   });

  io_service.run();
}
