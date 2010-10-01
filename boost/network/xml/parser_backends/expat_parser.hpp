//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_XML_PARSER_BACKENDS_EXPAT_PARSER_INC__
# define __BOOST_NETWORK_XML_PARSER_BACKENDS_EXPAT_PARSER_INC__


# include <boost/network/traits/string.hpp>
# include <boost/network/xml/element.hpp>
# include <boost/noncopyable.hpp>
# include <expat.h>
# include <cstring>
# include <stack>


namespace boost {
namespace network {
namespace detail {
template <
    class Tag
    >
class basic_expat_parser : boost::noncopyable {
public:

    typedef typename string<Tag>::type string_type;

    typedef basic_element<Tag> element_type;

    basic_expat_parser()
        : parser_(XML_ParserCreate(NULL)), depth_(0) {
        assert(parser_);
        XML_SetUserData(parser_, this);
        XML_SetElementHandler(parser_, start_element, end_element);
        XML_SetCharacterDataHandler(parser_, cdata);
    }

    ~basic_expat_parser() {
        XML_ParserFree(parser_);
    }
    
    bool feed(const string_type &chunk) {
        while (!elements_.empty()) {
            elements_.pop();
        }
        elements_.push(0);
        depth_ = 0;
        return XML_Parse(parser_, chunk.c_str(), chunk.size(), 0) != 0;
    }
    
    bool feed(const string_type &chunk, element_type &element) {
        while (!elements_.empty()) {
            elements_.pop();
        }
        elements_.push(&element);
        depth_ = 0;
        return XML_Parse(parser_, chunk.c_str(), chunk.size(), 0) != 0;
    }

private:

    static void set_name(element_type *element, const XML_Char *name) {
        const XML_Char *name_begin = name;
        const XML_Char *name_end = name_begin + std::strlen(name_begin);

        element->set_name(string_type(name_begin, name_end));
    }

    static void set_attributes(element_type *element, const XML_Char **attrs) {
        if (attrs) {
            for (int i = 0; attrs[i]; i += 2) {
                const XML_Char *key_begin = attrs[i];
                const XML_Char *key_end = key_begin + std::strlen(key_begin);

                const XML_Char *val_begin = attrs[i + 1];
                const XML_Char *val_end = val_begin + std::strlen(val_begin);

                element->set_attribute(string_type(key_begin, key_end),
                                       string_type(val_begin, val_end));
            }
        }
    }

    static void start_element(void *userdata,
                              const XML_Char *name,
                              const XML_Char **attrs) {
        basic_expat_parser<Tag> *parser
            = static_cast<basic_expat_parser<Tag> *>(userdata);
        
        if (!parser->elements_.top()) {
            return;
        }

        if (parser->depth_ > 0) {
            element_type *child = new element_type;
            parser->elements_.top()->add_child(child);
            parser->elements_.push(child);
        }
        set_name(parser->elements_.top(), name);
        set_attributes(parser->elements_.top(), attrs);

        ++parser->depth_;
    }

    static void end_element(void *userdata,
                            const XML_Char *name) {
        basic_expat_parser<Tag> *parser
            = static_cast<basic_expat_parser<Tag> *>(userdata);
        
        if (!parser->elements_.top()) {
            return;
        }

        if (parser->depth_ > 0) {
            parser->elements_.pop();
        }

        --parser->depth_;
    }

    static void cdata(void *userdata,
                      const XML_Char *s,
                      int len) {
        basic_expat_parser<Tag> *parser
            = static_cast<basic_expat_parser<Tag> *>(userdata);
        
        if (!parser->elements_.top()) {
            return;
        }

        parser->elements_.top()->add_child(
            new element_type(typename element_type::text(), string_type(s, s + len)));
    }

    XML_Parser parser_;
    std::stack<element_type *> elements_;
    int depth_;

};
} // namespace detail
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_XML_PARSER_BACKENDS_EXPAT_PARSER_INC__
