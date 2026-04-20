#ifndef STACK_HPP
#define STACK_HPP
#include "Queue.hpp"

namespace petrov
{
  template<class T>
  class Stack
  {
    public:
      void push(T rhs);
      T drop();
  };
}
