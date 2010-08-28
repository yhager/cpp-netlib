//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE XMPP message tests
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/message.hpp>


namespace xmpp = boost::network::xmpp;
using boost::network::xmpp::message;


BOOST_AUTO_TEST_CASE(xmpp_message_source_directive_test) {
    message instance;
    instance << boost::network::source("source@example.com");
    BOOST_CHECK_EQUAL("source@example.com", boost::network::source(instance));
}


BOOST_AUTO_TEST_CASE(xmpp_message_destination_directive_test) {
    message instance;
    instance << boost::network::destination("dest@example.com");
    BOOST_CHECK_EQUAL("dest@example.com", boost::network::destination(instance));
}


BOOST_AUTO_TEST_CASE(xmpp_message_header_directive_test) {
    message instance;
    instance << boost::network::header("type", "chat");
    BOOST_CHECK_EQUAL(1, boost::network::headers(instance).count("type"));
    boost::network::headers_range<message>::type range
        = boost::network::headers(instance)["type"];
    BOOST_CHECK (boost::begin(range) != boost::end(range));
}


BOOST_AUTO_TEST_CASE(xmpp_message_body_directive_test) {
    message instance;
    instance << boost::network::header("type", "chat")
             << boost::network::body("Hello world!");
}


BOOST_AUTO_TEST_CASE(xmpp_message_type_accessor_test) {
    message instance;
    instance.set_type("chat");
    BOOST_CHECK_EQUAL("chat", instance.type());
}


BOOST_AUTO_TEST_CASE(xmpp_message_id_accessor_test) {
    message instance;
    instance.set_id("t2w4qax3");
    BOOST_CHECK_EQUAL("t2w4qax3", instance.id());
}


// BOOST_AUTO_TEST_CASE(xmpp_message_type_directive_test) {
//     message instance;
//     instance << xmpp::type("chat");
//     BOOST_CHECK_EQUAL("chat", xmpp::type(instance));
// }
// 
// 
// BOOST_AUTO_TEST_CASE(xmpp_message_id_directive_test) {
//     message instance;
//     instance << xmpp::id("t2w4qax3");
//     BOOST_CHECK_EQUAL("t2w4qax3", xmpp::id(instance));
// }
// 
// 
// BOOST_AUTO_TEST_CASE(xmpp_message_error_directive_test) {
//     message instance;
//     instance << boost::network::source("source@example.com")
//              << boost::network::destination("dest@example.com")
//         ;
// }
