#ifndef LOGISTICREGRESSION_HPP
#define LOGISTICREGRESSION_HPP
#include "list.hpp"
#include <fstream>
#include <string>
#include <cmath>

namespace petrov
{
  struct LogisticRegression
  {
    LogisticRegression()
    {
      W.push_back(0.1);
    }
    void add_we(double we)
    {
      W.push_back(we);
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
        return 1/(1 + exp(out));
      }
    }
    private:
      List<double> W;
  }
}

#endif
