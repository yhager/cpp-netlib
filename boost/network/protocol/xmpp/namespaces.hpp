//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_NAMESPACES_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_NAMESPACES_INC__


# include <boost/network/traits/string.hpp>


namespace boost {
namespace network {
namespace xmpp {
namespace ns {
template <
    class Tag
    >
inline
typename string<Tag>::type client() {
    static const char client[] = {
        'j', 'a', 'b', 'b', 'e', 'r', ':', 'c', 'l', 'i', 'e', 'n', 't'};
    return typename string<Tag>::type(
        client, client + sizeof(client));
}

template <
    class Tag
    >
inline
typename string<Tag>::type server() {
    static const char server[] = {
        'j', 'a', 'b', 'b', 'e', 'r', ':', 's', 'e', 'r', 'v', 'e', 'r'};
    return typename string<Tag>::type(
        server, server + sizeof(server));
}

template <
    class Tag
    >
inline
typename string<Tag>::type component() {
    static const char component[] = {
        'j', 'a', 'b', 'b', 'e', 'r', ':', 'c', 'o', 'm', 'p', 'o',
        'n', 'e', 'n', 't', ':', 'a', 'c', 'c', 'e', 'p', 't'};
    return typename string<Tag>::type(
        component, component + sizeof(component));
}

template <
    class Tag
    >
inline
typename string<Tag>::type streams() {
    static const char streams[] = {
        'h', 't', 't', 'p', ':', '/', '/', 'e', 't', 'h', 'e', 'r',
        'x', '.', 'j', 'a', 'b', 'b', 'e', 'r', '.', 'o', 'r', 'g',
        '/', 's', 't', 'r', 'e', 'a', 'm', 's'};
    return typename string<Tag>::type(
        streams, streams + sizeof(streams));
}

template <
    class Tag
    >
inline
typename string<Tag>::type streams_ietf() {
    static const char streams_ietf[] = {
        'u', 'r', 'n', ':', 'i', 'e', 't', 'f', ':', 'p', 'a', 'r',
        'a', 'm', 's', ':', 'x', 'm', 'l', ':', 'n', 's', ':', 'x',
        'm', 'p', 'p', '-', 's', 't', 'r', 'e', 'a', 'm', 's'};
    return typename string<Tag>::type(
        streams_ietf, streams_ietf + sizeof(streams_ietf));
}
} // namespace ns
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_NAMESPACES_INC__
