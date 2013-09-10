// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_DELEGATE_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_DELEGATE_INC__

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <network/http/v2/client/connection/connection_delegate.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class normal_connection_delegate : public connection_delegate {

        normal_connection_delegate(const normal_connection_delegate &) = delete;
        normal_connection_delegate &operator = (const normal_connection_delegate &) = delete;

      public:

        explicit normal_connection_delegate(boost::asio::io_service &io_service)
          : io_service_(io_service) {

        }

        virtual ~normal_connection_delegate() noexcept {

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

        virtual void async_read_some(const boost::asio::mutable_buffers_1 &read_buffer,
                                     read_callback callback) {
          socket_->async_read_some(read_buffer, callback);
        }

      private:

        boost::asio::io_service &io_service_;
        std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
        std::promise<std::pair<boost::system::error_code, std::size_t>> read_promise_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_DELEGATE_INC__
