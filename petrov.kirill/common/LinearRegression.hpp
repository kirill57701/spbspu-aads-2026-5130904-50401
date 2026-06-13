#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP
#include "list.hpp"
#include <fstream>
#include <string>

namespace petrov
{
  struct LinearRegression
  {
    LinearRegression()
    {
      W.push_back(0.1);
    }
    double model_predict(List<double> d)
    {
      if (d.getSize() == W.getSize())
      {
        double out = 0;
        LIter<double> di = d.begin();
        LIter<double> wi = W.begin();
        while (di != d.end())
        {
          out += (*di) * (*wi);
          ++di;
          ++wi;
        }
        return out;
      }
      else
      {
        throw std::logic_error("sizes dont equal");
      }
    }
    void model_fit(List<double> inp, double g, double pred, double a)
    {
      LIter<double> wi = W.begin();
      for (LIter<double> ii = inp.begin(); ii != inp.end(); ++ii)
      {
        (*wi) -= a * (pred - g) * (*ii);
        ++wi;
      }
    }
    void save_predict(std::istream& in, double pred)
    {
      std::ofstream out;
      std::string s;
      in >> s;
      bool isnorm = 0;
      for (size_t i = 0; i < s.size(); ++i)
      {
        if (s[i] == '.')
        {
          isnorm = 1;
          break;
        }
      }
      if (!isnorm)
      {
        out.open(s + ".predict");
      }
      else
      {
        out.open(s);
      }
      out << pred;
      out.close();
    }
    double model_score_mse(double pred, double goal)
    {
      return (pred - goal)*(pred - goal);
    }
    void save_model(std::istream& in)
    {
      std::ofstream out;
      std::string s;
      in >> s;
      bool isnorm = 0;
      for (size_t i = 0; i < s.size(); ++i)
      {
        if (s[i] == '.')
        {
          isnorm = 1;
          break;
        }
      }
      if (!isnorm)
      {
        out.open(s + ".model");
      }
      else
      {
        out.open(s);
      }
      for (LIter<double> wi = W.begin(); wi != W.end(); ++wi)
      {
        out << (*wi) << std::endl;
      }
      out.close();
    }
  private:
    List<double> W;
  };
}

#endif
