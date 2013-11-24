// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris <dberris@google.com>.
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_RESOLVER_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_RESOLVER_INC__

#include <stdexcept>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/exception/all.hpp>
#include <network/config.hpp>

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \class async_resolver network/http/v2/client/connection/async_resolver.hpp
       * \brief Resolves and maintains a cache of hosts.
       */
      class async_resolver {

        async_resolver(const async_resolver &) = delete;
        async_resolver &operator = (const async_resolver &) = delete;

      public:

        /**
         * \brief resolver
         */
        typedef boost::asio::ip::tcp::resolver resolver;

        /**
         * \brief resolver_iterator
         */
        typedef resolver::iterator resolver_iterator;

        /**
         * \brief Constructor.
         */
        async_resolver(boost::asio::io_service &service, bool cache_resolved = false)
          : resolver_(service)
          , resolver_strand_(new boost::asio::io_service::strand(service))
          , cache_resolved_(cache_resolved) {

        }

        /**
         * \brief Destructor.
         */
        ~async_resolver() NETWORK_NOEXCEPT {

        }

        /**
         * \brief Resolves a host asynchronously.
         * \param host The hostname to resolve.
         * \param port The port number.
         * \param callback A callback handler.
         */
        template <class Handler>
        void async_resolve(const std::string &host, std::uint16_t port, Handler &&handler) {
          if (cache_resolved_) {
            endpoint_cache::iterator it = endpoint_cache_.find(boost::to_lower_copy(host));
            if (it != endpoint_cache_.end()) {
              boost::system::error_code ec;
              handler(ec, it->second);
              return;
            }
          }


          resolver::query query(host, std::to_string(port));
          resolver_.async_resolve(query,
              resolver_strand_->wrap(
                  [&host, &handler, this](const boost::system::error_code &ec,
                                           resolver_iterator endpoint_iterator) {
                    if (ec) {
                      handler(ec, resolver_iterator());
                    }
                    else {
                      if (cache_resolved_) {
                        endpoint_cache_.insert(std::make_pair(host, endpoint_iterator));
                      }
                      handler(ec, endpoint_iterator);
                    }
                  }));
        }

        /**
         * \brief Clears the cache of already resolved endpoints.
         */
        void clear_resolved_cache() {
          endpoint_cache().swap(endpoint_cache_);
        }

      private:

        typedef boost::asio::io_service::strand strand;
        typedef std::unordered_map<std::string, resolver_iterator> endpoint_cache;

        resolver resolver_;
        std::unique_ptr<strand> resolver_strand_;
        bool cache_resolved_;
        endpoint_cache endpoint_cache_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_RESOLVER_INC__
