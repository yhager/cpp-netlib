// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include "network/http/v2/client/response.hpp"

namespace http = network::http::v2;

TEST(response_test, constructor) {
  ASSERT_NO_THROW(http::response());
}
