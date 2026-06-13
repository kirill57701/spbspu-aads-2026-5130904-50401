#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LinearRegression model;
  petrov::List<double> inp;
  inp.push_back(1);
  std::cout << model.predict(inp) << '\n';
  double pred = model.predict(inp);
  double a = 0.05;
  model.model_fit(inp, 1, pred, a);
  std::cout << model.predict(inp) << '\n';
}
