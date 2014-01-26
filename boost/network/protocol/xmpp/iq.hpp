//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_IQ_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_IQ_INC__


# include <boost/network/protocol/xmpp/stanza.hpp>
// # include <boost/network/message/message_concept.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag
    >
class basic_iq
    : public basic_stanza<Tag> {

    typedef basic_stanza<Tag> base_type;

public:

    typedef typename base_type::string_type string_type;
    typedef typename base_type::headers_container_type headers_container_type;

    basic_iq() {
        static const char name[] = {'i', 'q', 0};
        base_type::set_name(string_type(name, name + sizeof(name)));
    }

    basic_iq(const basic_iq &other)
        : basic_stanza<Tag>(other) {

    }

    basic_iq &operator = (const basic_iq &other) {
        basic_iq tmp(other);
        swap(tmp);
        return *this;
    }

    ~basic_iq() {

    }

    void swap(basic_iq &other) {
        base_type::swap(other);
    }

};


typedef basic_iq<tags::default_> iq;
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_IQ_INC__
