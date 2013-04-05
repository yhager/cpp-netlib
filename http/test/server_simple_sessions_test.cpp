// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <http/server/simple_sessions.hpp>

namespace http = network::http;
namespace net = network;

namespace {

TEST(simple_sessions_test, constructor) {
  http::simple_sessions simple_sessions;
  (void) simple_sessions;
}

TEST(simple_sessions_test, lookup) {
  http::simple_sessions simple_sessions;
  http::session &session = simple_sessions.lookup("sessionid");
  (void) session;
}

TEST(simple_sessions_test, update) {
  http::simple_sessions simple_sessions;
  {
    http::session &session = simple_sessions.lookup("sessionid");
    session.set("user", "some-user");
  }
  {
    http::session &session = simple_sessions.lookup("sessionid");
    EXPECT_EQ("some-user", session["user"]);
  }
}

}  // namespace
