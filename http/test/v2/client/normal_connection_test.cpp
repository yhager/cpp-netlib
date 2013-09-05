// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/normal_connection_delegate.hpp"
#include <iostream>

using boost::asio::ip::tcp;
namespace http = network::http::v2;

