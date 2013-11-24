// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_INC__

#include <functional>
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>
#include <network/config.hpp>

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \class connection network/http/v2/client/connection/connection.hpp
       * \brief Manages a connection through a socket.
       */
      class connection {

        connection(const connection &) = delete;
        connection &operator = (const connection &) = delete;

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

        /**
         * \brief Constructor.
         */
        connection() = default;

        /**
         * \brief Destructor.
         */
        virtual ~connection() NETWORK_NOEXCEPT { }

        /**
         * \brief Asynchronously creates a connection to an endpoint.
         * \param endpoint The endpoint to which to connect.
         * \param host The host name.
         * \param callback A callback handler.
         */
        virtual void async_connect(boost::asio::ip::tcp::endpoint &endpoint,
                                   const std::string &host, connect_callback callback) = 0;

        /**
         * \brief Asynchronously writes data across the connection.
         * \param command_streambuf
         * \param callback A callback handler.
         */
        virtual void async_write(boost::asio::streambuf &command_streambuf,
                                 write_callback callback) = 0;

        /**
         * \brief Asynchronously reads some data from the connection.
         * \param read_buffer The buffer in which to read the network data.
         * \param callback A callback handler.
         */
        virtual void async_read_until(boost::asio::streambuf &command_streambuf,
                                      const std::string &delim,
                                      read_callback callback) = 0;


        /**
         * \brief Cancels an operation on a connection.
         */
        virtual void cancel() = 0;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_INC__
