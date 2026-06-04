#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP
#include "list.hpp"

namespace petrov
{
  struct LinearRegression
  {
    List<double> W1;
    double lr;
    double predict(List<double> inp);
    List<double> Adamar(List<double> a, List<double> b);
    double sum_vec(List<double> a);
    double mse(double pred, double goal);
  };
  void fit(double& mse, List<double> inp, LinearRegression& d, double g);
}

#endif
