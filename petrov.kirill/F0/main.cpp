#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/list.hpp"

int main()
{
  petrov::LinearRegression model;
  model.W1.push_back(0.1);
  double q;
  model.lr = 0.01;
  petrov::List<double> g;
  g.push_back(1);
  double mse = model.mse(model.predict(g), *g.begin());
  petrov::fit(mse, g, model, *g.begin());
  std::cout << "\n" << model.predict(g);

  for (size_t i = 0; i < 100; ++i)
  {
    petrov::fit(mse, g, model, *g.begin());
  }
  std::cout << "\n" << model.predict(g);
}
