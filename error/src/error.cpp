// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/error.hpp>
#include <cstring>

namespace network {

  class network_category_impl : public std::error_category {

  public:

    network_category_impl() = default;

    virtual ~network_category_impl() noexcept;

    virtual const char *name() const noexcept;

    virtual std::string message(int ev) const;

  };

  network_category_impl::~network_category_impl() noexcept {

  }

  const char *network_category_impl::name() const noexcept {
    static const char name[] = "network_error";
    return name;
  }

  std::string network_category_impl::message(int ev) const {
    return std::strerror(ev);
  }

  const std::error_category &network_category() {
    static network_category_impl category;
    return category;
  }
} // namespace network
