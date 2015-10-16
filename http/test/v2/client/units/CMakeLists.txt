# Copyright (C) 2013 by Glyn Matthews
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

set(CPP-NETLIB_CLIENT_TESTS
  client_options_test
  client_test
  client_resolution_test
  request_options_test
  byte_source_test
  request_test
  response_test
  )

foreach(test ${CPP-NETLIB_CLIENT_TESTS})
  #if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  #  set_source_files_properties(${test}.cpp
  #    PROPERTIES COMPILE_FLAGS "-Wall")
  #endif()

  add_executable(cpp-netlib-http-v2-${test} ${test}.cpp)
  target_link_libraries(cpp-netlib-http-v2-${test}
    network-uri
    network-http-v2-client
    ${Boost_LIBRARIES}
    #${GMOCK_BOTH_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    )
  target_include_directories(cpp-netlib-http-v2-${test} PUBLIC ${Boost_INCLUDE_DIRS})
  set_target_properties(cpp-netlib-http-v2-${test}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
  add_test(cpp-netlib-http-v2-${test}
    ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-v2-${test})

endforeach(test)
