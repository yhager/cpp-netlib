// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_DELEGATE_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_DELEGATE_INC__

#include <functional>
#include <string>
#include <future>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class connection_delegate {

	connection_delegate(const connection_delegate &) = delete;
	connection_delegate &operator = (const connection_delegate &) = delete;

      public:

	connection_delegate() = default;

	virtual ~connection_delegate() noexcept { }

	virtual std::future<boost::system::error_code>
	connect(boost::asio::ip::tcp::endpoint &endpoint,
		const std::string &host) = 0;

	virtual void write(boost::asio::streambuf &command_streambuf,
			   std::function<void (const boost::system::error_code &, size_t)> handler) = 0;

	virtual void read_some(const boost::asio::mutable_buffers_1 &read_buffer,
			       std::function<void (const boost::system::error_code &, size_t)> handler) = 0;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_CONNECTION_DELEGATE_INC__
