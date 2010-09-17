//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE XMPP stanza tests
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/stanza.hpp>
#include <boost/network/protocol/xmpp/message.hpp>
#include <boost/network/protocol/xmpp/iq.hpp>
#include <boost/network/protocol/xmpp/presence.hpp>
#include <boost/network/detail/xml_wrappers/traits/parser_backend.hpp>
#include <boost/network/detail/xml_wrappers/parser_backends/expat/element_parser.hpp>
#include <boost/network/protocol/xmpp/detail/stanza_parser.hpp>
#include <boost/network/detail/xml_wrappers/parser_backends/libxml2/element_parser.hpp>


namespace xmpp = boost::network::xmpp;


xmpp::detail::basic_stanza_parser<boost::network::tags::default_> stanza_parser;


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
    xmpp::message instance;
    stanza_parser.feed("<message to=\"foo\"><body /></message>", instance);
    BOOST_CHECK_EQUAL("message", instance.get_name());
    BOOST_CHECK_EQUAL("foo", instance.get_attribute("to"));
}


BOOST_AUTO_TEST_CASE(parse_presence_test) {
    xmpp::presence instance;
    stanza_parser.feed("<presence to=\"foo\"></presence>", instance);
    BOOST_CHECK_EQUAL("presence", instance.get_name());
    BOOST_CHECK_EQUAL("foo", instance.get_attribute("to"));
}
