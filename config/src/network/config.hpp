// Copyright (c) Glyn Matthews 2012, 2013.
// Copyright 2012 Dean Michael Berris <dberris@google.com>
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef NETWORK_CONFIG_INC
#define NETWORK_CONFIG_INC

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(BOOST_ALL_DYN_LINK)
#define NETWORK_DECL BOOST_SYMBOL_EXPORT
#else
#define NETWORK_DECL
#endif // defined(BOOST_ALL_DYN_LINK)

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
#define NETWORK_DEFAULTED_FUNCTION {}
#else
#define NETWORK_DEFAULTED_FUNCTION = default
#endif // defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)

#if defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#define NETWORK_DELETED_FUNCTION {}
#else
#define NETWORK_DELETED_FUNCTION = delete
#endif // defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)

#if defined(BOOST_NO_CXX11_NOEXCEPT)
#define NETWORK_NOEXCEPT throw()
#else
#define NETWORK_NOEXCEPT noexcept
#endif // defined(BOOST_NO_CXX11_NOEXCEPT)

#if defined(BOOST_NO_CXX11_OVERRIDE)
#define NETWORK_OVERRIDE
#else
#define NETWORK_OVERRIDE override
#endif // defined(BOOST_NO_CXX11_OVERRIDE)

#endif // NETWORK_CONFIG_INC
