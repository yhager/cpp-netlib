// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris <dberris@google.com>.
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file
 * \brief
 */

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_INC__

#include <memory>
#include <functional>
#include <boost/utility/string_ref.hpp>

namespace network {
  namespace http {
    namespace v2 {

      class response;
      class request;
      class request_options;

      /**
       * \ingroup http_client
       * \class connection network/http/v2/client/connection.hpp
       * \brief A base class for HTTP connections.
       */
      class connection {

        connection(const connection &) = delete;
        connection &operator = (const connection &) = delete;

      public:

        /**
         * \typedef The connection callback type.
         */
        typedef std::function<void (boost::string_ref, boost::system::error_code)> callback_type;

        /**
         * \brief Constructor.
         */
        connection() = default;

        /**
         * \brief Destructor.
         */
        virtual ~connection() noexcept { }

        /**
         * \brief Sends an HTTP request to the server.
         * \param method The HTTP method.
         * \param request_ The request object.
         * \param get_body
         * \param callback
         * \param options
         * \returns An HTTP response.
         * \throws connection_error
         */
        virtual response send_request(std::string method,
                                      request request_,
                                      bool get_body,
                                      callback_type callback,
                                      request_options &options) = 0;

        virtual void reset() = 0;

      };
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_INC__
