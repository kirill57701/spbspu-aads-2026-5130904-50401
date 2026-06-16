#ifndef PANDAS_HPP
#define PANDAS_HPP
#include "list.hpp"
#include <string>
#include <fstream>

namespace petrov
{
  size_t how_c(std::string i)
  {
    size_t s = 0;
    for (size_t j = 0; j < i.size(); ++j)
    {
      s += (i[j] == ',');
    }
    return s + 1;
  }
  List<std::string> toma(std::string i)
  {
    std::string s = "";
    List<std::string> d;
    for (size_t j = 0; j < s.size(); ++j)
    {
      if (i[j] == ',')
      {
        d.push_back(s);
        s = "";
      }
      else
      {
        s += i[j];
      }
    }
    d.push_back(s);
    return d;
  }
  struct dataset
  {
    void read_dataset(std::istream& in)
    {
      std::string s;
      in >> s;
      std::ifstream i;
      i.open(s);
      if (i.is_open())
      {
        std::string q;
        c = how_c(q);
        size_t r1 = 0;
        while (std::getline(i, q))
        {
          if (r1 > 0)
          {
            data.push_back()
          }
          r1++;
        }
        r = r1;
      }
      else
      {
        throw std::logic_error("err\n");
      }
    }
    private:
      size_t c, r;
      List<List<std::string>> data;
  };
}

#endif
