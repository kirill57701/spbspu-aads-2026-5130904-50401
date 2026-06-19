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
  double split = 0.3;
  std::pair<petrov::List<petrov::List<std::string>>, petrov::List<petrov::List<std::string>>> w = d.data_split(split);
  petrov::List<double> kirill = petrov::convert(*w.first.begin());
  for (petrov::LIter<double> ki = kirill.begin(); ki != kirill.end(); ++ki)
  {
    std::cout << (*ki) << '\n';
  }
  d.dims();
  std::string s1 = "workload", s2 = "work";
  d.rename(s1, s2);
  d.dims();
}
