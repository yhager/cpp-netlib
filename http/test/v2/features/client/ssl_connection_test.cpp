// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <thread>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/ssl_connection_delegate.hpp"
#include "network/http/v2/client/request.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(https_connection) {

  void SetUp() {
    io_service_.reset(new boost::asio::io_service);
    resolver_.reset(new tcp::resolver(*io_service_));
    options_.reset(new http::client_options);
    connection_.reset(new http::ssl_connection_delegate(*io_service_, *options_));
    socket_.reset(new tcp::socket(*io_service_));
  }

  void TearDown() {
    socket_->close();
  }

  It(connects_to_localhost) {
    // Resolve the host.
    boost::system::error_code ec;
    tcp::resolver::query query("127.0.0.1", "80");
    auto it = resolver_->resolve(query, ec);
    Assert::That(ec, Equals(boost::system::error_code()));

    // Make sure that the connection is successful.
    tcp::endpoint endpoint(it->endpoint());
    connection_->async_connect(endpoint, "127.0.0.1",
                               [&ec] (const boost::system::error_code &ec_) {
                                 ec = ec_;
                               });
    io_service_->run_one();
    Assert::That(ec, Equals(boost::system::error_code()));
  }

  /*
  It(writes_to_localhost) {
    // Resolve the host.
    boost::system::error_code ec;
    tcp::resolver::query query("127.0.0.1", "80");
    auto it = resolver_->resolve(query, ec);
    Assert::That(ec, Equals(boost::system::error_code()));

    // Make sure that the connection is successful.
    tcp::endpoint endpoint(it->endpoint());
    connection_->async_connect(endpoint, "127.0.0.1",
                               [&ec] (const boost::system::error_code &ec_) {
                                 Assert::That(ec_, Equals(boost::system::error_code()));
                               });

    // Create an HTTPS request.
    http::request request{network::uri{"http://127.0.0.1/"}};
    request.set_method(http::method::GET);
    request.set_version("1.0");
    request.append_header("User-Agent", "ssl_connection_test");
    request.append_header("Connection", "close");

    // Write the HTTP request to the socket, sending it to the server.
    boost::asio::streambuf request_;
    std::ostream request_stream(&request_);
    request_stream << request;
    std::size_t bytes_written = 0;
    connection_->async_write(request_,
                             [&bytes_written] (const boost::system::error_code &ec_,
                                               std::size_t bytes_written_) {
                               Assert::That(ec_, Equals(boost::system::error_code()));
                               bytes_written = bytes_written_;
                             });
    io_service_->run();
    Assert::That(bytes_written, IsGreaterThan(0));
  }

  It(reads_from_localhost) {
    // Resolve the host.
    boost::system::error_code ec;
    tcp::resolver::query query("127.0.0.1", "80");
    auto it = resolver_->resolve(query, ec);
    Assert::That(ec, Equals(boost::system::error_code()));

    // Make sure that the connection is successful.
    tcp::endpoint endpoint(it->endpoint());
    connection_->async_connect(endpoint, "127.0.0.1",
                               [] (const boost::system::error_code &ec_) {
                                 Assert::That(ec_, Equals(boost::system::error_code()));
                               });

    // Create an HTTP request.
    http::request request{network::uri{"http://127.0.0.1/"}};
    request.set_method(http::method::GET);
    request.set_version("1.0");
    request.append_header("User-Agent", "ssl_connection_test");
    request.append_header("Connection", "close");

    // Write the HTTP request to the socket, sending it to the server.
    boost::asio::streambuf request_;
    std::ostream request_stream(&request_);
    request_stream << request;
    std::size_t bytes_written = 0;
    connection_->async_write(request_,
                             [&bytes_written] (const boost::system::error_code &ec_,
                                                    std::size_t bytes_written_) {
                               Assert::That(ec_, Equals(boost::system::error_code()));
                               bytes_written = bytes_written_;
                             });

    // Read the HTTP response on the socket from the server.
    char output[8192];
    std::memset(output, 0, sizeof(output));
    std::size_t bytes_read = 0;
    connection_->async_read_some(boost::asio::mutable_buffers_1(output, sizeof(output)),
                                 [&bytes_read] (const boost::system::error_code &ec_,
                                                std::size_t bytes_read_) {
                                   Assert::That(ec_, Equals(boost::system::error_code()));
                                   bytes_read = bytes_read_;
                                 });

    io_service_->run();
    Assert::That(bytes_read, IsGreaterThan(0));
  }
  */

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<tcp::resolver> resolver_;
  std::unique_ptr<http::client_options> options_;
  std::unique_ptr<http::connection_delegate> connection_;
  std::unique_ptr<tcp::socket> socket_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
