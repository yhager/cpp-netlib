//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_DETAILS_NS_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_DETAILS_NS_INC__


namespace boost {
namespace network {
namespace xmpp {
namespace details {
class namespaces {
public:
    
    static const char *client() {
        return "jabber:client";
    }

    static const char *component() {
        return "jabber:component:accept";
    }

    static const char *streams() {
        return "http://etherx.jabber.org/streams";
    }

    static const char *streams_ietf() {
        return "urn:ietf:params:xml:ns:xmpp-streams";
    }

    static const char *tls() {
        return "urn:ietf:params:xml:ns:xmpp-tls";
    }

    static const char *sasl() {
        return "urn:ietf:params:xml:ns:xmpp-sasl";
    }

    static const char *bind() {
        return "urn:ietf:params:xml:ns:xmpp-bind";
    }

    static const char *session() {
        return "urn:ietf:params:xml:ns:xmpp-session";
    }

    static const char *auth() {
        return "jabber:iq:auth";
    }

    static const char *disco_info() {
        return "http://jabber.org/protocol/disco#info";
    }

    static const char *disco_items() {
        return "http://jabber.org/protocol/disco#items";
    }

    static const char *roster() {
        return "jabber:iq:roster";
    }
};
} // namespace details
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_DETAILS_NS_INC__
