#include <iostream>
#include "../common/LogisticRegression.hpp"

int main()
{
  LogisticRegression model;
  model.load_data(std::cin);
  model.model_info(std::cin);
}
