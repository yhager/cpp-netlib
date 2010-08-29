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
    
    typedef basic_message<Tag> message_type;
    typedef basic_presence<Tag> presence_type;
    typedef basic_iq<Tag> iq_type;
    
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

private:

    void handle_stream_start();
    void handle_stream_stanza();
    void handle_stream_end();

    // tcp socket
    // tls
    // sasl

    // parameters, such as jid, domain, port etc.
    string_type jid_;

    // io_service
    boost::asio::io_service io_service_;

    // xml parser

    Handler handler_;

};


template <
    class Tag,
    class Handler
    >
basic_client<Tag, Hander>::basic_client(Handler handler) {
    // set the handlers
}

template <
    class Tag,
    class Handler
    >
basic_client<Tag, Hander>::~basic_client() {
    
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Hander>::connect(const string_type &proxy_host,
                                        const string_type &proxy_port) {
    // get the JID domain
    // default port is 52222
    // open socket
    // socket has a state
    // signal connection handler
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Hander>::disconnect() {
    // close socket
    // signal connection handler
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Hander>::authenticate(const string_type &jid,
                                             const string_type &password) {
    
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Hander>::send_message(const message_type &message) {
    
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Hander>::send_presence(const presence_type &presence) {
    
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Hander>::send_iq(const iq_type &iq) {
    
}

template <
    class Tag,
    class Handler
    >
basic_client<Tag, Handler>::string_type
basic_client<Tag, Hander>::jid() const {
    return jid_;
}


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
