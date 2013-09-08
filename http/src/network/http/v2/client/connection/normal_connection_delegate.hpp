// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_DELEGATE_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_DELEGATE_INC__

#include "network/http/v2/client/connection/connection_delegate.hpp"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

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

	virtual std::future<boost::system::error_code>
	connect(boost::asio::ip::tcp::endpoint &endpoint,
		const std::string &host) {
	  socket_.reset(new boost::asio::ip::tcp::socket(io_service_));
//	  socket_->async_connect(endpoint,
//				 [this](const boost::system::error_code &ec) {
//				   std::cout << "oh" << std::endl;
//				   promise_.set_value(ec);
//				 });
	  boost::system::error_code ec;
	  socket_->connect(endpoint, ec);
	  promise_.set_value(ec);
	  return promise_.get_future();
	}

	virtual void write(boost::asio::streambuf &command_streambuf,
			   std::function<void (const boost::system::error_code &, size_t)> handler) {
	  boost::asio::async_write(*socket_, command_streambuf, handler);
	}

	virtual void read_some(const boost::asio::mutable_buffers_1 &read_buffer,
			       std::function<void (const boost::system::error_code &, size_t)> handler) {
	  socket_->async_read_some(read_buffer, handler);
	}

      private:

	boost::asio::io_service &io_service_;
	std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
	std::promise<boost::system::error_code> promise_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_DELEGATE_INC__
