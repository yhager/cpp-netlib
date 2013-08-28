// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_REQUEST_INC__
#define __NETWORK_HTTP_V2_REQUEST_INC__

#include <cstdint>
#include <memory>
#include <string>
#include <network/http/v2/constants.hpp>
#include <network/http/v2/message_base.hpp>
#include <network/uri.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class byte_source {

      public:

	typedef message_base::string_type string_type;
	typedef message_base::size_type size_type;

	virtual ~byte_source() {}

	virtual size_type read(string_type &source, size_type length) = 0;

      };

      class string_byte_source : public byte_source {

      public:

	explicit string_byte_source(string_type source);

	virtual ~string_byte_source() {}

	virtual size_type read(string_type &source, size_type length);

      private:

	string_type source_;

      };

      class request {

      public:

	typedef byte_source::string_type string_type;

	request(uri destination, std::shared_ptr<byte_source> source = nullptr)
	  : destination_(destination), byte_source_(source) { }

	request(const request &other)
	  : destination_(other.destination_), byte_source_(other.byte_source_) { }

	request(request &&other) noexcept
	  : destination_(std::move(other.destination_))
	  , byte_source_(std::move(other.byte_source_)) { }

	request &operator = (request other) {
	  other.swap(*this);
	  return *this;
	}

	void swap(request &other) noexcept {
	  std::swap(destination_, other.destination_);
	  std::swap(byte_source_, other.byte_source_);
	  std::swap(headers_, other.headers_);
	  std::swap(method_, other.method_);
	  std::swap(version_, other.version_);
	}

	void set_body(std::shared_ptr<byte_source> byte_source) {
	  byte_source_ = byte_source;
	}

	void add_header(string_type key, string_type value) {
	  headers_.emplace(key, value);
	}

	void remove_header(string_type key) {
	  headers_.erase(key);
	}

	void clear_headers() {
	  headers_.clear();
	}

	void set_method(string_type method) {
	  method_ = std::move(method);
	}

	string_type method() const {
	  return method_;
	}

	void set_version(string_type version) {
	  version_ = std::move(version);
	}

	string_type version() const {
	  return version_;
	}

	uri destination_;
	std::shared_ptr<byte_source> byte_source_;
	std::map<string_type, string_type> headers_;
	string_type method_, version_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_REQUEST_INC__
