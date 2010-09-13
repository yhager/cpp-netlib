//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_PROTOCOL_XMPP_CLIENT_INC__
# define __BOOST_NETWORK_PROTOCOL_XMPP_CLIENT_INC__


# include <boost/noncopyable.hpp>
# include <boost/network/traits/string.hpp>
# include <boost/cstdint.hpp>
# include <boost/bind.hpp>
# include <boost/network/protocol/xmpp/message.hpp>
# include <boost/network/protocol/xmpp/presence.hpp>
# include <boost/network/protocol/xmpp/iq.hpp>
# include <boost/asio/io_service.hpp>
# include <boost/asio/ip/tcp.hpp>


namespace boost {
namespace network {
namespace xmpp {
template <
    class Tag,
    class Handler
    >
class basic_client : boost::noncopyable {

private:

    typedef basic_client<Tag, Handler> this_type;
    
public:

    typedef typename string<Tag>::type string_type;
    
    typedef basic_message<Tag> message_type;
    typedef basic_presence<Tag> presence_type;
    typedef basic_iq<Tag> iq_type;
    
    explicit basic_client(Handler &handler);

    ~basic_client();

    void connect(const string_type &proxy_host,
                 const string_type &proxy_port);

    void disconnect();

    void authenticate(const string_type &jid,
                      const string_type &password);

    void send_message(const message_type &message);

    void send_presence(const presence_type &presence);

    void send_iq(const iq_type &iq);

    void set_jid(const string_type &jid);

    string_type get_jid() const;

private:

    void write_stanza(const basic_stanza<Tag> &stanza);
    void close_socket();

    Handler &handler_;

    // io_service
    boost::asio::io_service io_service_;

    // tcp socket
    boost::asio::ip::tcp::socket socket_;
    
    // tls
    // sasl

    // parameters, such as jid, domain, port etc.
    string_type jid_;

    // xml parser

};


template <
    class Tag,
    class Handler
    >
basic_client<Tag, Handler>::basic_client(Handler &handler)
    : handler_(handler), socket_(io_service_) {
    // set the handlers
}


template <
    class Tag,
    class Handler
    >
basic_client<Tag, Handler>::~basic_client() {
    
}


template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::connect(const string_type &proxy_host,
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
void basic_client<Tag, Handler>::disconnect() {
    // close socket
    // signal connection handler
    io_service_.post(
        boost::bind(&this_type::close_socket, this));
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::authenticate(const string_type &jid,
                                              const string_type &password) {
    
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::send_message(const message_type &message) {
    io_service_.post(
        boost::bind(&this_type::write_stanza, this, boost::ref(message)));
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::send_presence(const presence_type &presence) {
    io_service_.post(
        boost::bind(&this_type::write_stanza, this, boost::ref(presence)));
}

template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::send_iq(const iq_type &iq) {
    io_service_.post(
        boost::bind(&this_type::write_stanza, this, boost::ref(iq)));
}

template <
    class Tag,
    class Handler
    >
typename basic_client<Tag, Handler>::string_type
basic_client<Tag, Handler>::get_jid() const {
    return jid_;
}


template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::write_stanza(const basic_stanza<Tag> &stanza) {
    
}


template <
    class Tag,
    class Handler
    >
void basic_client<Tag, Handler>::close_socket() {
    socket_.close();
}


template <
    class Handler
    >
struct client : basic_client<tags::default_, Handler> {

    explicit client(Handler &handler)
        : basic_client<tags::default_, Handler>(handler) {
        
    }

};
} // namespace xmpp
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_PROTOCOL_XMPP_CLIENT_INC__
