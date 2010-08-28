//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_STANZA_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_STANZA_INC__


# include <boost/network/message.hpp>


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

    void set_name(const string_type &name) {
        name_ = name;
    }

    string_type name() const {
        return name_;
    }

    void set_attribute(const string_type &key, const string_type &value) {
        this->headers().insert(std::make_pair(key, value));
    }

    string_type attribute(const string_type &key) const {
        typename headers_range<basic_stanza<Tag> >::type range
            = this->headers().equal_range(key);
        if (boost::begin(range) == boost::end(range)) {
            return string_type();
        }

        return boost::begin(range)->second;
    }

private:

    string_type name_;
    
};


typedef basic_stanza<tags::default_> stanza;
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_STANZA_INC__
