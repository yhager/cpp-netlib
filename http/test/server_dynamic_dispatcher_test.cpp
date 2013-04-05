// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/server/dynamic_dispatcher.hpp>

namespace http = ::network::http;

TEST(server_dynamic_dispatcher, constructor) {
  http::dynamic_dispatcher dispatcher;
  (void)dispatcher;
}
