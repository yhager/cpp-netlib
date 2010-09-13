//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_DETAIL_STANZA_PARSER_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_DETAIL_STANZA_PARSER_INC__


# include <boost/network/detail/xml_wrappers/traits/parser_backend.hpp>
# include <boost/network/detail/xml_wrappers/parser_backends/expat_parser.hpp>
# include <boost/network/protocol/xmpp/stanza.hpp>
# include <boost/network/traits/string.hpp>



namespace boost {
namespace network {
namespace xmpp {
namespace detail {
template <
    class Tag
    >
class basic_stanza_parser {
public:

    typedef basic_stanza<Tag> stanza_type;
    typedef typename string<Tag>::type string_type;
    typedef typename boost::network::detail::parser_backend<Tag>::type parser_type;

    basic_stanza_parser() {
        
    }

    ~basic_stanza_parser() {
        
    }

    bool feed(const string_type &chunk) {
        parser_.feed(chunk);
    }

    bool feed(const string_type &chunk, stanza_type &stanza) {
        parser_.feed(chunk, &stanza.element());
    }

private:
    
    parser_type parser_;
    
};
} // namespace detail
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_DETAIL_STANZA_PARSER_INC__
