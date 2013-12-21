// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include "network/http/v2/client/connection/async_resolver.hpp"
#include "network/http/v2/client/connection/async_connection.hpp"
#include "network/http/v2/client.hpp"

namespace http = network::http::v2;
namespace http_cc = http::client_connection;

class mock_async_resolver : public http_cc::async_resolver {
public:

  mock_async_resolver() { }

  virtual ~mock_async_resolver() noexcept { }

  virtual void async_resolve(const std::string &, std::uint16_t,
                             resolve_callback callback) {
    // arbitrary error code, I just want this to fail
    boost::system::error_code ec(boost::asio::error::host_not_found,
                                 boost::asio::error::get_netdb_category());
    callback(ec, resolver_iterator());
  }

  virtual void clear_resolved_cache() { }

};

class fake_async_connection : public http_cc::async_connection {
public:

  fake_async_connection() { }

  virtual ~fake_async_connection() noexcept { }

  virtual void async_connect(const boost::asio::ip::tcp::endpoint &,
                             connect_callback) { }

  virtual void async_write(boost::asio::streambuf &,
                           write_callback) { }

  virtual void async_read_until(boost::asio::streambuf &,
                                const std::string &,
                                read_callback) { }

  virtual void async_read(boost::asio::streambuf &,
                          read_callback) { }

  virtual void cancel() { }

};

class client_resolution_test : public ::testing::Test {

protected:

  void SetUp() {
    resolver_.reset(new mock_async_resolver{});
    connection_.reset(new fake_async_connection{});
    client_.reset(new http::client{std::move(resolver_), std::move(connection_)});
  }

  void TearDown() {

  }

  std::unique_ptr<http_cc::async_resolver> resolver_;
  std::unique_ptr<http_cc::async_connection> connection_;
  std::unique_ptr<http::client> client_;

};

TEST_F(client_resolution_test, host_not_found) {
  http::client::request request;
  request
    .method(http::method::get)
    .path("/LICENSE_1_0.txt")
    .version("1.1")
    .append_header("Host", "www.boost.org")
    .append_header("User-Agent", "cpp-netlib client_test")
    .append_header("Connection", "close");
  auto future_response = client_->head(request);
  ASSERT_THROW(future_response.get(), std::system_error);
}
