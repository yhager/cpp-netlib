// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <igloo/igloo_alt.h>
#include "network/http/v2/client.hpp"

using namespace igloo;
namespace http = network::http::v2;

Describe(http_client) {

  It(gets_a_response) {
    http::request request(network::uri("http://127.0.0.1/"));
    auto response = client_.get(request);
  }

  http::client client_;

};

//TEST(client_test, get) {
//  http::client client;
//  auto response = client.get(http::request(network::uri("http://127.0.0.1/")));
//  FAIL();
//}
//
//TEST(client_test, post) {
//  http::client client;
//  auto response = client.post(http::request(network::uri("http://127.0.0.1/")));
//  FAIL();
//}
//
//TEST(client_test, put) {
//  http::client client;
//  auto response = client.put(http::request(network::uri("http://127.0.0.1/")));
//  FAIL();
//}
//
//TEST(client_test, delete) {
//  http::client client;
//  auto response = client.delete_(http::request(network::uri("http://127.0.0.1/")));
//  FAIL();
//}
//
//TEST(client_test, head) {
//  http::client client;
//  auto response = client.head(http::request(network::uri("http://127.0.0.1/")));
//  FAIL();
//}

int
main(int argc, char *argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char **>(argv));
}
