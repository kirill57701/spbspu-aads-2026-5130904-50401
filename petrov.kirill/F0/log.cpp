#include <iostream>
#include "../common/LogisticRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LogisticRegression model;
  model.load_model(std::cin);
  model.model_info(std::cout);
  petrov::List<double> inp;
  inp.push_back(1);
  inp.push_back(2);
  double pred = model.model_predict(inp);
  std::cout << pred;
}
