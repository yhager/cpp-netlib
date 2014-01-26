// Copyright (c) Glyn Matthews 2012, 2013.
// Copyright 2012 Dean Michael Berris <dberris@google.com>.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_CLIENT_INC
#define NETWORK_HTTP_CLIENT_INC

#include <network/http/v2/client.hpp>
#include <network/http/v2/method.hpp>
#include <network/http/v2/status.hpp>

namespace network {
  namespace http {
    using v2::client;
    using v2::client_options;
    using v2::request;
    using v2::request_options;
    using v2::response;
    using v2::method;
    namespace status = v2::status;
    using v2::client_error;
    using v2::invalid_url;
    using v2::client_exception;
  } // namespace http
} // namespace network


#endif  // NETWORK_HTTP_CLIENT_INC
