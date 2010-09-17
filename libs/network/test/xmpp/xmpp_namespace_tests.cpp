//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE XMPP namespace tests
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/namespaces.hpp>
#include <boost/network/tags.hpp>
#include <boost/mpl/list.hpp>
#include <boost/range/algorithm/equal.hpp>


namespace xmpp = boost::network::xmpp;


typedef boost::mpl::list<
    boost::network::tags::default_string,
    boost::network::tags::default_wstring
    > tag_types;


BOOST_AUTO_TEST_CASE_TEMPLATE(test_namespaces, T, tag_types) {
    BOOST_CHECK(boost::equal(std::string("jabber:client"),
                             xmpp::ns::client<T>()));
    BOOST_CHECK(boost::equal(std::string("jabber:server"),
                             xmpp::ns::server<T>()));
    BOOST_CHECK(boost::equal(std::string("jabber:component:accept"),
                             xmpp::ns::component<T>()));
    BOOST_CHECK(boost::equal(std::string("http://etherx.jabber.org/streams"),
                             xmpp::ns::streams<T>()));
    BOOST_CHECK(boost::equal(std::string("urn:ietf:params:xml:ns:xmpp-streams"),
                             xmpp::ns::streams_ietf<T>()));
}
