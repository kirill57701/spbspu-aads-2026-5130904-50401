#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP
#include "list.hpp"

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
  private:
    List<double> W;
  };
}

#endif
