#include "../common/LinearRegression.hpp"

double petrov::LinearRegression::predict(petrov::List<double> inp)
{
  double c = 0;
  for (petrov::LIter<double> i = inp.begin(), j = W1.begin(); i != inp.end(); ++i, ++j)
  {
    c += (*i)*(*j);
  }
  return c;
}
