// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_DELEGATE_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_DELEGATE_INC__

#include <functional>
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \class connection_delegate network/http/v2/client/connection/connection_delegate.hpp
       * \brief Manages a connection through a socket.
       */
      class connection_delegate {

        connection_delegate(const connection_delegate &) = delete;
        connection_delegate &operator = (const connection_delegate &) = delete;

      public:

        /**
         * \typedef connect_callback
         */
        typedef std::function<void (const boost::system::error_code &)> connect_callback;

        /**
         * \typedef write_callback
         */
        typedef std::function<void (const boost::system::error_code &, std::size_t)> write_callback;

        /**
         * \typedef read_callback
         */
        typedef std::function<void (const boost::system::error_code &, std::size_t)> read_callback;

        connection_delegate() = default;

        virtual ~connection_delegate() noexcept { }

        virtual void async_connect(boost::asio::ip::tcp::endpoint &endpoint,
                                   const std::string &host, connect_callback callback) = 0;

        virtual void async_write(boost::asio::streambuf &command_streambuf,
                                 write_callback callback) = 0;

        virtual void async_read_some(const boost::asio::mutable_buffers_1 &read_buffer,
                                     read_callback callback) = 0;

        virtual void cancel() = 0;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_DELEGATE_INC__
