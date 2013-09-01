// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_RESOLVER_DELEGATE_FACTORY_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_RESOLVER_DELEGATE_FACTORY_INC__

#include "network/http/v2/client/resolver_delegate.hpp"

namespace network {
  namespace http {
    namespace v2 {
      class resolver_delegate_factory {

	resolver_delegate_factory(const resolver_delegate_factory &) = delete;
	resolver_delegate_factory &operator = (const resolver_delegate_factory &) = delete;

      public:

	resolver_delegate_factory() = default;

	virtual ~resolver_delegate_factory() noexcept { }

	virtual std::shared_ptr<resolver_delegate> create(boost::asio::io_service &io_service,
							  bool cache_resolved) = 0;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_RESOLVER_DELEGATE_FACTORY_INC__
