// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_SERVER_DYNAMIC_DISPATCHER_HPP_20130327
#define NETWORK_HTTP_SERVER_DYNAMIC_DISPATCHER_HPP_20130327

#include <http/server/session.hpp>
#include <http/server/connection.hpp>
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

namespace network {
namespace http {

struct dynamic_dispatcher{
  void register_handler(boost::string_ref pattern, std::function<void(session&, std::shared_ptr<connection>)> handler);
  void dispatch(boost::string_ref path, session& s, std::shared_ptr<connection> c);
  private:
  std::unordered_map<
      std::string,
      std::function<void(session &, std::shared_ptr<connection>)> > handlers_;
};

}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_SERVER_DYNAMIC_DISPATCHER_HPP_20130327 */

