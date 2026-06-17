#include <iostream>
#include "../common/LogisticRegression.hpp"

int main()
{
  petrov::LogisticRegression model;
  model.load_model(std::cin);
  model.model_info(std::cout);
}
