//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#define BOOST_TEST_MODULE XMPP XML parsers
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/parser_backends/expat/element_parser.hpp>
#include <boost/network/protocol/xmpp/element.hpp>


using namespace boost::network::xmpp;
using boost::network::xmpp::element;


basic_expat_element_parser<boost::network::tags::default_> element_parser;


namespace {
struct xml_document_fixture {
    xml_document_fixture() {
        element_parser.feed("<?xml version=\"1.0\"?><stream>");
    }

    ~xml_document_fixture() {
        element_parser.feed("</stream>");
    }
};
} // namespace


BOOST_GLOBAL_FIXTURE(xml_document_fixture);


BOOST_AUTO_TEST_CASE(parse_message_test) {
    element instance;
    element_parser.feed("<message to=\"foo\"><body /></message>", &instance);
    BOOST_CHECK_EQUAL("message", instance.get_name());
    BOOST_CHECK(instance.get_attribute("to"));
    BOOST_CHECK_EQUAL("foo", instance.get_attribute("to").get());
    
    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 1);
    BOOST_CHECK_EQUAL("body", (*boost::begin(children))->get_name());
}


BOOST_AUTO_TEST_CASE(parse_presence_test) {
    element instance;
    element_parser.feed("<presence><show /></presence>", &instance);
    BOOST_CHECK_EQUAL("presence", instance.get_name());

    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 1);
    BOOST_CHECK_EQUAL("show", (*boost::begin(children))->get_name());
}


BOOST_AUTO_TEST_CASE(parse_iq_test) {
    element instance;
    element_parser.feed("<iq to=\"bar\"><query /></iq>", &instance);
    BOOST_CHECK_EQUAL("iq", instance.get_name());
    BOOST_CHECK(instance.get_attribute("to"));
    BOOST_CHECK_EQUAL("bar", instance.get_attribute("to").get());

    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 1);
    BOOST_CHECK_EQUAL("query", (*boost::begin(children))->get_name());
}
