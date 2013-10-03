// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <http/server.hpp>

namespace http = network::http;
namespace net = network;

namespace {

TEST(server_test, default_constructor) {
  http::server server;
  (void) server;
}

}  // namespace 
