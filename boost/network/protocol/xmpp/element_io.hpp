//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_ELEMENT_IO_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_ELEMENT_IO_INC__


# include <boost/network/protocol/xmpp/element.hpp>
# include <ostream>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag
    >
std::ostream &operator << (std::ostream &os,
                           const basic_element<Tag> &element) {
    if (element.is_tag()) {
        os << "<" << element.get_name();
        boost::iterator_range<typename basic_element<Tag>::headers_container_type::const_iterator>
            attributes(element.get_attributes());

        typename basic_element<Tag>::headers_container_type::const_iterator
            attr_it(boost::begin(attributes)),
            attr_end(boost::end(attributes));
        for (; attr_it != attr_end; ++attr_it) {
            os << " " << attr_it->first << "=\"" << attr_it->second << "\"";
        }
        os << ">";

        boost::iterator_range<typename basic_element<Tag>::element_children_type::const_iterator>
            children(element.get_children());
        
        typename basic_element<Tag>::element_children_type::const_iterator
            child_it(boost::begin(children)),
            child_end(boost::end(children));
        for (; child_it != child_end; ++child_it) {
            os << **child_it;
        }
        os << "</" << element.get_name() << ">";
    }
    else {
        os << element.get_text().get();
    }
    return os;
}
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_ELEMENT_IO_INC__
