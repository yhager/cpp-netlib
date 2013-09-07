// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC__
#define __NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC__

/**
 * \file
 * \brief Contains a set of error classes and exceptions for HTTP
 *        clients.
 */

#include <network/config.hpp>
#include <system_error>

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \enum client_error client_errors.hpp network/http/v2/client/client_errors.hpp
       * \brief An enumeration of all types of client error.
       */
      enum class client_error {
	// url
	invalid_url,

	// resolution
	resolver_error,

	// connection
	connection_timeout,
	https_not_supported,
      };

      /**
       * \brief Gets the error category for HTTP client errors.
       */
      const std::error_category &client_category();

      /**
       * \brief Makes an error code object from a client_error enum.
       */
      std::error_code make_error_code(client_error e);

      /**
       * \class invalid_url network/http/v2/client/client_errors.hpp
       * \brief An exception thrown if the URL provides is invalid.
       */
      class invalid_url : public std::system_error {

      public:

	/**
	 * \brief Constructor.
	 */
	explicit invalid_url();

	/**
	 * \brief Destructor.
	 */
	virtual ~invalid_url() noexcept;

      };

      /**
       * \class resolver_error network/http/v2/client/client_errors.hpp
       * \brief An exception thrown when there is a resolver error.
       */
      class resolver_error : std::system_error {

      public:

	/**
	 * \brief Constructor.
	 */
	explicit resolver_error();

	/**
	 * \brief Destructor.
	 */
	virtual ~resolver_error() noexcept;

      };

      /**
       * \class connection_error network/http/v2/client/client_errors.hpp
       * \brief An exception thrown when there is a connection error.
       */
      class connection_error : public std::system_error {

      public:

	/**
	 * \brief Constructor.
	 * \param The client_error code.
	 */
	explicit connection_error(client_error error);

	/**
	 * \brief Destructor.
	 */
	virtual ~connection_error() noexcept;

      };

    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC__
