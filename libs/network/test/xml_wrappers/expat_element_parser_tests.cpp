//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE expat wrapper tests
#include <boost/test/unit_test.hpp>
#include <boost/network/xml/parser_backends/expat_parser.hpp>
#include <boost/network/xml/element.hpp>
#include <boost/network/xml/element_io.hpp>
#include <boost/foreach.hpp>

#include <iostream>


using namespace boost::network::detail;
using boost::network::detail::element;


basic_expat_parser<boost::network::tags::default_> *element_parser;


namespace {
struct xml_document_fixture {
    xml_document_fixture() {
        element_parser = new basic_expat_parser<
            boost::network::tags::default_>;
        element_parser->feed("<?xml version=\"1.0\"?><stream:stream>");
    }

    ~xml_document_fixture() {
        element_parser->feed("</stream:stream>");
        delete element_parser;
    }

};
} // namespace

// BOOST_GLOBAL_FIXTURE(xml_document_fixture);


BOOST_FIXTURE_TEST_SUITE(expat_parser_test_suite, xml_document_fixture)

BOOST_AUTO_TEST_CASE(parse_message_test) {
    element instance;
    element_parser->feed("<message to=\"foo\"><body /></message>", instance);
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
    element_parser->feed("<presence><show /></presence>", instance);
    BOOST_CHECK_EQUAL("presence", instance.get_name());

    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 1);
    BOOST_CHECK_EQUAL("show", (*boost::begin(children))->get_name());
}


BOOST_AUTO_TEST_CASE(parse_iq_test) {
    element instance;
    element_parser->feed("<iq to=\"bar\"><query /></iq>", instance);
    BOOST_CHECK_EQUAL("iq", instance.get_name());
    BOOST_CHECK(instance.get_attribute("to"));
    BOOST_CHECK_EQUAL("bar", instance.get_attribute("to").get());

    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 1);
    BOOST_CHECK_EQUAL("query", (*boost::begin(children))->get_name());
}


BOOST_AUTO_TEST_CASE(parse_tls) {
    element instance;
    element_parser->feed(
        "<stream:features><starttls xmlns='urn:ietf:params:xml:ns:xmpp-tls'/>"
        "<mechanisms xmlns='urn:ietf:params:xml:ns:xmpp-sasl'>"
        "<mechanism>DIGEST-MD5</mechanism><mechanism>PLAIN</mechanism>"
        "</mechanisms>"
        "<register xmlns='http://jabber.org/features/iq-register'/>"
        "</stream:features>", instance);
    BOOST_CHECK_EQUAL("stream:features", instance.get_name());
    
    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 3);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(parse_multiple_elements) {
    element_parser =
        new basic_expat_parser<boost::network::tags::default_>;
    element instance;
    element_parser->feed(
        "<?xml version='1.0'?>"
        "<stream:stream xmlns='jabber:client' "
        "xmlns:stream='http://etherx.jabber.org/streams' "
        "id='3829999679' from='127.0.0.1' version='1.0' "
        "xml:lang='en'>"
        "<stream:features><starttls xmlns='urn:ietf:params:xml:ns:xmpp-tls'/>"
        "<mechanisms xmlns='urn:ietf:params:xml:ns:xmpp-sasl'>"
        "<mechanism>DIGEST-MD5</mechanism><mechanism>PLAIN</mechanism>"
        "</mechanisms>"
        "<register xmlns='http://jabber.org/features/iq-register'/>"
        "</stream:features>", instance);
    boost::iterator_range<element::element_children_type::const_iterator> children
        (instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 1);
    BOOST_CHECK_EQUAL((*boost::begin(children))->get_name(),
                      "stream:features");
    children = (*boost::begin(children))->get_children();
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children),
                                    boost::end(children)), 3);

    element_parser->feed("</stream:stream>");
    delete element_parser;
}
