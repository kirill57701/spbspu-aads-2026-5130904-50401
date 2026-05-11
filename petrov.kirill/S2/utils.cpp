#include "utils.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include <limits>
#include <stdexcept>
#include <string>

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

  petrov::Stack<long long int> calcStream(std::istream& in)
  {
    petrov::Stack<long long int> res;
    std::string s;
    while (std::getline(in, s))
    {
      if (!s.empty())
      {
        petrov::Queue<std::string> post;
        petrov::Stack<char> c;
        for (size_t i = 0; i < s.size(); ++i)
        {
          if (s[i] != ' ')
          {
	    if (std::isdigit(s[i]))
	    {
	      std::string n = "";
	      while (i < s.size() && std::isdigit(s[i]))
    	      {
		n += s[i++];
	      }
	      post.push(n);
  	      --i;
 	    }
  	    else if (s[i] == '(')
  	    {
	      c.push(s[i]);
	    }
 	    else if (s[i] == ')')
	    {
	      while (!c.empty() && c.top() != '(')
	      {
		std::string q = "";
 		q += c.drop();
		post.push(q);
	      }
	      if (c.empty())
	      {
		throw std::logic_error("err\n");
	      }
	      c.pop();
	    }
	    else if (isOp(s[i]))
	    {
	      while (!c.empty() && prior(c.top()) >= prior(s[i]))
	      {
		std::string q = "";
		q += c.drop();
		post.push(q);
	      }
	      c.push(s[i]);
	    }
          }
        }
	while (!c.empty())
        {
          if (c.top() == '(')
	  {
	    throw std::logic_error("err\n");
          }
	  std::string q = "";
          q += c.drop();
          post.push(q);
        }

	petrov::Stack<long long int> b;
        while (!post.empty())
        {
          std::string t = post.drop();
          if (std::isdigit(t[0]))
          {
            b.push(std::stoll(t));
          }
          else
          {
            if (b.size() < 2)
	    {
	      throw std::logic_error("err\n");
            }
	    long long int b1 = b.drop();
            long long int a = b.drop();
            b.push(oper(a, b1, t[0]));
          }
        }
        if (b.size() != 1)
	{
	  throw std::logic_error("err\n");
        }
	res.push(b.drop());
      }
    }
    return res;
  }
}
