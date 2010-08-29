//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE XMPP iq tests
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/iq.hpp>


namespace xmpp = boost::network::xmpp;


BOOST_AUTO_TEST_CASE(xmpp_iq_source_directive_test) {
    xmpp::iq instance;
    instance << boost::network::source("source@example.com");
    BOOST_CHECK_EQUAL("source@example.com", boost::network::source(instance));
}


BOOST_AUTO_TEST_CASE(xmpp_iq_destination_directive_test) {
    xmpp::iq instance;
    instance << boost::network::destination("dest@example.com");
    BOOST_CHECK_EQUAL("dest@example.com", boost::network::destination(instance));
}
