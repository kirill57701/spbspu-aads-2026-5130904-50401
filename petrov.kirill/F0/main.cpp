#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LinearRegression model;
  petrov::List<double> d;
  d.push_back(1);
  std::cout << model.predict(d);
}
