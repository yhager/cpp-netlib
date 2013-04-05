// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_SERVER_HPP_20130327
#define NETWORK_HTTP_SERVER_HPP_20130327

#include <memory>
#include <utility>
#include <functional>
#include <boost/utility/string_ref.hpp>

namespace network {
namespace http {

struct dynamic_dispatcher;
struct simple_sessions;
struct no_auth;
struct default_connection_manager;

template <class Handler = dynamic_dispatcher,
          class SessionManager = simple_sessions, class Authenticator = no_auth,
          class ConnectionManager = default_connection_manager>
struct basic_server {
  void register_handler(
      boost::string_ref spec,
      std::function<void(
          typename SessionManager::session &,
          std::shared_ptr<typename ConnectionManager::connection>)> handler);
};

typedef basic_server<> server;

}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_SERVER_HPP_20130327 */

