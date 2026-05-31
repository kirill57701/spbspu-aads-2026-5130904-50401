#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LinearRegression model;
  size_t a;
  double q;
  petrov::List<double> inp;
  std::cin >> a;
  for (size_t i = 0; i < a; ++i)
  {
    std::cin >> q;
    model.W1.push_back(q);
  }
  for (size_t i = 0; i < a; ++i)
  {
    std::cin >> q;
    inp.push_back(q);
  }
  std::cout << model.predict(inp);
}
