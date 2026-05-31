#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP
#include "list.hpp"

namespace petrov
{
  struct LinearRegression
  {
    List<double> W1;
    double predict(List<double> inp);
  };
}

#endif
