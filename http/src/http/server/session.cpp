// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <http/server/session.hpp>

namespace network {
namespace http {

std::string session::get(boost::string_ref key, boost::string_ref value) const {
  session_map_type::const_iterator entry = session_map_.find(
                                               static_cast<std::string>(key));
  return entry == session_map_.end() ? static_cast<std::string>(value) :
         entry->second.second;
}

void session::set(boost::string_ref key, boost::string_ref value,
                  bool server_only) {
  auto new_value = make_pair(server_only, static_cast<std::string>(value));
  std::pair<session_map_type::iterator, bool> result =
      session_map_.insert(make_pair(static_cast<std::string>(key), new_value));
  if (!result.second)
    result.first->second = std::move(new_value);
}

std::string session::operator[](boost::string_ref key) const {
  return get(key, "");
}

}  // namespace http
}  // namespace network
