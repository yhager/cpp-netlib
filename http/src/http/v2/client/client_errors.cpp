// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/config.hpp>
#include <network/http/v2/client/client_errors.hpp>

namespace network {
  namespace http {
    namespace v2 {

      class client_category_impl : public std::error_category {

      public:

	client_category_impl() = default;

	virtual ~client_category_impl() noexcept;

	virtual const char *name() const noexcept;

	virtual std::string message(int ev) const;

      };

      client_category_impl::~client_category_impl() noexcept {

      }

      const char *client_category_impl::name() const noexcept {
	static const char name[] = "client_error";
	return name;
      }

      std::string client_category_impl::message(int ev) const {
	switch (client_error(ev)) {
	case client_error::invalid_url:
	  return "Requires HTTP or HTTPS URL.";
	case client_error::resolver_error:
	  return "Unable to resolve host";
	case client_error::connection_timeout:
	  return "Connection timeout.";
	case client_error::https_not_supported:
	  return "HTTPS is not supported.";
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

      invalid_url::invalid_url()
	: std::system_error(make_error_code(client_error::invalid_url)) {

      }

      invalid_url::~invalid_url() noexcept {

      }

      resolver_error::resolver_error()
	: std::system_error(make_error_code(client_error::resolver_error)) {

      }

      resolver_error::~resolver_error() {

      }

      connection_error::connection_error(client_error error)
	: std::system_error(make_error_code(error)) {

      }

      connection_error::~connection_error() {

      }

    } // namespace v2
  } // namespace network
} // namespace network
