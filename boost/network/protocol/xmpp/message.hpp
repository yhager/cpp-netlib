//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_MESSAGE_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_MESSAGE_INC__


# include <boost/network/protocol/xmpp/stanza.hpp>
// # include <boost/network/message/message_concept.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag
    >
class basic_message
    : public basic_stanza<Tag> {

    typedef basic_stanza<Tag> base_type;

public:

    typedef typename base_type::string_type string_type;
    typedef typename base_type::headers_container_type headers_container_type;

    basic_message() {
        static const char name[] = {'m', 'e', 's', 's', 'a', 'g', 'e', 0};
        base_type::set_name(string_type(name, name + sizeof(name)));
    }

    basic_message(const basic_message &other)
        : basic_stanza<Tag>(other) {

    }

    basic_message &operator = (const basic_message &other) {
        basic_message tmp(other);
        swap(tmp);
        return *this;
    }

    ~basic_message() {

    }

    void swap(basic_message &other) {
        base_type::swap(other);
    }

    void set_type(const string_type &type) {
        static const char type_[] = {'t', 'y', 'p', 'e', 0};
        set_attribute(string_type(type_, type_ + std::strlen(type_)), type);
    }

    string_type type() const {
        static const char type_[] = {'t', 'y', 'p', 'e', 0};
        return get_attribute(string_type(type_, type_ + std::strlen(type_)));
    }

    void set_id(const string_type &id) {
        static const char id_[] = {'i', 'd', 0};
        set_attribute(string_type(id_, id_ + std::strlen(id_)), id);
    }

    string_type id() const {
        static const char id_[] = {'i', 'd', 0};
        return get_attribute(string_type(id_, id_ + std::strlen(id_)));
    }

};


typedef basic_message<tags::default_> message;
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_MESSAGE_INC__
