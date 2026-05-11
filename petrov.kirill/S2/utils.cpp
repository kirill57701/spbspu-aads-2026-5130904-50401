#include "utils.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include <limits>
#include <stdexcept>

namespace petrov
{
  size_t prior(char s)
  {
    if (s == '+' || s == '-')
    {
      return 2;
    }
    else if (s == '*' || s == '/' || s == '%')
    {
      return 3;
    }
    if (s == '&')
    {
      return 1;
    }
    return 0;
  }

  long long int oper(long long int a, long long int b, char s)
  {
    if (s != '/' && s != '%')
    {
      return (s == '+' ? a + b : (s == '-' ? a - b : (s == '*' ? a*b : a & b)));
    }
    if (s == '/')
    {
      if (b == 0)
      {
	throw std::logic_error("err\n");
      }
      return a/b;
    }
    if (s == '%')
    {
      if (b == 0)
      {
        throw std::logic_error("err\n");
      }
      return a%b;
    }
    throw std::logic_error("err\n");
  }

  size_t isOp(char s)
  {
    return s == '+' || s == '-' || s == '*' || s == '%' || s == '/' || s == '&';
  }
}
