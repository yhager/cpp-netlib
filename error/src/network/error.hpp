// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_ERROR_INC
#define NETWORK_ERROR_INC

/**
 * \defgroup error Generic Error Handling
 *
 * This module contains a simple function that is used in generic
 * error handling inside cpp-netlib.
 *
 * \file
 * \brief Contains a set of error classes and exceptions for
 *        network connections.
 */

#include <system_error>

namespace network {
  /**
   * \ingroup error
   * \brief Gets the error category for network errors.
   *
   * e.g.
   *
   * \code
   * throw std::system_error(EPIPE, network::network_category());
   * \endcode
   */
  const std::error_category &network_category();

  /**
   * \ingroup error
   * \class network_exception network/error.hpp
   * \brief An exception thrown in the event of a network error.
   */
  class network_exception : public std::system_error {

  public:

    /**
     * \brief Constructor.
     * \param error_code The system error code.
     */
    explicit network_exception(int error_code)
      : std::system_error(error_code, network_category()) {

    }

    /**
     * \brief Destructor.
     */
    virtual ~network_exception() noexcept;

  };
} // namespace network

#endif // NETWORK_ERROR_INC
