// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris (dberris@google.com).
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef __NETWORK_HTTP_V2_CLIENT_DEFAULT_CONNECTION_MANAGER_INC__
#define __NETWORK_HTTP_V2_CLIENT_DEFAULT_CONNECTION_MANAGER_INC__

#include "network/http/v2/client/connection/default_connection_manager.hpp"
#include <network/http/v2/client/connection/async_resolver_delegate.hpp>

namespace network {
  namespace http {
    namespace v2 {

      class request;
      class client_connection;
      class client_options;

      class default_connection_manager {

      public:

	default_connection_manager() = default;

	virtual default_connection_manager() noexcept;

	virtual connection_ptr get_connection(boost::asio::io_service &io_service,
					      const request &req,
					      const client_options &options);

	virtual void clear_resolved_cache();

	virtual void reset();

      private:

	async_resolver_delegate resolver_;

      };
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __NETWORK_HTTP_V2_CLIENT_DEFAULT_CONNECTION_MANAGER_INC__
