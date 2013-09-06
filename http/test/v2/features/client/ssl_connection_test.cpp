// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <igloo/igloo.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/ssl_connection_delegate.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
