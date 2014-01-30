# Copyright (c) Glyn Matthews 2013.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/error/src)

set(CPP-NETLIB_ERROR_SRCS
    error.cpp)

# prepend current directory to make paths absolute
prependToElements( "${CMAKE_CURRENT_SOURCE_DIR}/"
    CPP-NETLIB_ERROR_SRCS )

# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_ERROR_SRCS ${CPP-NETLIB_ERROR_SRCS} PARENT_SCOPE)
