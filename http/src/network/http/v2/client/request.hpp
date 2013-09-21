// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris (dberris@google.com).
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_REQUEST_INC__
#define __NETWORK_HTTP_V2_CLIENT_REQUEST_INC__

/**
 * \file
 * \brief Contains classes for handling creating and handling HTTP
 *        requests.
 */

#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <cstdint>
#include <algorithm>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/as_literal.hpp>
#include "network/http/v2/constants.hpp"
#include "network/http/v2/method.hpp"
#include "network/http/v2/client/client_errors.hpp"
#include "network/uri.hpp"

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \ingroup http_client
       * \class request_options network/http/v2/client/request.hpp
       * \brief A class used to configure an HTTP request.
       */
      class request_options {

      public:

	/**
	 * \brief Constructor.
	 */
	request_options()
	  : resolve_timeout_(30000)
	  , read_timeout_(30000)
	  , total_timeout_(30000)
	  , max_redirects_(10) { }

	/**
	 * \brief Copy constructor.
	 */
	request_options(request_options const &) = default;

	/**
	 * \brief Move constructor.
	 */
	request_options(request_options &&) = default;

	/**
	 * \brief Assignment operator.
	 */
	request_options &operator = (request_options other) {
	  other.swap(*this);
	  return *this;
	}

	/**
	 * \brief Destructor.
	 */
	~request_options() noexcept {

	}

	void swap(request_options &other) noexcept {
	  std::swap(resolve_timeout_, other.resolve_timeout_);
	  std::swap(read_timeout_, other.read_timeout_);
	  std::swap(total_timeout_, other.total_timeout_);
	}

	request_options &resolve_timeout(std::uint64_t resolve_timeout) noexcept {
	  resolve_timeout_ = resolve_timeout;
	  return *this;
	}

	std::uint64_t resolve_timeout() const noexcept {
	  return resolve_timeout_;
	}

	request_options &read_timeout(std::uint64_t read_timeout) noexcept {
	  read_timeout_ = read_timeout;
	  return *this;
	}

	std::uint64_t read_timeout() const noexcept {
	  return read_timeout_;
	}

	request_options &total_timeout(std::uint64_t total_timeout) noexcept {
	  total_timeout_ = total_timeout;
	  return *this;
	}

	std::uint64_t total_timeout() const noexcept {
	  return total_timeout_;
	}

	request_options &max_redirects(int max_redirects) noexcept {
	  max_redirects_ = max_redirects;
	  return *this;
	}

	int max_redirects() const noexcept {
	  return max_redirects_;
	}

      private:

	std::uint64_t resolve_timeout_;
	std::uint64_t read_timeout_;
	std::uint64_t total_timeout_;
	int max_redirects_;

      };

      /**
       * \ingroup http_client
       * \class byte_source network/http/v2/client/request.hpp
       * \brief An abstract class that allows a request object to read
       *        data from any source.
       */
      class byte_source {

      public:

	/**
	 * \typedef string_type
	 * \brief The byte_source string type.
	 */
	typedef std::string string_type;

	/**
	 * \typedef size_type
	 * \brief The byte_source size type.
	 */
	typedef std::size_t size_type;

	/**
	 * \brief Destructor.
	 */
	virtual ~byte_source() noexcept {}

	/**
	 * \brief Allows the request to read the data into a local
	 *        copy of it's source string.
	 */
	virtual size_type read(string_type &source, size_type length) = 0;

      };

      /**
       * \ingroup http_client
       * \class string_byte_source network/http/v2/client/request.hpp
       * \brief A class that wraps a string as a byte source.
       */
      class string_byte_source : public byte_source {

      public:

	/**
	 * \brief Constructor.
	 */
	explicit string_byte_source(string_type source);

	/**
	 * \brief Destructor.
	 */
	virtual ~string_byte_source() {}

	virtual size_type read(string_type &source, size_type length);

      private:

	string_type source_;

      };

      /**
       * \ingroup http_client
       * \class request network/http/v2/client/request.hpp
       * \brief A class that models an HTTP request.
       */
      class request {

      public:

	/**
	 * \typedef string_type
	 * \brief The request string type.
	 */
	typedef byte_source::string_type string_type;
	/**
	 * \typedef headers_type
	 * \brief The request headers type.
	 */
	typedef std::vector<std::pair<string_type, string_type>> headers_type;
	/**
	 * \typedef headers_iterator
	 * \brief The request headers iterator.
	 */
	typedef headers_type::iterator headers_iterator;
	/**
	 * \typedef const_headers_iterator
	 * \brief The request headers const_iterator.
	 */
	typedef headers_type::const_iterator const_headers_iterator;

	/**
	 * \brief Constructor.
	 */
	request()
	  : byte_source_(nullptr) { }

	/**
	 * \brief Constructor.
	 */
	explicit request(uri destination, std::shared_ptr<byte_source> source = nullptr)
	  : destination_(destination), byte_source_(source) {
	  if (auto scheme = destination.scheme()) {
	    if ((!boost::equal(*scheme, boost::as_literal("http"))) &&
		(!boost::equal(*scheme, boost::as_literal("https")))) {
	      throw invalid_url();
	    }
	  }
	  else {
	    throw invalid_url();
	  }
	}

	/**
	 * \brief Copy constructor.
	 */
	request(const request &other)
	  : destination_(other.destination_)
	  , method_(other.method_)
	  , version_(other.version_)
	  , headers_(other.headers_)
	  , byte_source_(other.byte_source_) { }

	/**
	 * \brief Move constructor.
	 */
	request(request &&other) noexcept
	  : destination_(std::move(other.destination_))
	  , method_(std::move(other.method_))
	  , version_(std::move(other.version_))
	  , headers_(std::move(other.headers_))
	  , byte_source_(std::move(other.byte_source_)) { }

	/**
	 * \brief Assignment operator.
	 */
	request &operator = (request other) {
	  other.swap(*this);
	  return *this;
	}

	/**
	 * \brief Destructor.
	 */
	~request() noexcept {

	}

	/**
	 * \brief Swap.
	 */
	void swap(request &other) noexcept {
	  std::swap(destination_, other.destination_);
	  std::swap(method_, other.method_);
	  std::swap(version_, other.version_);
	  std::swap(headers_, other.headers_);
	  std::swap(byte_source_, other.byte_source_);
	}

	/**
	 * \brief Sets the request destination.
	 * \param destination The destination.
	 */
	void set_destination(uri destination) {
	  destination_ = std::move(destination);
	}

	/**
	 * \brief Gets the request destination host.
	 * \return The destination host.
	 * \pre destination_.scheme() != boost::none
	 * \pre destination_.host() != boost::none
	 */
	string_type host() const {
	  assert(destination_.host());
	  return string_type(std::begin(*destination_.host()), std::end(*destination_.host()));
	}

	/**
	 * \brief Gets the request destination port.
	 * \return The destination port.
	 * \pre destination_.scheme() != boost::none
	 * \pre *destination_.scheme() == "http"
	 * \pre *destination_.scheme() == "https"
	 */
	std::uint16_t port() const {
	  assert(destination_.scheme());
	  assert((string_type(*destination_.scheme()) == "http") ||
		 (string_type(*destination_.scheme()) == "https"));
	  if (!destination_.port()) {
	    if (string_type(*destination_.scheme()) == "http") {
	      return 80;
	    }
	    else if (string_type(*destination_.scheme()) == "https") {
	      return 443;
	    }
	  }
	  return *destination_.port<std::uint16_t>();
	}

	void set_body(std::shared_ptr<byte_source> byte_source) {
	  byte_source_ = byte_source;
	}

	void append_header(string_type key, string_type value) {
	  headers_.emplace_back(std::make_pair(key, value));
	}

	boost::iterator_range<const_headers_iterator> headers() const {
	  return boost::make_iterator_range(std::begin(headers_), std::end(headers_));
	}

	void remove_header(string_type key) {
	  bool found_all = false;
	  while (!found_all) {
	    auto it = std::find_if(std::begin(headers_), std::end(headers_),
				   [&key] (const std::pair<string_type, string_type> &header) {
				     return header.first == key;
				   });
	    found_all = (it == std::end(headers_));
	    if (!found_all) {
	      headers_.erase(it);
	    }
	  }
	}

	void clear_headers() {
	  headers_type().swap(headers_);
	}

	void set_method(network::http::v2::method method) {
	  method_ = method;
	}

	network::http::v2::method method() const {
	  return method_;
	}

	void set_version(string_type version) {
	  version_ = std::move(version);
	}

	string_type version() const {
	  return version_;
	}

      private:

	uri destination_;
	network::http::v2::method method_;
	string_type version_;
	headers_type headers_;
	std::shared_ptr<byte_source> byte_source_;

	friend std::ostream &operator << (std::ostream &os, const request &req) {
	  os << req.method_ << " " << *req.destination_.path() << " HTTP/" << req.version_ << "\r\n";
	  os << "Host: " << *req.destination_.host();
	  os << "\r\n";
	  for (auto header : req.headers_) {
	    os << header.first << ": " << header.second << "\r\n";
	  }
	  return os << "\r\n";
	}
      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_REQUEST_INC__
