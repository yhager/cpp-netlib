# Copyright (c) Glyn Matthews 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/concurrency/src)

set(CPP-NETLIB_CONCURRENCY_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-concurrency ${CPP-NETLIB_CONCURRENCY_SRCS})
endif()

# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_CONCURRENCY_SRCS ${CPP-NETLIB_CONCURRENCY_SRCS} PARENT_SCOPE)
