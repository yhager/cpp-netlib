//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_AUTH_SASL_INC__
# define __BOOST_NETWORK_AUTH_SASL_INC__


# include <boost/network/traits/string.hpp>


namespace boost {
namespace network {
namespace auth {
template <
    class Tag
    >
class basic_sasl {

    // struct anonymous {};
    // struct plain {};
    // struct digest_md5 {};

public:

    typedef typename string<Tag>::type string_type;

    // explicit basic_sasl(anonymous);
    // 
    // explicit basic_sasl(plain,
    //                     const string_type &id, const string_type &password);
    // 
    // explicit basic_sasl(digest_md5,
    //                     const string_type &challenge,const string_type &jid, const string_type &password);

private:

    string_type auth_string_;
    
};
} // namespace auth
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_AUTH_SASL_INC__
