// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <http/server/default_connection_manager.hpp>

namespace http = network::http;

namespace  {

TEST(default_connection_manager_test, constructor_test) {
  http::default_connection_manager manager;
  (void)manager;
}

}  // namespace   
