//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_DETAIL_XML_WRAPPERS_PARSER_BACKENDS_LIBXML2_PARSER_INC__
# define __BOOST_NETWORK_DETAIL_XML_WRAPPERS_PARSER_BACKENDS_LIBXML2_PARSER_INC__


# include <boost/network/traits/string.hpp>
# include <boost/network/detail/xml_wrappers/element.hpp>
# include <libxml/parser.h>
# include <libxml/tree.h>
# include <stack>


namespace boost {
namespace network {
namespace detail {
template <
    class Tag
    >
class basic_libxml2_parser {

public:

    typedef typename string<Tag>::type string_type;

    typedef basic_element<Tag> element_type;

    basic_libxml2_parser() {
        std::memset(&handlers_, 0, sizeof(xmlSAXHandler));
        handlers_.startElement = start_element;
        handlers_.endElement = end_element;
        handlers_.characters = characters;
        depth_ = 0;
        
        context_ = xmlCreatePushParserCtxt(&handlers_, 
                                           this, 0, 0, 0);
        // assert(!context_);
    }

    ~basic_libxml2_parser() {
        xmlFreeParserCtxt(context_);
    }

    bool feed(const string_type &chunk) {
        while (!elements_.empty()) {
            elements_.pop();
        }
        elements_.push(0);
        depth_ = 0;
        return xmlParseChunk(context_, chunk.c_str(), chunk.size(), 0);
    }

    bool feed(const string_type &chunk, element_type &element) {
        while (!elements_.empty()) {
            elements_.pop();
        }
        elements_.push(&element);
        depth_ = 0;
        return xmlParseChunk(context_, chunk.c_str(), chunk.size(), 0);
    }

private:

    static void set_name(element_type *element, const xmlChar *name) {
        const xmlChar *name_begin = name;
        const xmlChar *name_end = name_begin + xmlStrlen(name_begin);
        element->set_name(string_type(name_begin, name_end));
    }

    static void set_attributes(basic_element<Tag> *element, const xmlChar **attrs) {
        if (attrs) {
            for (int i = 0; attrs[i]; i += 2) {
                const xmlChar *key_begin = attrs[i];
                const xmlChar *key_end = key_begin + xmlStrlen(key_begin);

                const xmlChar *val_begin = attrs[i + 1];
                const xmlChar *val_end = val_begin + xmlStrlen(val_begin);

                element->set_attribute(string_type(key_begin, key_end),
                                       string_type(val_begin, val_end));
            }
        }
    }

    static void start_element(void *userdata,
                              const xmlChar *name,
                              const xmlChar **attrs) {
        basic_libxml2_parser<Tag> *parser
            = static_cast<basic_libxml2_parser<Tag> *>(userdata);

        if (!parser->elements_.top()) {
            return;
        }

        else if (parser->depth_ > 0) {
            element_type *child = new element_type;
            parser->elements_.top()->add_child(child);
            parser->elements_.push(child);
        }
        set_name(parser->elements_.top(), name);
        set_attributes(parser->elements_.top(), attrs);
        
        ++parser->depth_;
    }

    static void end_element(void *userdata,
                            const xmlChar *name) {
        basic_libxml2_parser<Tag> *parser
            = static_cast<basic_libxml2_parser<Tag> *>(userdata);
        
        if (!parser->elements_.top()) {
            return;
        }

        if (parser->depth_ > 0) {
            parser->elements_.pop();
        }

        --parser->depth_;
    }

    static void characters(void *userdata,
                           const xmlChar *s,
                           int len) {
        basic_libxml2_parser<Tag> *parser
            = static_cast<basic_libxml2_parser<Tag> *>(userdata);
        
        if (!parser->elements_.top()) {
            return;
        }

        parser->elements_.top()->add_child(
            new element_type(typename element_type::text(), string_type(s, s + len)));
    }
    
    xmlParserCtxtPtr context_;
    xmlSAXHandler handlers_;
    std::stack<element_type *> elements_;
    int depth_;
    
};
} // namespace detail
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_DETAIL_XML_WRAPPERS_PARSER_BACKENDS_LIBXML2_PARSER_INC__
