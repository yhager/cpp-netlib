//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_STANZA_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_STANZA_INC__


# include <boost/network/message.hpp>
# include <boost/network/detail/xml_wrappers/element.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag
    >
class basic_stanza
    : public boost::network::basic_message<Tag> {

    typedef boost::network::basic_message<Tag> base_type;
    
public:

    typedef typename base_type::string_type string_type;

    explicit basic_stanza() {
        
    }

    explicit basic_stanza(const string_type &name) {
        element_.set_name(name);
    }

    void set_name(const string_type &name) {
        element_.set_name(name);
    }

    string_type get_name() const {
        return element_.get_name();
    }

    void set_attribute(const string_type &key, const string_type &value) {
        element_.set_attribute(key, value);
    }

    string_type get_attribute(const string_type &key) const {
        boost::optional<string_type> attr = element_.get_attribute(key);
        return attr? *attr : string_type();
    }

    detail::basic_element<Tag> &element() {
        return element_;
    }

private:

    detail::basic_element<Tag> element_;
    
};


typedef basic_stanza<tags::default_> stanza;
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_STANZA_INC__
