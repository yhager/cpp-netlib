// Copyright (c) Glyn Matthews 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/error.hpp>
#include <cerrno>

TEST(error_test, system_error) {
  std::system_error error(EPIPE, network::network_category());
  ASSERT_EQ(EPIPE, error.code().value());
}
