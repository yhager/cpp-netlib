//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#define BOOST_TEST_MODULE XMPP XML parsers
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/parser_backends/libxml2/stanza_parser.hpp>
#include <boost/network/protocol/xmpp/message.hpp>
#include <boost/network/protocol/xmpp/presence.hpp>
#include <boost/network/protocol/xmpp/iq.hpp>


using namespace boost::network::xmpp;
using boost::network::xmpp::message;
using boost::network::xmpp::presence;
using boost::network::xmpp::iq;


basic_libxml2_stanza_parser<boost::network::tags::default_> stanza_parser;


namespace {
struct xml_document_fixture {
    xml_document_fixture() {
        stanza_parser.feed("<?xml version=\"1.0\"?><stream>");
    }

    ~xml_document_fixture() {
        stanza_parser.feed("</stream>");
    }
};
} // namespace


BOOST_GLOBAL_FIXTURE(xml_document_fixture);


BOOST_AUTO_TEST_CASE(parse_message_test) {
    message instance;
    stanza_parser.feed("<message to=\"foo\"><body /></message>", instance);
    BOOST_CHECK_EQUAL("message", instance.name());
    BOOST_CHECK_EQUAL("foo", instance.attribute("to"));
}


BOOST_AUTO_TEST_CASE(parse_presence_test) {
    presence instance;
    stanza_parser.feed("<presence><show /></presence>", instance);
    BOOST_CHECK_EQUAL("presence", instance.name());
}


BOOST_AUTO_TEST_CASE(parse_iq_test) {
    iq instance;
    stanza_parser.feed("<iq to=\"bar\"><query /></iq>", instance);
    BOOST_CHECK_EQUAL("iq", instance.name());
    BOOST_CHECK_EQUAL("bar", instance.attribute("to"));
}
