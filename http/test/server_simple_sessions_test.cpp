// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <http/server/simple_sessions.hpp>
#include <future>

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

TEST(simple_sessions_test, threaded_sessions) {
  http::simple_sessions simple_sessions;
  auto f0 = std::async([&]() {
    http::session &session = simple_sessions.lookup("");
    return session["id"];
  });
  auto f1 = std::async([&]() {
    http::session &session = simple_sessions.lookup("");
    return session["id"];
  });
  auto f2 = std::async([&]() {
    http::session &session = simple_sessions.lookup("");
    return session["id"];
  });
  std::string session0 = f0.get(),
    session1 = f1.get(),
    session2 = f2.get();
  EXPECT_NE(session0, session1);
  EXPECT_NE(session1, session2);
  EXPECT_NE(session0, session2);
}

}  // namespace
