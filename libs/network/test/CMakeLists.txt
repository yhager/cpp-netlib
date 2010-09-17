#            Copyright (c) Dean Michael Berris 2010.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR})
find_package( Boost 1.41.0 COMPONENTS unit_test_framework system regex date_time thread filesystem )
find_package( OpenSSL )
include_directories(${OPENSSL_INCLUDE_DIR})
find_package( Threads )
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package( EXPAT )
find_package( LibXml2 )

if (Boost_FOUND)
    add_executable(cpp-netlib-hello_world hello_world.cpp)
    add_executable(cpp-netlib-http_1_0_test http_1_0_test.cpp)
    add_executable(cpp-netlib-http_1_1_test http_1_1_test.cpp)
    add_executable(cpp-netlib-http_localhost_tests http_localhost_tests.cpp)
    add_executable(cpp-netlib-https_localhost_tests https_localhost_tests.cpp)
    add_executable(cpp-netlib-message_test message_test.cpp)
    add_executable(cpp-netlib-http_message_test http_message_test.cpp)
    add_executable(cpp-netlib-message_transform_test message_transform_test.cpp)
    add_executable(cpp-netlib-url_test url_test.cpp)
    target_link_libraries(cpp-netlib-hello_world ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_DATE_TIME_LIBRARY} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} )
    target_link_libraries(cpp-netlib-http_1_0_test ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-http_1_1_test ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-http_message_test ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-message_test ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-message_transform_test ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-http_localhost_tests ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-https_localhost_tests ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})
    target_link_libraries(cpp-netlib-url_test ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

    set_target_properties(cpp-netlib-hello_world
                          cpp-netlib-http_1_0_test 
			  cpp-netlib-http_1_1_test 
			  cpp-netlib-message_test
			  cpp-netlib-http_message_test 
			  cpp-netlib-message_transform_test 
			  cpp-netlib-http_localhost_tests
			  cpp-netlib-https_localhost_tests
			  cpp-netlib-url_test 
			  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)

    add_test(cpp-netlib-hello_world python httplib_acceptance.py ../../../build/tests/cpp-netlib-hello_world ../../../build/tests/cpp-netlib-hello_world.passed)
    add_test(cpp-netlib-http_1_0_test ../../../build/tests/cpp-netlib-http_1_0_test)
    add_test(cpp-netlib-http_1_1_test ../../../build/tests/cpp-netlib-http_1_1_test)
    add_test(cpp-netlib-http_localhost_tests ../../../build/tests/cpp-netlib-http_localhost_tests)
    add_test(cpp-netlib-https_localhost_tests ../../../build/tests/cpp-netlib-https_localhost_tests)
    add_test(cpp-netlib-message_test ../../../build/tests/cpp-netlib-message_test)
    add_test(cpp-netlib-http_message_test ../../../build/tests/cpp-netlib-http_message_test)
    add_test(cpp-netlib-url_test ../../../build/tests/cpp-netlib-url_test)

    add_executable(cpp-netlib-xml_element_tests xml_wrappers/xml_element_tests.cpp)
    target_link_libraries(cpp-netlib-xml_element_tests ${Boost_LIBRARIES})
    add_test(cpp-netlib-xml_element_tests ../../../build/tests/cpp-netlib-xml_element_tests)

    set_target_properties(cpp-netlib-xml_element_tests
                          PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)

    add_executable(cpp-netlib-xmpp_message_tests xmpp/xmpp_message_tests.cpp)
    add_executable(cpp-netlib-xmpp_presence_tests xmpp/xmpp_presence_tests.cpp)
    add_executable(cpp-netlib-xmpp_iq_tests xmpp/xmpp_iq_tests.cpp)
    add_executable(cpp-netlib-xmpp_namespace_tests xmpp/xmpp_namespace_tests.cpp)
    target_link_libraries(cpp-netlib-xmpp_message_tests ${Boost_LIBRARIES})
    target_link_libraries(cpp-netlib-xmpp_presence_tests ${Boost_LIBRARIES})
    target_link_libraries(cpp-netlib-xmpp_iq_tests ${Boost_LIBRARIES})
    target_link_libraries(cpp-netlib-xmpp_namespace_tests ${Boost_LIBRARIES})
    set_target_properties(cpp-netlib-xmpp_message_tests
                          cpp-netlib-xmpp_presence_tests
                          cpp-netlib-xmpp_iq_tests
                          cpp-netlib-xmpp_namespace_tests
                          PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)
    add_test(cpp-netlib-xmpp_message_tests ../../../build/tests/cpp-netlib-xmpp_message_tests)
    add_test(cpp-netlib-xmpp_presence_tests ../../../build/tests/cpp-netlib-xmpp_presence_tests)
    add_test(cpp-netlib-xmpp_iq_tests ../../../build/tests/cpp-netlib-xmpp_iq_tests)
    add_test(cpp-netlib-xmpp_namespace_tests ../../../build/tests/cpp-netlib-xmpp_namespace_tests)

    if (EXPAT_FOUND)
      include_directories( ${EXPAT_INCLUDE_DIRS} )
      add_executable(cpp-netlib-expat_element_parser_tests xml_wrappers/expat_element_parser_tests.cpp)
      target_link_libraries(cpp-netlib-expat_element_parser_tests ${Boost_LIBRARIES} ${EXPAT_LIBRARIES})
      add_test(cpp-netlib-expat_element_parser_tests ../../../build/tests/cpp-netlib-expat_element_parser_tests)

      # add_executable(cpp-netlib-expat_stanza_parser_tests xml_wrappers/expat_stanza_parser_tests.cpp)
      # target_link_libraries(cpp-netlib-expat_stanza_parser_tests ${Boost_LIBRARIES} ${EXPAT_LIBRARIES})
      # add_test(cpp-netlib-expat_stanza_parser_tests ../../../build/tests/cpp-netlib-expat_stanza_parser_tests)
      
      add_executable(cpp-netlib-xmpp_stanza_tests xmpp/xmpp_stanza_tests.cpp)
      target_link_libraries(cpp-netlib-xmpp_stanza_tests ${Boost_LIBRARIES} ${EXPAT_LIBRARIES})
      add_test(cpp-netlib-xmpp_stanza_tests ../../../build/tests/cpp-netlib-xmpp_stanza_tests)

      add_executable(cpp-netlib-xmpp_client_tests xmpp/xmpp_client_tests.cpp)
      target_link_libraries(cpp-netlib-xmpp_client_tests ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXPAT_LIBRARIES})
      add_test(cpp-netlib-xmpp_client_tests ../../../build/tests/cpp-netlib-xmpp_client_tests)
      
      set_target_properties(cpp-netlib-expat_element_parser_tests
                            cpp-netlib-xmpp_stanza_tests
                            cpp-netlib-xmpp_client_tests
                            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)
    endif()

    if (LIBXML2_FOUND)
      include_directories( ${LIBXML2_INCLUDE_DIR} )
      add_executable(cpp-netlib-libxml2_element_parser_tests xml_wrappers/libxml2_element_parser_tests.cpp)
      target_link_libraries(cpp-netlib-libxml2_element_parser_tests ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})
      add_test(cpp-netlib-libxml2_element_parser_tests ../../../build/tests/cpp-netlib-libxml2_element_parser_tests)

      # add_executable(cpp-netlib-libxml2_stanza_parser_tests xml_wrappers/libxml2_stanza_parser_tests.cpp)
      # target_link_libraries(cpp-netlib-libxml2_stanza_parser_tests ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})
      # add_test(cpp-netlib-libxml2_stanza_parser_tests ../../../build/tests/cpp-netlib-libxml2_stanza_parser_tests)
      set_target_properties(cpp-netlib-libxml2_element_parser_tests
                            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)
    endif()

endif()
