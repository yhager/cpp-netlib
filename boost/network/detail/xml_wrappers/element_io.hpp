//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_DETAIL_XML_WRAPPERS_ELEMENT_IO_INC__
# define __BOOST_NETWORK_DETAIL_XML_WRAPPERS_ELEMENT_IO_INC__


# include <boost/network/detail/xml_wrappers/element.hpp>
# include <boost/range/algorithm_ext/for_each.hpp>
# include <boost/spirit/home/phoenix/core.hpp>
# include <ostream>


namespace boost {
namespace network {
namespace detail {
template <
    class Tag
    >
std::ostream &operator << (std::ostream &os,
                           const basic_element<Tag> &element) {
    typedef typename basic_element<Tag>::headers_container_type::const_iterator header_iterator;
    typedef typename basic_element<Tag>::element_children_type::const_iterator children_iterator;
    typedef boost::iterator_range<header_iterator> header_range;
    typedef boost::iterator_range<children_iterator> children_range;
    
    if (element.is_tag()) {
        os << "<" << element.get_name();
        header_range attributes(element.get_attributes());
        
        header_iterator attr_it(boost::begin(attributes)), attr_end(boost::end(attributes));
        for (; attr_it != attr_end; ++attr_it) {
            os << " " << attr_it->first << "='" << attr_it->second << "'";
        }
        os << ">";

        children_range children(element.get_children());
        
        children_iterator child_it(boost::begin(children)), child_end(boost::end(children));
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
} // namespace detail
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_DETAIL_XML_WRAPPERS_ELEMENT_IO_INC__
