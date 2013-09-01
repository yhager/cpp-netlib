// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/client/client_errors.hpp>

namespace network {
  namespace http {
    namespace v2 {
      client_category_impl::~client_category_impl() noexcept {

      }

      const char *client_category_impl::name() const noexcept {
	static const char name[] = "client_error";
	return name;
      }

      std::string client_category_impl::message(int ev) const {
	switch (client_error(ev)) {
	case client_error::invalid_scheme:
	  return "Requires HTTP or HTTPS scheme.";
	default:
	  break;
	}
	return "Unknown client error.";
      }

      const std::error_category &client_category() {
	static client_category_impl client_category;
	return client_category;
      }

      std::error_code make_error_code(client_error e) {
	return std::error_code(static_cast<int>(e), client_category());
      }

      invalid_scheme::invalid_scheme(const std::string &scheme)
	: std::system_error(make_error_code(client_error::invalid_scheme), "Invalid scheme: " + scheme) {

      }

      invalid_scheme::~invalid_scheme() noexcept {

      }

      resolver_error::resolver_error(const std::string &msg)
	: std::system_error(make_error_code(client_error::resolver_error), msg) {

      }

      resolver_error::~resolver_error() {

      }

      connection_timeout::connection_timeout()
	: std::system_error(make_error_code(client_error::connection_timeout)) {

      }

      connection_timeout::~connection_timeout() {

      }

    } // namespace v2
  } // namespace network
} // namespace network
