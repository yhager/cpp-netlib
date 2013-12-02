// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_ERROR_INC
#define NETWORK_ERROR_INC

/**
 * \file
 * \brief Contains a set of error classes and exceptions for
 *        network connections.
 */

#include <system_error>

namespace network {
  /**
   * \brief Gets the error category for network errors.
   */
  const std::error_category &network_category();
} // namespace network

#endif // NETWORK_ERROR_INC
