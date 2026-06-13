#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LinearRegression model;
  model.add_we(0.2);
  petrov::List<double> inp;
  inp.push_back(1);
  inp.push_back(2);
  std::cout << model.model_predict(inp) << '\n';
  double pred = model.model_predict(inp);
  double a = 0.05;
  model.model_fit(inp, 1, pred, a);
  std::cout << model.model_predict(inp) << '\n';
  model.save_model(std::cin);
  petrov::LinearRegression model2;
  model2.load_model(std::cin);
  std::cout << model2.model_predict(inp) << '\n';
}
