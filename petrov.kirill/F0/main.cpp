#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/LogisticRegression.hpp"
#include "../common/list.hpp"
#include "../common/pandas.hpp"

std::string parsing(std::string s)
{
  std::string r = "";
  for (size_t i = 0; i < s.size(); ++i)
  {
    if (s[i] != ' ')
    {
      r += s[i];
    }
    else
    {
      if (r[r.size() - 1] != ' ')
      {
        r += s[i];
      }
    }
  }
  return r;
}

std::string whatAcomm(std::string s)
{
  std::string d = "";
  for (size_t i = 0; i < s.size(); ++i)
  {
    if (s[i] != ' ')
    {
      d += s[i];
    }
    else
    {
      return d;
    }
  }
  return d;
}

int main()
{
  std::string s;
  petrov::LinearRegression modeli;
  petrov::LogisticRegression modelo;
  petrov::dataset data;
  petrov::List<petrov::List<double>> train, test;
  petrov::List<double> goal, pred;
  double a = 0.05;
  while (std::getline(std::cin, s) && !std::cin.eof())
  {
    if (s.empty())
    {
      continue;
    }
    s = parsing(s);
    std::string comm = whatAcomm(s);
    if (comm == "Load_model_linear")
    {
      try
      {
        modeli.load_model(std::cin);
      }
      catch (...)
      {
        std::cout << "err, model not found\n";
        continue;
      }
      std::cout << "Successful load\n";
    }
    else if (comm == "Load_model_logistic")
    {
      try
      {
        modelo.load_model(std::cin);
      }
      catch (...)
      {
        std::cout << "err, model not found\n";
        continue;
      }
      std::cout << "Successful load\n";
    }
    else if (comm == "Save_model_linear")
    {
      modeli.save_model(std::cin);
      std::cout << "<Successfuly saved>\n";
    }
    else if (comm == "Save_model_logistic")
    {
      modelo.save_model(std::cin);
      std::cout << "<Succesfuly saved>\n";
    }
    else if (comm == "Read_dataset")
    {
      try
      {
        data.read_dataset(std::cin);
      }
      catch (...)
      {
        std::cout << "<Unsuccessfuly readed, dataset not found>\n";
        continue;
      }
      std::cout << "<Successfuly readed>\n";
    }
    else if (comm == "Save_data")
    {
      data.save_data(std::cin);
      std::cout << "<Data Succefully saved>\n";
    }
    else if (comm == "Linear_model_init")
    {
      try
      {
        modeli.Linear_model_init(data);
      }
      catch(...)
      {
        std::cout << "err, dataset not filled\n";
        continue;
      }
      std::cout << "<Model initialazed correctly>\n";
    }
    else if (comm == "Log_loss_model_init")
    {
      try
      {
        modelo.Log_loss_model_init(data);
      }
      catch (...)
      {
        std::cout << "err, dataset not filled\n";
        continue;
      }
      std::cout << "<Model initialazed correctly\n>";
    }
    else if (comm == "Model_linear_fit")
    {
      modeli.model_fit(train, goal, pred, a);
      std::cout << "<Model fitted successfuly>\n";
    }
    else if (comm == "Model_logistic_fit")
    {
      modelo.model_fit(train, goal, pred, a);
      std::cout << "<Model fitted succesfuly>\n";
    }
    else if (comm == "Change_a")
    {
      std::cin >> a;
      std::cout << "<Changed succesfully>\n";
    }
    else if (comm == "Linear_model_predict_train")
    {
      try
      {
        pred = model.model_predict(train);
      }
      catch(...)
      {
        std::cout << "err, sizes not equal\n";
        continue;
      }
      std::cout << "<train_predicted_succesfully>\n";
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
