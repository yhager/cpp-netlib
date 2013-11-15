// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris (dberris@google.com).
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_RESPONSE_INC__
#define __NETWORK_HTTP_V2_CLIENT_RESPONSE_INC__

#include <cstdint>
#include <vector>
#include <utility>
#include <string>
#include <future>
#include <network/http/v2/status.hpp>
#include <boost/range/iterator_range.hpp>
#include <network/uri.hpp>

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \ingroup http_client
       * \class response network/http/v2/client/response.hpp
       * \brief A class that encapsulates an HTTP response.
       */
      class response {

      public:

        /**
         * \typedef string_type
         * \brief The responses string_type.
         */
	typedef std::string string_type;

        /**
         * \typedef headers_type
         * \brief
         */
	typedef std::vector<std::pair<string_type, string_type>> headers_type;

        /**
         * \typedef headers_iterator
         */
	typedef headers_type::iterator headers_iterator;

        /**
         * \typedef const_headers_iterator
         */
	typedef headers_type::const_iterator const_headers_iterator;

        /**
         * \brief Constructor.
         */
	response() { }

        /**
         * \brief Copy constructor.
         * \param other The other response object.
         */
	response(const response &other)
	  : version_(other.version_)
	  , status_(other.status_)
	  , status_message_(other.status_message_)
	  , headers_(other.headers_) {

	}

        /**
         * \brief Move constructor.
         * \param other The other response object.
         */
	response(response &&other) noexcept
          : version_(std::move(other.version_))
          , status_(std::move(other.status_))
          , status_message_(std::move(other.status_message_))
	  , headers_(std::move(other.headers_)) {

	}

        /**
         * \brief Assignment operator.
         * \param other The other response object.
         */
	response &operator= (response other) {
	  other.swap(*this);
	  return *this;
	}

        /**
         * \brief Swap function.
         * \param other The other response object.
         */
	void swap(response &other) noexcept {
          using std::swap;
	  swap(version_, other.version_);
	  swap(status_, other.status_);
	  swap(status_message_, other.status_message_);
	  swap(headers_, other.headers_);
	}

        /**
         * \brief Returns the HTTP response status.
         * \returns The status code.
         */
        network::http::v2::status::code status() const {
	  return status_;
	}

        /**
         * \brief Returns the HTTP response status message.
         * \returns The status message.
         */
	string_type status_message() const {
	  return status_message_;
	}

        /**
         * \brief
         */
	boost::iterator_range<const_headers_iterator> headers() const {
	  return boost::make_iterator_range(std::begin(headers_), std::end(headers_));
	}

	std::future<string_type> read_body(std::size_t length) const;

        // set_version
        // set_status
        // set_status_message
	// add_header
	// set_body
	// append_body
	// get_body

        /**
         * \brief Returns the HTTP version.
         * \returns The HTTP version.
         */
	string_type version() const {
	  return version_;
	}

      private:

        string_type version_;
        network::http::v2::status::code status_;
	string_type status_message_;
	headers_type headers_;

      };

      inline
      void swap(response &lhs, response &rhs) noexcept {
        lhs.swap(rhs);
      }
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_RESPONSE_INC__
