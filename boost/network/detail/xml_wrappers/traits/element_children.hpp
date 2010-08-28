//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_DETAIL_XML_WRAPPERS_TRAITS_ELEMENT_CHILDREN_INC__
# define __BOOST_NETWORK_DETAIL_XML_WRAPPERS_TRAITS_ELEMENT_CHILDREN_INC__


# include <boost/network/tags.hpp>
# include <boost/shared_ptr.hpp>
# include <list>


namespace boost {
namespace network {
namespace detail {
template <
    class Tag
    >
class basic_element;


template <
    class Tag
    >
struct element_children {
    typedef unsupported_tag<Tag> type;
};


template <>
struct element_children<tags::default_> {
    typedef std::list<boost::shared_ptr<basic_element<tags::default_> > > type;
};
} // namespace detail
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_DETAIL_XML_WRAPPERS_TRAITS_ELEMENT_CHILDREN_INC__
