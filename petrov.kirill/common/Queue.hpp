#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "queue.hpp"

namespace petrov {
  template<class T>
  class Queue
  {
    public:
      Queue() = default;
      Queue(Queue&& a) = default;
      Queue(const Queue& a) = default;
      ~Queue() = default;

      void push(T rhs);
      void push(const T& a);
      void push(T&& a);

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
  };
}

template<class T>
void petrov::Queue<T>::push(T rhs)
{
  dat.push_back(rhs);
}

template<class T>
void petrov::Queue<T>::push(const T& a)
{
  dat.push_back(a);
}

template<class T>
void petrov::Queue<T>::push(T&& a)
{
  dat.push_back(std::move(a));
}

#endif
