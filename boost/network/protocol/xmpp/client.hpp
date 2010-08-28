//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_CLIENT_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_CLIENT_INC__


# include <boost/utility/noncopyable.hpp>
# include <boost/network/traits/string.hpp>
# include <boost/cstdint.hpp>
# include <boost/network/protocol/xmpp/message.hpp>
# include <boost/network/protocol/xmpp/presence.hpp>
# include <boost/network/protocol/xmpp/iq.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Handler,
    class Tag
    >
class basic_client : boost::noncopyable {
public:

    typedef typename string<Tag>::type string_type;
    
    typedef basic_message<Tag> message;
    typedef basic_presence<Tag> presence;
    typedef basic_iq<Tag> iq;
    
    explicit basic_client(Handler handler);

    ~basic_client();

    void connect(const string_type &proxy_host,
                 const string_type &proxy_port);

    void disconnect();

    void authenticate(const string_type &jid,
                      const string_type &password);

    void send_message(const message_type &message);

    void send_presence(const presence_type &presence);

    void send_iq(const iq_type &iq);

    string_type jid() const;

    string_type bound_jid() const;

private:

    // tcp socket
    // tls
    // sasl

    // parameters, such as jid, bound_jid, domain, port etc.

    // io_service

    // xml parser

    // event handler

    // stream open handler

    // connection event handlers
    
    Handler handler_;

};



template <
    class Handler
    >
struct client : basic_client<tags::default_> {

    explicit client(Handler handler) : basic_client<tags::default_>(handler) {
        
    }

};
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_CLIENT_INC__
