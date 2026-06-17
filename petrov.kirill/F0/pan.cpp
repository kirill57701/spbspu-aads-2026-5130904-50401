#include <iostream>
#include "../common/pandas.hpp"

int main()
{
  petrov::dataset d;
  d.read_dataset(std::cin);
  d.data_head(3);
  d.save_data(std::cin);
  std::string s = "alu_type";
  d.feature_del(s);
  d.data_head(3);
}
