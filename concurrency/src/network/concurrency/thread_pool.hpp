// Copyright 2010 Dean Michael Berris.
// Copyright 2012 Google, Inc.
// Copyright (c) Glyn Matthews 2012, 2013, 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_CONCURRENCY_THREAD_POOL_INC
#define NETWORK_CONCURRENCY_THREAD_POOL_INC

/**
 * \defgroup concurrency Basic Concurrency Types
 *
 * This module contains a simple concurrency types for use inside the
 * cpp-netlib network libraries.
 *
 * \file
 * \brief Contains a thread_pool type.
 */

#include <cstddef>
#include <thread>
#include <memory>
#include <functional>
#include <vector>
#include <boost/asio/io_service.hpp>

namespace network {
  namespace concurrency {

    typedef std::shared_ptr<boost::asio::io_service> io_service_ptr;
    typedef std::shared_ptr<std::vector<std::thread>> worker_threads_ptr;
    typedef std::shared_ptr<boost::asio::io_service::work> sentinel_ptr;

    /**
     * \ingroup concurrency
     * \class thread_pool network/concurrency/thread_pool.hpp
     * \brief A very simple thread pool.
     */
    class thread_pool {

      thread_pool(thread_pool const&) = delete;
      thread_pool& operator=(thread_pool const&) = delete;

    public:

      /**
       * \brief Constructor.
       * \param thread_count The number of threads in the thread pool.
       * \param io_service An external io_service.
       * \param worker_threads An external thread pool.
       */
      thread_pool(std::size_t thread_count = 1,
		  io_service_ptr io_service = io_service_ptr(),
		  std::vector<std::thread> worker_threads = std::vector<std::thread>());

      /**
       * \brief Move constuctor.
       * \param other The other thread_pool object.
       */
      thread_pool(thread_pool&& other);

      /**
       * \brief Destructor.
       */
      ~thread_pool();

      /**
       * \brief Swap function.
       * \param other The other thread_pool object.
       */
      void swap(thread_pool& other);

      /**
       * \brief Move assignment operator.
       * \param other The other thread_pool object.
       */
      thread_pool& operator=(thread_pool&& other);

      /**
       * \brief Returns the number of threads in the thread pool.
       * \returns The number of threads in the thread pool.
       */
      std::size_t const thread_count() const;

      /**
       * \brief Posts a task to the thread pool.
       * \param task The task to be executed.
       */
      void post(std::function<void()> task);

    private:

      struct impl;
      impl* pimpl_;

    };

    inline
    void swap(thread_pool& l, thread_pool& r) {
      l.swap(r);
    }

  }  // namespace concurrency
}  // namespace network

#endif // NETWORK_CONCURRENCY_THREAD_POOL_INC
