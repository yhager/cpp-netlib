// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_SERVER_SESSION_HPP_20130405
#define NETWORK_HTTP_SERVER_SESSION_HPP_20130405

#include <string>
#include <unordered_map>
#include <boost/utility/string_ref.hpp>

namespace network {
namespace http {

struct session {
  session() = default;
  session(const session&) = default;
  session(session&&) = default;
  session& operator=(const session&) = default;
  session& operator=(session&&) = default;

  void set(boost::string_ref key, boost::string_ref value, bool server_only = false);
  std::string get(boost::string_ref key, boost::string_ref default_value) const;
  std::string operator[](boost::string_ref key) const;
 private:
  typedef std::unordered_map<std::string, std::pair<bool, std::string>> session_map_type;
  session_map_type session_map_;
};

}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_SERVER_SESSION_HPP_20130405 */

