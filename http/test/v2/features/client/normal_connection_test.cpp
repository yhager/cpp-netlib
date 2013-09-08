// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <thread>
#include <igloo/igloo_alt.h>
#include <boost/asio.hpp>
#include "network/http/v2/client/connection/async_resolver_delegate.hpp"
#include "network/http/v2/client/connection/normal_connection_delegate.hpp"
#include "network/http/v2/client/request.hpp"

using namespace igloo;
using boost::asio::ip::tcp;
namespace http = network::http::v2;

Describe(normal_http_connection) {

  void SetUp() {
    io_service_.reset(new boost::asio::io_service);
    resolver_.reset(new http::async_resolver_delegate(*io_service_));
    connection_.reset(new http::normal_connection_delegate(*io_service_));

    // resolve endpoints
    auto endpoints = resolver_->resolve("127.0.0.1", 80);
    io_service_->run_one();
    endpoints_ = endpoints.get();
  }

  void TearDown() {

  }

  It(connects_to_localhost) {
    auto it = std::begin(endpoints_.second);
    tcp::endpoint endpoint(it->endpoint().address(), 80);
    auto connected = connection_->connect(endpoint, "127.0.0.1");
    io_service_->run_one();
    auto connected_ = connected.get();
    Assert::That(connected_, Equals(boost::system::error_code()));
  }

  It(writes_to_localhost) {
    auto it = std::begin(endpoints_.second);
    tcp::endpoint endpoint(it->endpoint().address(), 80);
    auto connected = connection_->connect(endpoint, "127.0.0.1");
    io_service_->run_one();
    auto connected_ = connected.get();
    Assert::That(connected_, Equals(boost::system::error_code()));

    http::request request{network::uri{"http://127.0.0.1/"}};
    request.set_method(http::method::GET);
    request.set_version("1.0");
    request.append_header("User-Agent", "normal_connection_test");
    request.append_header("Connection", "close");

    boost::asio::streambuf request_;
    std::ostream request_stream(&request_);
    request_stream << request;
    auto written = connection_->write(request_);
    io_service_->run_one();
    auto written_ = written.get();
    Assert::That(written_.first, Equals(boost::system::error_code()));
  }

  It(reads_from_localhost) {
    auto it = std::begin(endpoints_.second);
    tcp::endpoint endpoint(it->endpoint().address(), 80);
    auto connected = connection_->connect(endpoint, "127.0.0.1");
    io_service_->run_one();
    auto connected_ = connected.get();
    Assert::That(connected_, Equals(boost::system::error_code()));

    http::request request{network::uri{"http://127.0.0.1/"}};
    request.set_method(http::method::GET);
    request.set_version("1.0");
    request.append_header("User-Agent", "normal_connection_test");
    request.append_header("Connection", "close");

    boost::asio::streambuf request_;
    std::ostream request_stream(&request_);
    request_stream << request;
    auto written = connection_->write(request_);
    //io_service_->run_one();
    std::cout << 0 << std::endl;
    //auto written_ = written.get();
    std::cout << 1 << std::endl;

    char output[8192];
    std::memset(output, 0, sizeof(output));
    std::cout << "A" << std::endl;
    auto read = connection_->read_some(boost::asio::mutable_buffers_1(output, sizeof(output)));
    std::cout << "A" << std::endl;
    //auto read_ = read.get();

    std::cout << output << std::endl;
  }

  std::unique_ptr<boost::asio::io_service> io_service_;
  std::unique_ptr<http::async_resolver_delegate> resolver_;
  std::pair<boost::system::error_code,
	    http::async_resolver_delegate::resolver_iterator_range> endpoints_;
  std::unique_ptr<http::connection_delegate> connection_;

};

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
