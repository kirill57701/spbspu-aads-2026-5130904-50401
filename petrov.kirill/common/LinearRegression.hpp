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
      double predict(List<double> d)
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
    private:
      List<double> W;
  };
}

#endif
