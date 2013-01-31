
// Copyright 2007, 2012 Dean Michael Berris <dberris@google.com>
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/message.hpp>
#include <algorithm>

TEST(message_test, message_transform_toupper) {
  using namespace network;

  message msg;
  msg << source("me");
  std::string const& source_orig = source(msg);
  ASSERT_EQ(source_orig, "me");
  msg << transform(to_upper_, source_);
  std::string const& source_upper = source(msg);
  ASSERT_EQ(source_upper, "ME");
  msg << destination("you");
  std::string const& destination_orig = destination(msg);
  ASSERT_EQ(destination_orig, "you");
  msg << transform(to_upper_, destination_);
  std::string const& destination_upper = destination(msg);
  ASSERT_EQ(destination_upper, "YOU");
}

TEST(message_test, message_transform_tolower) {
  using namespace network;

  message msg;
  msg << source("ME");
  std::string const& source_orig = source(msg);
  ASSERT_EQ(source_orig, "ME");
  msg << transform(to_lower_, source_);
  std::string const& source_lower = source(msg);
  ASSERT_EQ(source_lower, "me");
  msg << destination("YOU");
  std::string const& destination_orig = destination(msg);
  ASSERT_EQ(destination_orig, "YOU");
  msg << transform(to_lower_, destination_);
  std::string const& destination_lower = destination(msg);
  ASSERT_EQ(destination_lower, "you");
}

