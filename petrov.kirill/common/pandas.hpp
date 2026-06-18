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
    for (size_t j = 0; j < i.size(); ++j)
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
  List<double> convert(List<std::string> l)
  {
    List<double> r;
    for (LIter<std::string> i = l.begin(); i != l.end(); ++i)
    {
      r.push_back(std::stod(*i));
    }
    return r;
  }
  std::pair<List<List<double>>, List<double>> data_train_test_split(List<List<double>> inp, size_t i)
  {
    List<List<double>> l1;
    List<double> l2;
    for (LIter<List<double>> li = inp.begin(); li != inp.end(); ++li)
    {
      size_t n = 0;
      List<double> l12;
      for (LIter<double> lii = (*li).begin(); lii != (*li).end(); ++lii, ++n)
      {
        if (n != i)
        {
          l12.push_back(*lii);
        }
        else
        {
          l2.push_back(*lii);
        }
      }
      l1.push_back(l12);
    }
    return {l1, l2};
  }
  struct dataset
  {
    void data_head(size_t n)
    {
      LIter<List<std::string>> d = data.begin();
      for (size_t i = 0; i < data.getSize() && i < n; ++i, ++d)
      {
        LIter<std::string> q = (*d).begin();
        for (size_t j = 0; j < c; ++j, ++q)
        {
          std::cout << ' ' << (*q) << ' ';
        }
        std::cout << '\n';
      }
    }
    void read_dataset(std::istream& in)
    {
      std::string s;
      in >> s;
      std::ifstream i;
      i.open(s);
      if (i.is_open())
      {
        std::string q;
        std::getline(i, q);
        c = how_c(q);
        noname = q;
        name_data = s;
        size_t r1 = 0;
        while (std::getline(i, q))
        {
          data.push_back(toma(q));
          r1++;
        }
        r = r1;
      }
      else
      {
        throw std::logic_error("err\n");
      }
    }
    void save_data(std::istream& in)
    {
      std::string s;
      in >> s;
      bool norm = 0;
      for (size_t i = 0; i < s.size(); ++i)
      {
        if (s[i] == '.')
        {
          norm = 1;
          break;
        }
      }
      if (!norm)
      {
        s += ".data";
      }
      std::ofstream out;
      out.open(s);
      std::string wh = "";
      for (size_t i = 0; i < noname.size(); ++i)
      {
        if (noname[i] == ',')
        {
          out << wh << ',';
          wh = "";
        }
        else
        {
          wh += noname[i];
        }
      }
      out << wh;
      for (LIter<List<std::string>> d = data.begin(); d != data.end(); ++d)
      {
        for (LIter<std::string> q = (*d).begin(); q != (*d).end(); ++q)
        {
          out << (*q);
          if ((++q) != ((*d).end()))
          {
            out << ',';
          }
          --q;
        }
        out << '\n';
      }
    }
    void feature_del(std::string s)
    {
      List<std::string> f;
      std::string d = "";
      for (size_t i = 0; i < noname.size(); ++i)
      {
        if (noname[i] == ',')
        {
          f.push_back(d);
          d = "";
        }
        else
        {
          d += noname[i];
        }
      }
      f.push_back(d);
      size_t n_r = 0, n = 0;
      for (LIter<std::string> fi = f.begin(); fi != f.end(); ++fi, ++n_r)
      {
        if (*fi == s)
        {
          n = 1;
          break;
        }
      }
      if (!n)
      {
        throw std::logic_error("err\n");
      }
      else
      {
        List<List<std::string>> datan;
        LIter<List<std::string>> di = data.begin();
        for (size_t i = 0; i < c; ++i, ++di)
        {
          List<std::string> add;
          LIter<std::string> qi = (*di).begin();
          for (size_t j = 0; j < r && qi != (*di).end(); ++j, ++qi)
          {
            if (j != n_r)
            {
              add.push_back(*qi);
            }
          }
          datan.push_back(add);
        }
        data = datan;
        std::string l = "";
        LIter<std::string> fi = f.begin();
        for (size_t i = 0; fi != f.end(); ++i, ++fi)
        {
          if (i != n_r)
          {
            l += *fi;
          }
        }
        noname = l;
        c--;
      }
    }
    std::pair<List<List<std::string>>, List<List<std::string>>> data_split(double t_siz)
    {
      if (r > 1)
      {
        List<List<std::string>> l1, l2;
        size_t j = 1;
        l1.push_back(*data.begin());
        LIter<List<std::string>> i = data.begin();
        ++i;
        l2.push_back(*i);
        ++i;
        for (; i != data.end() && j < t_siz*r; ++i, ++j)
        {
          l1.push_back(*i);
        }
        for (; i != data.end(); ++i)
        {
          l2.push_back(*i);
        }
        return {l1, l2};
      }
      else
      {
        throw std::logic_error("malo tensorov");
      }
    }
    private:
      size_t c, r;
      std::string noname, name_data;
      List<List<std::string>> data;
  };
}

#endif
