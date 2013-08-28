// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/constants.hpp>

namespace http_constants = network::http::v2::constants;

// methods
TEST(constants_test, get)
{
  ASSERT_EQ("GET", http_constants::methods::get());
}

TEST(constants_test, post)
{
  ASSERT_EQ("POST", http_constants::methods::post());
}

TEST(constants_test, put)
{
  ASSERT_EQ("PUT", http_constants::methods::put());
}

TEST(constants_test, delete_)
{
  ASSERT_EQ("DELETE", http_constants::methods::delete_());
}

TEST(constants_test, head)
{
  ASSERT_EQ("HEAD", http_constants::methods::head());
}

TEST(constants_test, options)
{
  ASSERT_EQ("OPTIONS", http_constants::methods::options());
}

TEST(constants_test, trace)
{
  ASSERT_EQ("TRACE", http_constants::methods::trace());
}

TEST(constants_test, connect)
{
  ASSERT_EQ("CONNECT", http_constants::methods::connect());
}

TEST(constants_test, merge)
{
  ASSERT_EQ("MERGE", http_constants::methods::merge());
}

TEST(constants_test, patch)
{
  ASSERT_EQ("PATCH", http_constants::methods::patch());
}
