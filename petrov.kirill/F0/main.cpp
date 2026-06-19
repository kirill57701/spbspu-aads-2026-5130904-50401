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
  petrov::List<double> tr_goal, tr_pred, te_goal, te_pred;
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
      modeli.model_fit(train, tr_goal, tr_pred, a);
      std::cout << "<Model fitted successfuly>\n";
    }
    else if (comm == "Model_logistic_fit")
    {
      if (train.getSize())
      {
        modelo.model_fit(train, tr_goal, tr_pred, a);
        std::cout << "<Model fitted succesfuly>\n";
      }
      else
      {
        std::cout << "err train is empty\n";
      }
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
        tr_pred = modeli.model_predict(train);
      }
      catch(...)
      {
        std::cout << "err, sizes not equal\n";
        continue;
      }
      std::cout << "<train_predicted_succesfully>\n";
    }
    else if (comm == "Linear_model_predict_test")
    {
      try
      {
        te_pred = modeli.model_predict(test);
      }
      catch(...)
      {
        std::cout << "err, sizes not equal\n";
        continue;
      }
      std::cout << "<test_predicted_succesfully>\n";
    }
    else if (comm == "Logistic_model_predict_train")
    {
      try
      {
        tr_pred = modelo.model_predict(train);
      }
      catch(...)
      {
        std::cout << "err, sizes not equal\n";
        continue;
      }
      std::cout << "<train_predicted_succesfully>\n";
    }
    else if (comm == "Logistic_model_predict_test")
    {
      try
      {
        te_pred = modelo.model_predict(test);
      }
      catch(...)
      {
        std::cout << "err, sizes not equal\n";
        continue;
      }
      std::cout << "<test_predicted_succesfully>\n";
    }
    else if (comm == "Save_predict")
    {
      modeli.save_predict(std::cin, te_pred);
      std::cout << "<Saved succesfully>\n";
    }
    else if (comm == "Model_linear_score")
    {
      std::cout << modeli.model_score_mse(te_pred, te_goal);
    }
    else if (comm == "Feature_del")
    {
      std::string s;
      std::cin >> s;
      try
      {
        data.feature_del(s);
      }
      catch(...)
      {
        std::cout << "err, feature not found\n";
        continue;
      }
      std::cout << "<Feature deleted successfuly>\n";
    }
    else if (comm == "Make_double")
    {
      double c;
      std::cout << "enter % of test_size\n";
      std::cin >> c;
      std::pair<petrov::List<petrov::List<std::string>>, petrov::List<petrov::List<std::string>>> datp;
      datp = data.data_split(c);
      petrov::List<petrov::List<double>> dat1p = convert(datp.first), dat2p = petrov::convert(datp.second);
      size_t k;
      std::cout << "enter number of feature\n";
      std::cin >> k;
      std::pair<petrov::List<petrov::List<double>>, petrov::List<double>> tra = data_train_test_split(dat1p, k), tes = data_train_test_split(dat2p, k);
      te_goal = tes.second;
      tr_goal = tra.second;
      train = tra.first;
      test = tes.first;
      std::cout << "<Maked_successfull>\n";
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}
