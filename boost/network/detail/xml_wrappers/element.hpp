//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_DETAIL_XML_WRAPPERS_ELEMENT_INC__
# define __BOOST_NETWORK_DETAIL_XML_WRAPPERS_ELEMENT_INC__


# include <boost/network/traits/string.hpp>
# include <boost/network/traits/headers_container.hpp>
# include <boost/network/detail/xml_wrappers/traits/element_children.hpp>
# include <boost/network/detail/xml_wrappers/traits/parser_backend.hpp>
# include <boost/network/tags.hpp>
# include <boost/optional.hpp>
# include <boost/range/iterator_range.hpp>
# include <algorithm>
# include <cassert>


namespace boost {
namespace network {
namespace detail {
template <
    class Tag
    >
class basic_element {

public:

    struct tag {};
    struct text {};

    typedef typename string<Tag>::type string_type;
    typedef typename headers_container<Tag>::type headers_container_type;
    typedef typename element_children<Tag>::type element_children_type;

    basic_element() {
        
    }

    basic_element(tag, const string_type &name)
        : name_(name) {
        
    }

    basic_element(text, const string_type &text)
        : text_(text) {
        
    }

    basic_element(const basic_element &other)
        : name_(other.name_),
          attributes_(other.attributes_),
          children_(other.children_),
          text_(other.text_) {
        
    }

    basic_element &operator = (const basic_element &other) {
        basic_element tmp(other);
        swap(tmp);
        return *this;
    }

    ~basic_element() {
        
    }

    void swap(basic_element &other) {
        std::swap(name_, other.name_);
        std::swap(attributes_, other.attributes_);
        std::swap(children_, other.children_);
        std::swap(text_, other.text_);
    }

    void set_name(const string_type &name) {
        assert(!is_text());
        name_ = name;
    }

    string_type get_name() const {
        assert(is_tag());
        return name_;
    }

    void set_text(const string_type &text) {
        assert(!is_tag());
        text_ = text;
    }
    
    boost::optional<string_type> get_text() const {
        assert(is_text());
        return text_.get();
    }

    bool is_tag() const {
        return !name_.empty();
    }

    bool is_text() const {
        return static_cast<bool>(text_);
    }

    void set_attribute(const string_type &name, const string_type &value) {
        assert(is_tag());
        attributes_.insert(typename headers_container_type::value_type(name, value));
    }

    boost::optional<string_type> get_attribute(const string_type &name) const {
        typename headers_container_type::const_iterator it = attributes_.find(name);
        if (it != attributes_.end()) {
            return it->second;
        }
        return boost::none;
    }

    boost::iterator_range<typename headers_container_type::const_iterator>
    get_attributes() const {
        return boost::make_iterator_range(boost::begin(attributes_),
                                          boost::end(attributes_));
    }

    boost::optional<string_type> get_namespace() const {
        return get_attribute("xmlns");
    }

    boost::optional<string_type> get_type() const {
        return get_attribute("type");
    }

    boost::optional<string_type> get_lang() const {
        boost::optional<string_type> lang
            = get_attribute("xml:lang");
        if (!lang) {
            lang = get_attribute("lang");
        }
        return lang;
    }

    boost::optional<string_type> get_id() const {
        return get_attribute("id");
    }

    void add_child(basic_element<Tag> *element) {
        assert(is_tag());
        boost::shared_ptr<basic_element<Tag> > shared_element(element);
		children_.push_back(shared_element);
    }

    boost::optional<const basic_element<Tag> &> get_child(const string_type &name) const {
        for (typename element_children_type::const_iterator it = children_.begin();
             it != children_.end();
             ++it) {
            if ((*it)->get_name() == name) {
                return **it;
            }
        }
        return boost::none;
    }

    boost::iterator_range<typename element_children_type::const_iterator>
    get_children() const {
        return boost::make_iterator_range(boost::begin(children_),
                                          boost::end(children_));
    }

private:

    // if it's a tag node
    string_type name_;
    headers_container_type attributes_;
    element_children_type children_;

    // if it's a text node
    boost::optional<string_type> text_;

};


typedef basic_element<boost::network::tags::default_> element;
} // namespace detail
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_DETAIL_XML_WRAPPERS_ELEMENT_INC__
