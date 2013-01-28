
// Copyright 2007, 2012 Dean Michael Berris <dberris@google.com>
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/message.hpp>
#include <algorithm>

using namespace network;

TEST(message_test, copy_constructor) {
    message instance;
    instance << header("name", "value");
    message copy(instance);
    headers_wrapper::container_type const &headers_ = headers(copy);
    ASSERT_EQ(headers_.count("name"), static_cast<std::size_t>(1));
    message::headers_range range = headers_.equal_range("name");
    ASSERT_TRUE (!boost::empty(range));
}

TEST(message_test, swap) {
    message instance;
    instance << header("name", "value");
    message other;
    swap(instance, other);
    headers_wrapper::container_type const &instance_headers = headers(instance);
    headers_wrapper::container_type const &other_headers = headers(other);
    ASSERT_EQ (instance_headers.count("name"), static_cast<std::size_t>(0));
    ASSERT_EQ (other_headers.count("name"), static_cast<std::size_t>(1));
}

TEST(message_test, headers_directive) {
    message instance;
    instance << header("name", "value");
    headers_wrapper::container_type const &instance_headers = headers(instance);
    ASSERT_EQ ( instance_headers.count("name"), static_cast<std::size_t>(1) );
    message::headers_range range = instance_headers.equal_range("name");
    ASSERT_TRUE (boost::begin(range) != boost::end(range));
}

TEST(message_test, body_directive) {
    message instance;
    instance << ::network::body("body");
    std::string body_string = body(instance);
    ASSERT_TRUE ( body_string == "body" );
}

TEST(message_test, source_directive) {
    message instance;
    instance << ::network::source("source");
    std::string source_string = source(instance);
    ASSERT_TRUE ( source_string == "source" );
}

TEST(message_test, destination_directive) {
    message instance;
    instance << destination("destination");
    std::string const & destination_ = destination(instance);
    ASSERT_TRUE ( destination_ == "destination" );
}

TEST(message_test, remove_header_directive) {
    message instance;
    instance << header("name", "value")
        << remove_header("name");
    headers_wrapper::container_type const &instance_headers =
        headers(instance);
    message::headers_range range = instance_headers.equal_range("name");
    ASSERT_TRUE ( boost::begin(range) == boost::end(range) );
}
