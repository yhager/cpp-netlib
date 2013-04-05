// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_SERVER_SIMPLE_SESSIONS_HPP_20130327
#define NETWORK_HTTP_SERVER_SIMPLE_SESSIONS_HPP_20130327

#include <unordered_map>
#include <http/server/session.hpp>
#include <boost/utility/string_ref.hpp>
#include <atomic>

namespace network {
namespace http {

struct simple_sessions {
  simple_sessions() = default;
  simple_sessions(const simple_sessions&) = delete;
  simple_sessions(simple_sessions&&) = delete;
  simple_sessions& operator=(const simple_sessions&) = delete;
  simple_sessions& operator=(simple_sessions&) = delete;

  session &lookup(boost::string_ref session_id);
 private:
  typedef std::unordered_map<std::string, session> session_map_type;
  session_map_type sessions_;
  std::atomic_uint_fast64_t next_session_id_;
};

}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_SERVER_SIMPLE_SESSIONS_HPP_20130327 */

