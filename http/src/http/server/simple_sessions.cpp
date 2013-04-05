// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <http/server/simple_sessions.hpp>

namespace network {
namespace http {

session& simple_sessions::lookup(boost::string_ref session_id) {
  std::string real_session_id = session_id.empty() ?
    std::to_string(next_session_id_.fetch_add(1, std::memory_order::memory_order_seq_cst))
    : static_cast<std::string>(session_id);
  std::pair<session_map_type::iterator, bool> result =
    sessions_.insert(make_pair(std::move(real_session_id), session()));
  result.first->second.set("id", real_session_id);
  return result.first->second;
}

}  // namespace http
}  // namespace network
