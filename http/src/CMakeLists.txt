# Copyright (c) Glyn Matthews 2011, 2012, 2013.
# Copyright 2011 Dean Michael Berris (dberris@google.com)
# Copyright 2012 A. Joel Lamotte (mjklaim@gmail.com)
# Copyright 2011 Google, Inc.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


include_directories(
  ${CPP-NETLIB_SOURCE_DIR}/config/src
  ${CPP-NETLIB_SOURCE_DIR}/uri/src
  ${CPP-NETLIB_SOURCE_DIR}/message/src
  ${CPP-NETLIB_SOURCE_DIR}/logging/src
  ${CPP-NETLIB_SOURCE_DIR}/http/src
  ${CPP-NETLIB_SOURCE_DIR})

if (OPENSSL_FOUND)
include_directories(${OPENSSL_INCLUDE_DIR})
endif()

set(CPP-NETLIB_HTTP_MESSAGE_SRCS
  http/request.cpp
  http/response.cpp)

if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-message ${CPP-NETLIB_HTTP_MESSAGE_SRCS})
  add_dependencies(cppnetlib-http-message
    cppnetlib-message)
  target_link_libraries(cppnetlib-http-message
    ${Boost_LIBRARIES}
    cppnetlib-message)
endif()

set(CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS
    http/message/wrappers.cpp)

if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-message-wrappers ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS})
endif()

#set(CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS
#    http/client_connections.cpp
#    http/simple_connection_manager.cpp
#    http/simple_connection_factory.cpp
#    http/connection_delegate_factory.cpp
#    http/client_resolver_delegate.cpp
#    http/client_resolver_delegate_factory.cpp
#    http/client_connection_delegates.cpp
#    http/client_connection_factory.cpp
#    http/client_async_resolver.cpp
#    http/client_connection_normal.cpp)
#
#if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
#  add_library(cppnetlib-http-client-connections ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS})
#endif()

set(CPP-NETLIB_CONSTANTS_SRCS
    constants.cpp)

if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-constants ${CPP-NETLIB_CONSTANTS_SRCS})
endif()

# Server implementation files.
set(CPP-NETLIB_HTTP_SERVER_SRCS
  http/server/session.cpp
  http/server/simple_sessions.cpp
  http/server/dynamic_dispatcher.cpp)

if (NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-server ${CPP-NETLIB_HTTP_SERVER_SRCS})
endif()

#set(CPP-NETLIB_HTTP_CLIENT_SRCS
#    http/client.cpp)
#
#if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
#  add_library(cppnetlib-http-client ${CPP-NETLIB_HTTP_CLIENT_SRCS})
#  add_dependencies(cppnetlib-http-client
#    ${CPP-NETLIB_LOGGING_LIB}
#    cppnetlib-constants
#    cppnetlib-uri
#    cppnetlib-message
#    cppnetlib-message-wrappers
#    cppnetlib-message-directives
#    cppnetlib-http-message
#    cppnetlib-http-message-wrappers
#    cppnetlib-http-client-connections
#    )
#  target_link_libraries(cppnetlib-http-client
#    ${Boost_LIBRARIES}
#    ${CPP-NETLIB_LOGGING_LIB}
#    cppnetlib-constants
#    cppnetlib-uri
#    cppnetlib-message
#    cppnetlib-message-wrappers
#    cppnetlib-message-directives
#    cppnetlib-http-message
#    cppnetlib-http-message-wrappers
#    cppnetlib-http-client-connections
#    )
#endif()


set(CPP-NETLIB_HTTP_V2_CLIENT_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/http/v2/client/client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/http/v2/client/client_errors.cpp
  )
add_library(network-http-v2-client ${CPP-NETLIB_HTTP_V2_CLIENT_SRCS})
add_dependencies(network-http-v2-client
  network-uri
  )
target_link_libraries(network-http-v2-client
  ${Boost_LIBRARIES}
  network-uri
  )

# prepend current directory to make paths absolute
prependToElements( "${CMAKE_CURRENT_SOURCE_DIR}/"
    CPP-NETLIB_HTTP_MESSAGE_SRCS
    CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS
#    CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS
    CPP-NETLIB_CONSTANTS_SRCS
    CPP-NETLIB_HTTP_SERVER_SRCS
#    CPP-NETLIB_HTTP_CLIENT_SRCS
    CPP-NETLIB_HTTP_V2_CLIENT_SRCS )


# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_HTTP_MESSAGE_SRCS ${CPP-NETLIB_HTTP_MESSAGE_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS} PARENT_SCOPE)
#set(CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS} PARENT_SCOPE)
#set(CPP-NETLIB_HTTP_CLIENT_SRCS ${CPP-NETLIB_HTTP_CLIENT_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_HTTP_SERVER_SRCS ${CPP-NETLIB_HTTP_SERVER_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_CONSTANTS_SRCS ${CPP-NETLIB_CONSTANTS_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_HTTP_V2_CLIENT_SRCS ${CPP-NETLIB_HTTP_V2_CLIENT_SRCS} PARENT SCOPE)
