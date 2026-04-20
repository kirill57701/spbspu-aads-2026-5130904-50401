#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "queue.hpp"

namespace petrov {
  template<class T>
  class Queue
  {
    public:
      Queue();
      Queue(Queue&& a);
      Queue(const Queue& a);
      ~Queue();
      void push(T rhs);
      push(const T& val);
      push(T&& value);
      void pop();
      T& front();
      T& back();
      bool empty();
      size_t size();
      T drop();
      Queue& operator=(const Queue& a);
      Queue& operator=(Queue&& a);
      const T& front() const;
      const T& back() const;
      bool empty() const;
      size_t size() const;
      void clear();
      bool operator==(const Queue& a) const;
      bool operator!=(const Queue& a) const;
      void swap(Queue& a) noexcept;
    private:
      petrov::List<T> dat;
  }
}

#endif
