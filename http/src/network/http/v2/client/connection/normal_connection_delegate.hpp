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
	  auto promise = std::make_shared<std::promise<boost::system::error_code>>();
	  auto result = promise->get_future();

	  socket_.reset(new boost::asio::ip::tcp::socket(io_service_));
	  socket_->async_connect(endpoint,
				 [=](const boost::system::error_code &ec) {
							promise->set_value(ec);
						      });
//	  boost::system::error_code ec;
//	  socket_->connect(endpoint, ec);
//	  promise->set_value(ec);
	  return std::move(result);
	}

	virtual std::future<std::pair<boost::system::error_code, std::size_t>>
	write(boost::asio::streambuf &command_streambuf) {
	  auto promise = std::make_shared<
	    std::promise<std::pair<boost::system::error_code, std::size_t>>>();
	  auto result = promise->get_future();

	  boost::asio::async_write(*socket_, command_streambuf,
				   [&promise] (const boost::system::error_code &ec, std::size_t size) {
				     promise->set_value(std::make_pair(ec, size));
				   });
	  return std::move(result);
	}

	virtual std::future<std::pair<boost::system::error_code, std::size_t>>
	read_some(const boost::asio::mutable_buffers_1 &read_buffer) {
	  auto promise = std::make_shared<
	    std::promise<std::pair<boost::system::error_code, std::size_t>>>();
	  auto result = promise->get_future();

//	  socket_->async_read_some(read_buffer,
//				   [this] (const boost::system::error_code &ec, std::size_t bytes_read) {
//				     read_promise_.set_value(std::make_pair(ec, bytes_read));
//				   });
	  boost::system::error_code ec;
	  auto bytes_read = boost::asio::read(*socket_, read_buffer, ec);
	  promise->set_value(std::make_pair(ec, bytes_read));
	  return std::move(result);
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
