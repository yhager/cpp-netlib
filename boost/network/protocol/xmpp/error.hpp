//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_ERROR_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_ERROR_INC__


# include <boost/network/protocol/xmpp/stanza.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag
    >
class basic_error
    : public basic_stanza<Tag> {
public:

    basic_error() {

    }

};


typedef basic_error<tags::default_> error;
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_ERROR_INC__
