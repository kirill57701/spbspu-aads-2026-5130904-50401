#include "../common/LinearRegression.hpp"

double petrov::LinearRegression::predict(petrov::List<double> inp)
{
  return sum_vec(Adamar(inp, W1));
}

petrov::List<double> petrov::LinearRegression::Adamar(petrov::List<double> a, petrov::List<double> b)
{
  petrov::List<double> c;
  for (petrov::LIter<double> i = a.begin(), j = b.begin(); i != a.end(); ++i, ++j)
  {
    c.push_back((*i)*(*j));
  }
  return c;
}

double petrov::LinearRegression::sum_vec(petrov::List<double> a)
{
  double c = 0;
  for (petrov::LIter<double> i = a.begin(); i != a.end(); ++i)
  {
    c += *i;
  }
  return c;
}

double petrov::mse(double pred, double goal)
{
  return (goal - pred) * (goal - pred);
}
