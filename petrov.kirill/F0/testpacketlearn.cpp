#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/pandas.hpp"

int main()
{
  petrov::dataset d;
  d.read_dataset(std::cin);
  d.feature_del("alu_type");
  std::pair<petrov::List<petrov::List<double>>, petrov::List<double>> da = d.data_train_test_split(0.3);
}
