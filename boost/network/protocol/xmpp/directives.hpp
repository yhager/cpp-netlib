//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_DIRECTIVES_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_DIRECTIVES_INC__


# include <boost/network/protocol/xmpp/directives/attribute.hpp>
# include <boost/network/protocol/xmpp/directives/text.hpp>
# include <boost/network/protocol/xmpp/directives/id.hpp>
# include <boost/network/protocol/xmpp/directives/from.hpp>
# include <boost/network/protocol/xmpp/directives/to.hpp>
# include <boost/network/protocol/xmpp/directives/type.hpp>
# include <boost/network/protocol/xmpp/directives/namespace.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag,
    class Directive
    >
inline
basic_stanza<Tag> &operator << (basic_stanza<Tag> &stanza,
                                const Directive &directive) {
    directive(stanza);
    return stanza;
}
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_DIRECTIVES_INC__
