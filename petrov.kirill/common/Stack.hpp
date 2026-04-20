#ifndef STACK_HPP
#define STACK_HPP
#include "Queue.hpp"

namespace petrov
{
  template<class T>
  class Stack
  {
    public:
      Stack() = default;
      Stack(Stack&& a) = default;
      Stack(const Stack& a) = default;
      ~Stack();

      void push(T rhs);
      void push(T&& rhs);
      void pop();
      T drop();

      T top();
      const T& top() const;

      bool empty() const;
      size_t size() const;
      void clear();

      Stack& operator=(const Stack& a);
      Stack& operator=(Stack&& a);
      bool operator==(const Stack& a) const;
      bool operator!=(const Stack& a) const;

    private:
      petrov::List<T> dat;
  };

  template<class T>
  void Stack<T>::push(const T& val) {
    dat.push_front(val);
  }

  template<class T>
  void Stack<T>::push(T&& val) {
    dat.push_front(std::move(val));
  }

  template<class T>
  void Stack<T>::pop() {
    if (dat.IsEmpty()) {
      throw std::logic_error("err");
    }
    dat.pop_front();
  }
}



#endif
