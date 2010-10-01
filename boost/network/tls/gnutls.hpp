//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_TLS_GNUTLS_INC__
# define __BOOST_NETWORK_TLS_GNUTLS_INC__


# include <boost/network/traits/string.hpp>
# include <gnutls/gnutls.h>


namespace boost {
namespace network {
template <
    class Tag
    >
basic_gnutls {
public:

    typedef typename string<Tag>::type string_type;

    basic_gnutls();

    ~basic_gnutls();

private:

    gnutls_session_t session_;
    gnutls_certificate_credentials_t credentials_;
    
};


template <
    class Tag
    >
basic_gnutls<Tag>::basic_gnutls() {
    
}

template <
    class Tag
    >
basic_gnutls<Tag>::~basic_gnutls() {
    
}
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_TLS_GNUTLS_INC__
