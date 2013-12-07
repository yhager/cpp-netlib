// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <thread>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/normal_connection.hpp"
#include "network/http/v2/client/request.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(normal_http_connection) {

  void SetUp() {
    io_service_.reset(new boost::asio::io_service{});
    resolver_.reset(new tcp::resolver(*io_service_));
    connection_.reset(new http::normal_connection(*io_service_));
  }

  void TearDown() {

  }

  void ConnectToBoost(boost::system::error_code &ec) {
    // Resolve the host.
    tcp::resolver::query query("www.boost.org", "80");
    auto it = resolver_->resolve(query, ec);
    Assert::That(ec, Equals(boost::system::error_code()));

    // Make sure that the connection is successful.
    tcp::endpoint endpoint(it->endpoint());
    connection_->async_connect(endpoint,
                               [&ec] (const boost::system::error_code &ec_) {
                                 ec = ec_;
                               });
  }

  void WriteToBoost(boost::system::error_code &ec,
                    std::size_t &bytes_written) {
    // Create an HTTP request.
    http::request request;
    request
      .method(http::method::GET)
      .path("/LICENSE_1_0.txt")
      .version("1.0")
      .append_header("Host", "www.boost.org")
      .append_header("User-Agent", "cpp-netlib normal_connection_test")
      .append_header("Connection", "close");

    // Write the HTTP request to the socket, sending it to the server.
    std::ostream request_stream(&request_);
    request_stream << request;
    connection_->async_write(request_,
                             [&bytes_written] (const boost::system::error_code &ec_,
                                               std::size_t bytes_written_) {
                               Assert::That(ec_, Equals(boost::system::error_code()));
                               bytes_written = bytes_written_;
                             });
  }

  void ReadFromBoost(boost::system::error_code &ec,
                     std::size_t &bytes_read) {
    // Read the HTTP response on the socket from the server.
    connection_->async_read_until(response_,
                                  "\r\n",
                                  [] (const boost::system::error_code &ec_, std::size_t) {
                                    Assert::That(ec_, Equals(boost::system::error_code()));
                                 });
  }

  It(connects_to_boost) {
    boost::system::error_code ec;

    ConnectToBoost(ec);

    io_service_->run_one();
    Assert::That(ec, Equals(boost::system::error_code()));
  }

  It(writes_to_boost) {
    boost::system::error_code ec;
    std::size_t bytes_written = 0;

    ConnectToBoost(ec);
    WriteToBoost(ec, bytes_written);

    io_service_->run();
    Assert::That(bytes_written, IsGreaterThan(0));
  }

  It(reads_from_boost) {
    boost::system::error_code ec;
    std::size_t bytes_written = 0, bytes_read = 0;

    ConnectToBoost(ec);
    WriteToBoost(ec, bytes_written);
    ReadFromBoost(ec, bytes_read);

    io_service_->run();
    std::istream is(&response_);
    std::string status;
    std::getline(is, status);
    // getline delimits the new line, but not the carriage return
    Assert::That(status, Equals("HTTP/1.1 200 OK\r"));
  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<tcp::resolver> resolver_;
  std::unique_ptr<http::async_connection> connection_;

  boost::asio::streambuf request_;
  boost::asio::streambuf response_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
