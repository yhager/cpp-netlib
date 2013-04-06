// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <http/server/simple_sessions.hpp>
#include <cassert>

namespace network {
namespace http {

session& simple_sessions::lookup(boost::string_ref session_id) {
  std::string real_session_id =
      session_id.empty() ? std::to_string(next_session_id_.fetch_add(
          1, std::memory_order::memory_order_seq_cst)) :
      static_cast<std::string>(session_id);
  assert(real_session_id != "");
  std::lock_guard<std::mutex> lock_sessions(sessions_mutex_);
  std::pair<session_map_type::iterator, bool> result =
    sessions_.insert(make_pair(std::move(real_session_id), session()));
  if (result.second) {
    result.first->second.set("id", result.first->first);
    assert(result.first->second["id"] != "");
  }
  return result.first->second;
}

}  // namespace http
}  // namespace network
