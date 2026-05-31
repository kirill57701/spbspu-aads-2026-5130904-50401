#include <../common/LinearRegression.hpp>

double predict(petrov::List<double> inp)
{
  double c = 0;
  for (size_t i = 0; i < inp.size(); ++i)
  {
    c += inp[i]*W1[i];
  }
  return c;
}
