# Copyright (c) Glyn Matthews 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/concurrency/src)

set(CPP-NETLIB_CONCURRENCY_SRCS thread_pool.cpp)
add_library(cppnetlib-concurrency ${CPP-NETLIB_CONCURRENCY_SRCS})
