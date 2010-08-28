//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#define BOOST_TEST_MODULE XMPP XML parsers
#include <boost/test/unit_test.hpp>
#include <boost/network/uri/xmpp/uri.hpp>
#include <boost/network/tags/xmpp.hpp>
#include <string>

namespace xmpp = boost::network::uri::xmpp;


BOOST_AUTO_TEST_CASE(simple_uri_test) {
    xmpp::uri uri("node@jabber.org");
    BOOST_CHECK(uri.to_string() == "node@jabber.org");
    BOOST_CHECK(uri.node() == "node");
    BOOST_CHECK(uri.domain() == "jabber.org");
    BOOST_CHECK(uri.resource().empty());
}
