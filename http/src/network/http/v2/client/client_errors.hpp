// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC__
#define __NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC__

#include <network/config.hpp>
#include <system_error>

namespace network {
  namespace http {
    namespace v2 {
      enum class client_error {
	// scheme
	invalid_scheme,
      };

      class client_category_impl : public std::error_category {

      public:

	client_category_impl() = default;

	virtual ~client_category_impl() noexcept;

	virtual const char *name() const noexcept;

	virtual std::string message(int ev) const;

      };

      const std::error_category &client_category();

      std::error_code make_error_code(client_error e);

      class invalid_scheme : public std::system_error {

      public:

	invalid_scheme(const std::string &scheme);

	virtual ~invalid_scheme() noexcept;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC__
