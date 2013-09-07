// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__
#define __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__

#include <future>
#include <memory>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <boost/asio/io_service.hpp>
#include <boost/optional.hpp>
#include "network/http/v2/client/request.hpp"
#include "network/http/v2/client/response.hpp"

namespace network {
  namespace http {
    namespace v2 {
      /**
       * \class client_options network/http/v2/client/client_options.hpp
       * \brief A set of options to configure an HTTP client.
       */
      class client_options {

      public:

	/**
	 * \brief Constructor.
	 */
	client_options()
	  : io_service_(boost::none)
	  , follow_redirects_(false)
	  , cache_resolved_(false)
	  , use_proxy_(false)
	  , timeout_(30000) { }

	/**
	 * \brief Copy constructor.
	 */
	client_options(client_options const &) = default;

	/**
	 * \brief Move constructor.
	 */
	client_options(client_options &&) = default;

	/**
	 * \brief Assignment operator.
	 */
	client_options &operator = (client_options other) {
	  other.swap(*this);
	  return *this;
	}

	/**
	 * \brief Destructor.
	 */
	~client_options() noexcept {

	}

	/**
	 * \brief Swap.
	 */
	void swap(client_options &other) noexcept {
	  std::swap(io_service_, other.io_service_);
	  std::swap(follow_redirects_, other.follow_redirects_);
	  std::swap(cache_resolved_, other.cache_resolved_);
	  std::swap(use_proxy_, other.use_proxy_);
	  std::swap(timeout_, other.timeout_);
	  std::swap(openssl_certificate_paths_, other.openssl_certificate_paths_);
	  std::swap(openssl_verify_paths_, other.openssl_verify_paths_);
	}

	client_options &io_service(boost::asio::io_service &io_service) {
	  io_service_ = io_service;
	}

	boost::optional<boost::asio::io_service &> io_service() const {
	  return io_service_;
	}

	client_options &follow_redirects(bool follow_redirects) noexcept {
	  follow_redirects_ = follow_redirects;
	  return *this;
	}

	bool follow_redirects() const noexcept {
	  return follow_redirects_;
	}

	client_options &cache_resolved(bool cache_resolved) noexcept {
	  cache_resolved_ = cache_resolved;
	  return *this;
	}

	bool cache_resolved() const noexcept {
	  return cache_resolved_;
	}

	client_options &use_proxy(bool use_proxy) noexcept {
	  use_proxy_ = use_proxy;
	  return *this;
	}

	bool use_proxy() const noexcept {
	  return use_proxy_;
	}

	client_options &timeout(std::chrono::milliseconds timeout) noexcept {
	  timeout_ = timeout;
	  return *this;
	}

	std::chrono::milliseconds timeout() const noexcept {
	  return timeout_;
	}

	client_options &openssl_certificate_path(std::string path) {
	  openssl_certificate_paths_.emplace_back(std::move(path));
	  return *this;
	}

	std::vector<std::string> openssl_certificate_paths() const {
	  return openssl_certificate_paths_;
	}

	client_options &openssl_verify_path(std::string path) {
	  openssl_verify_paths_.emplace_back(std::move(path));
	  return *this;
	}

	std::vector<std::string> openssl_verify_paths() const {
	  return openssl_verify_paths_;
	}

      private:

	boost::optional<boost::asio::io_service &> io_service_;
	bool follow_redirects_;
	bool cache_resolved_;
	bool use_proxy_;
	std::chrono::milliseconds timeout_;
	std::vector<std::string> openssl_certificate_paths_;
	std::vector<std::string> openssl_verify_paths_;

      };

      /**
       * \class client client.hpp network/http/v2/client/client.hpp
       * \brief An HTTP client.
       */
      class client {

	client(client const &) = delete;
	client(client &&) = delete;

      public:

	typedef request::string_type string_type;

	/**
	 * Constructor.
	 * \params options Client options.
	 */
	explicit client(client_options options = client_options());

	/**
	 * Destructor.
	 */
	~client() noexcept;

	std::future<response> get(request request_, request_options options = request_options());

	std::future<response> post(request request_, request_options options = request_options());

	std::future<response> put(request request_, request_options options = request_options());

	std::future<response> delete_(request request_, request_options options = request_options());

	std::future<response> head(request request_, request_options options = request_options());

	std::future<response> options(request request_, request_options options = request_options());

      private:

	struct impl;
	impl *pimpl_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CLIENT_INC__
