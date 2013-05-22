// Copyright 2013 (c) Google, Inc.
// Copyright 2013 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <http/src/http/server/dynamic_dispatcher.hpp>

namespace network {
namespace http {

void dynamic_dispatcher::register_handler(boost::string_ref pattern, std::function<void(session&, std::shared_ptr<connection>)> handler) {
  auto inserted = handlers_.insert(make_pair(static_cast<std::string>(pattern),
                                             handler));
  if (!inserted.second)
    inserted.first->second = handler;
}

void dynamic_dispatcher::dispatch(boost::string_ref path, session& s, std::shared_ptr<connection> c) {
  auto entry = handlers_.find(static_cast<std::string>(path));
  if (entry != handlers_.end()) {
    entry->second(s, c);
  }
}

}  // namespace http
}  // namespace network
