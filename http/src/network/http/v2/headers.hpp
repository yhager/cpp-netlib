// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_HEADERS_INC__
#define __NETWORK_HTTP_V2_HEADERS_INC__

#include <network/http/v2/message_base.hpp>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include <ostream>
#include <istream>

namespace network {
  namespace http {
    namespace v2 {

      struct header {
	typedef std::string string_type;
	typedef boost::string_ref string_view;
	string_type name, value;
      };

      class headers {

      public:

	typedef header::string_type string_type;
	typedef boost::string_ref string_view;
	typedef std::map<string_type, string_type> map_type;

	typedef map_type::value_type value_type;
	typedef map_type::key_type key_type;
	typedef map_type::mapped_type mapped_type;
	typedef map_type::allocator_type allocator_type;
	typedef map_type::iterator iterator;
	typedef map_type::const_iterator const_iterator;
	typedef map_type::reverse_iterator reverse_iterator;
	typedef map_type::const_reverse_iterator const_reverse_iterator;
	typedef map_type::size_type size_type;
	typedef map_type::difference_type difference_type;
	typedef map_type::pointer pointer;
	typedef map_type::const_pointer const_pointer;
	typedef map_type::reference reference;
	typedef map_type::const_reference const_reference;

	headers() = default;

	const_iterator begin() {
	  return std::begin(headers_);
	}

	const_iterator end() {
	  return std::end(headers_);
	}

	const_iterator begin() const {
	  return std::begin(headers_);
	}

	const_iterator end() const {
	  return std::end(headers_);
	}

	const_iterator cbegin() const {
	  return std::begin(headers_);
	}

	const_iterator cend() const {
	  return std::end(headers_);
	}

      private:

	map_type headers_;

      };

    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_HEADERS_INC__
