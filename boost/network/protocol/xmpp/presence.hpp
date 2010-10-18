//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_PRESENCE_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_PRESENCE_INC__


# include <boost/network/protocol/xmpp/stanza.hpp>
// # include <boost/network/message/message_concept.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag
    >
class basic_presence
    : public basic_stanza<Tag> {

    typedef basic_stanza<Tag> base_type;

public:

    typedef typename base_type::string_type string_type;
    typedef typename base_type::headers_container_type headers_container_type;

    basic_presence() {
        static const char name[] = {'p', 'r', 'e', 's', 'e', 'n', 'c', 'e', 0};
        base_type::set_name(string_type(name, name + sizeof(name)));
    }

    basic_presence(const basic_presence &other)
        : basic_stanza<Tag>(other) {

    }

    basic_presence &operator = (const basic_presence &other) {
        basic_presence tmp(other);
        swap(tmp);
        return *this;
    }

    ~basic_presence() {

    }

    void swap(basic_presence &other) {
        base_type::swap(other);
    }

};


typedef basic_presence<tags::default_> presence;
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_PRESENCE_INC__
