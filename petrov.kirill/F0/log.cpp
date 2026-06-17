#include <iostream>
#include "../common/LogisticRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LogisticRegression model;
  model.load_model(std::cin);
  model.model_info(std::cout);
  petrov::List<double> inp;
  inp.push_back(2);
  inp.push_back(3);
  double pred = model.model_predict(inp);
  std::cout << pred << '\n';
  double g = 1, a = 0.5;
  for (size_t k = 0; k < 10; ++k)
  {
    model.model_fit(inp, g, pred, a);
  }
  std::cout << model.model_predict(inp) << '\n';
}
