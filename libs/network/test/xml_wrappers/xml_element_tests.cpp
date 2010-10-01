//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE XML element tests
#include <boost/test/unit_test.hpp>
#include <boost/network/xml/element.hpp>
#include <boost/network/xml/element_io.hpp>


using namespace boost::network::detail;
using boost::network::detail::element;


BOOST_AUTO_TEST_CASE(default_constructor_test) {
    element instance;
    BOOST_CHECK(!instance.is_tag());
    BOOST_CHECK(!instance.is_text());
}


BOOST_AUTO_TEST_CASE(tag_constructor_test) {
    element instance(element::tag(), "message");
    BOOST_CHECK(instance.is_tag());
    BOOST_CHECK(!instance.is_text());
    BOOST_CHECK_EQUAL(instance.get_name(), std::string("message"));
}


BOOST_AUTO_TEST_CASE(text_constructor_test) {
    element instance(element::text(), "data");
    BOOST_CHECK(!instance.is_tag());
    BOOST_CHECK(instance.is_text());
    BOOST_CHECK(instance.get_text());
    BOOST_CHECK_EQUAL(instance.get_text().get(), std::string("data"));
}


BOOST_AUTO_TEST_CASE(text_constructor_empty_string_test) {
    element instance(element::text(), "");
    BOOST_CHECK(!instance.is_tag());
    BOOST_CHECK(instance.is_text());
    BOOST_CHECK(instance.get_text().get().empty());
}


BOOST_AUTO_TEST_CASE(children_test) {
    element instance(element::tag(), "message");
    instance.set_attribute("from", "someone@example.org");
    instance.set_attribute("to", "world@example.org");
    element *body = new element(element::tag(), "body");
    element *text = new element(element::text(), "Hello world!");
    body->add_child(text);
    instance.add_child(body);

    boost::iterator_range<element::element_children_type::const_iterator>
        children_1(instance.get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children_1),
                                    boost::end(children_1)), 1);
    
    boost::iterator_range<element::element_children_type::const_iterator>
        children_2((*boost::begin(children_1))->get_children());
    BOOST_CHECK_EQUAL(std::distance(boost::begin(children_2),
                                    boost::end(children_2)), 1);
    BOOST_CHECK((*boost::begin(children_2))->is_text());
    BOOST_CHECK_EQUAL((*boost::begin(children_2))->get_text(), std::string("Hello world!"));
}


BOOST_AUTO_TEST_CASE(element_ostream_test) {
    element instance(element::tag(), "message");
    instance.set_attribute("from", "someone@example.org");
    instance.set_attribute("to", "world@example.org");
    element *body = new element(element::tag(), "body");
    element *text = new element(element::text(), "Hello world!");
    body->add_child(text);
    instance.add_child(body);

    std::ostringstream os;
    os << instance;
    
    BOOST_CHECK_EQUAL(os.str(),
                      std::string("<message from=\"someone@example.org\""
                                  " to=\"world@example.org\">"
                                  "<body>Hello world!</body></message>"));
}
