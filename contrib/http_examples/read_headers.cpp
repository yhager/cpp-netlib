// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/client.hpp>
#include <iostream>

namespace http = network::http;


int
main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " url" << std::endl;
    return 1;
  }

  try {
    http::client client;
    http::client::request request{network::uri{std::string{argv[1]}}};
    request.version("1.0");
    request.append_header("Connection", "close");
    request.append_header("User-Agent", "cpp-netlib read_headers example");
    auto future_response = client.head(request);
    auto response = future_response.get();

    std::cout << "HTTP version: " << response.version() << std::endl;
    std::cout << "HTTP status: " << static_cast<int>(response.status()) << std::endl;
    std::cout << "HTTP status message: " << response.status_message() << std::endl;
    std::cout << std::endl;
    for (auto header : response.headers()) {
      std::cout << header.first << ": " << header.second << std::endl;
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
