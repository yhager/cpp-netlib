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
#include <network/http/v2/constants.hpp>
#include <boost/range/iterator_range.hpp>
#include <network/uri.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class response {

      public:

	typedef std::string string_type;
	typedef std::vector<std::pair<string_type, string_type>> headers_type;
	typedef headers_type::iterator headers_iterator;
	typedef headers_type::const_iterator const_headers_iterator;

	response() { }

	response(const response &other)
	  : status_(other.status_)
	  , version_(other.version_)
	  , status_message_(other.status_message_)
	  , headers_(other.headers_) {

	}

	response(response &&other) noexcept
	  : status_(std::move(other.status_))
	  , version_(std::move(other.version_))
	  , status_message_(std::move(other.status_message_))
	  , headers_(std::move(other.headers_)) {

	}

	response &operator= (response other) {
	  other.swap(*this);
	  return *this;
	}

	void swap(response &other) noexcept {
	  std::swap(status_, other.status_);
	  std::swap(version_, other.version_);
	  std::swap(status_message_, other.status_message_);
	  std::swap(headers_, other.headers_);
	}

	std::uint16_t status() const {
	  return status_;
	}

	string_type status_message() const {
	  return status_message_;
	}

	boost::iterator_range<const_headers_iterator> headers() const {
	  return boost::make_iterator_range(std::begin(headers_), std::end(headers_));
	}

	std::future<string_type> read_body(std::size_t length) const;

	// destination
	// source
	// add_header
	// remove_header
	// set_body
	// append_body
	// get_body

	string_type version() const {
	  return version_;
	}

      private:

	std::uint16_t status_;
	string_type version_, status_message_;
	headers_type headers_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_RESPONSE_INC__
