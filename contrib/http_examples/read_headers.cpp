// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/client.hpp>
#include <iostream>

namespace http = network::http::v2;



int
main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " url" << std::endl;
    return 1;
  }

  try {
    http::client client;
    http::request request{network::uri{std::string{argv[1]}}};
    request.append_header("Connection", "close");
    auto future_response = client.head(request);
    auto response = future_response.get();

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
