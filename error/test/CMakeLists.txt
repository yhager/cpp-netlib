# Copyright (c) Glyn Matthews 2013.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/error/src
  ${GTEST_INCLUDE_DIRS}
  ${CPP-NETLIB_SOURCE_DIR}
)

if (CPP-NETLIB_BUILD_TESTS)
  add_executable(cpp-netlib-error_test error_test.cpp)
  target_link_libraries(cpp-netlib-error_test
    ${link_cppnetlib_lib}
    network_error
    ${Boost_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
  set_target_properties(cpp-netlib-error_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
  add_test(cpp-netlib-error_test
    ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-error_test)
endif()
