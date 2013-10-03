// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <http/server/dynamic_dispatcher.hpp>
#include <http/server/session.hpp>
#include <http/server/connection.hpp>

namespace http = ::network::http;

TEST(server_dynamic_dispatcher, constructor) {
  http::dynamic_dispatcher dispatcher;
  (void)dispatcher;
}

TEST(server_dynamic_dispatcher, register_handler) {
  http::dynamic_dispatcher dispatcher;
  bool called = false;
  dispatcher.register_handler("/", [&called](http::session& s, std::shared_ptr<http::connection> c){ called = true; });
  http::session s;
  std::shared_ptr<http::connection> c;
  dispatcher.dispatch("/", s, c);
  EXPECT_EQ(true, called);
}
