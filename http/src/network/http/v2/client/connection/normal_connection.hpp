// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_INC__

#include <boost/asio/write.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <network/http/v2/client/connection/connection.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class normal_connection : public connection {

        normal_connection(const normal_connection &) = delete;
        normal_connection &operator = (const normal_connection &) = delete;

      public:

        explicit normal_connection(boost::asio::io_service &io_service)
          : io_service_(io_service) {

        }

        virtual ~normal_connection() noexcept {

        }

        virtual void async_connect(boost::asio::ip::tcp::endpoint &endpoint,
                                   const std::string &host,
                                   connect_callback callback) {
          socket_.reset(new boost::asio::ip::tcp::socket(io_service_));
          socket_->async_connect(endpoint, callback);
        }

        virtual void async_write(boost::asio::streambuf &command_streambuf,
                                 write_callback callback) {
          boost::asio::async_write(*socket_, command_streambuf, callback);
        }

        virtual void async_read_until(boost::asio::streambuf &command_streambuf,
                                      const std::string &delim,
                                      read_callback callback) {
          boost::asio::async_read_until(*socket_, command_streambuf, delim, callback);
        }

        virtual void cancel() {
          socket_->cancel();
        }

      private:

        boost::asio::io_service &io_service_;
        std::unique_ptr<boost::asio::ip::tcp::socket> socket_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_INC__
