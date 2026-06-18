#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/pandas.hpp"

int main()
{
  petrov::dataset d;
  double a = 0.05;
  d.read_dataset(std::cin);
  d.feature_del("alu_type");
  std::pair<petrov::List<petrov::List<std::string>>, petrov::List<petrov::List<std::string>>> da = d.data_split(0.3);
  std::pair<petrov::List<petrov::List<double>>, petrov::List<double>> train = petrov::data_train_test_split(convert(da.first), 1);
  petrov::LinearRegression model;
  double w = 0.1;
  while(model.getWsize() < d.getC())
  {
    model.add_we(w);
    w += 0.2;
    std::cout << w << '\n';
  }
  model.model_info(std::cout);
  std::cout << '\n';
  model.model_fit(train.first, train.second, model.model_predict(train.first), a);
  model.model_info(std::cout);
}
