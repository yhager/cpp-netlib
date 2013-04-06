// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <http/server/simple_sessions.hpp>
#include <future>
#include <map>

namespace http = network::http;
namespace net = network;

namespace {

TEST(simple_sessions_test, constructor) {
  http::simple_sessions simple_sessions;
  (void) simple_sessions;
}

TEST(simple_sessions_test, lookup) {
  http::simple_sessions simple_sessions;
  http::session session = simple_sessions.lookup("sessionid");
  (void) session;
}

TEST(simple_sessions_test, update) {
  http::simple_sessions simple_sessions;
  {
    http::session session = simple_sessions.lookup("sessionid");
    session.set("user", "some-user");
    simple_sessions.update("sessionid", std::move(session));
  }
  {
    http::session session = simple_sessions.lookup("sessionid");
    EXPECT_EQ("some-user", session["user"]);
  }
}

TEST(simple_sessions_test, threaded_sessions) {
  http::simple_sessions simple_sessions;
  // Run many asynchronous functions (hoping that there will be many threads
  // created) so that we may be able to exercise the atomics and the
  // concurrency of the simple session manager.
  std::vector<std::future<std::string>> futures;
  constexpr size_t max_sessions = 1000;
  for (size_t counter = 0; counter < max_sessions; ++counter) {
    futures.emplace_back(std::async(std::launch::async, [&]() {
      return simple_sessions.lookup("")["id"];
    }));
  }
  std::set<std::string> ids;
  for (auto &future : futures)
    ids.emplace(future.get());
  EXPECT_EQ(max_sessions, ids.size());
}

}  // namespace
