#include <iostream>
#include "../common/LinearRegression.hpp"
#include "../common/LogisticRegression.hpp"
#include "../common/list.hpp"
#include "../common/pandas.hpp"

using namespace petrov;

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
  LinearRegression modeli;
  LogisticRegression modelo;
  dataset data;
  List<List<double>> train, test;
  List<double> tr_goal, tr_pred, te_goal, te_pred;
  double a = 0.0005;
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
      std::cout << "<Model initialazed correctly>\n";
    }
    else if (comm == "Model_linear_fit")
    {
      size_t k;
      std::cout << "how much iterations of fitting you need?\n";
      std::cin >> k;
      for (size_t i = 0; i < k; ++i)
      {
        modeli.model_fit(train, tr_goal, tr_pred, a);
      }
      std::cout << "<Model fitted successfuly>\n";
    }
    else if (comm == "Model_logistic_fit")
    {
      if (train.getSize())
      {
        size_t k;
        std::cout << "how much iterations of fitting you need?\n";
        std::cin >> k;
        for (size_t i = 0; i < k; ++i)
        {
          modelo.model_fit(train, tr_goal, tr_pred, a);
          tr_pred = modelo.model_predict(train);
        }
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
    else if (comm == "Data_train_test_split")
    {
      double c;
      std::cout << "enter % of train_size\n";
      std::cin >> c;
      std::pair<List<List<std::string>>, List<List<std::string>>> datp;
      datp = data.data_split(c);
      List<List<double>> dat1p = convert(datp.first), dat2p = convert(datp.second);
      train = dat1p;
      test = dat2p;
      std::cout << "<Splitted_successfull>\n";
    }
    else if (comm == "Data_split")
    {
      size_t k;
      std::cout << "Enter number of feature\n";
      std::cin >> k;
      std::pair<List<List<double>>, List<double>> tra = data_train_test_split(train, k);
      std::pair<List<List<double>>, List<double>> tes = data_train_test_split(test, k);
      te_goal = tes.second;
      tr_goal = tra.second;
      train = tra.first;
      test = tes.first;
      std::cout << "<Splitted_successfull>\n";
    }
    else if (comm == "Feature_scale")
    {
      size_t i;
      std::cout << "select dimension to scale\n";
      std::cin >> i;
      train = norm(train, i);
      test = norm(test, i);
      std::cout << "<Features scaled succesfully>\n";
    }
    else if (comm == "Data_corr")
    {
      data_corr(train);
    }
    else if (comm == "Predict_Linear")
    {
      std::cout << "Enter " << data.getC() - 1 << " elems\n";
      List<double> d;
      for (size_t i = 0; i < data.getC() - 1; ++i)
      {
        double in;
        std::cin >> in;
        d.push_back(in);
      }
      std::cout << modeli.model_predict(d) << '\n';
    }
    else if (comm == "Predict_Logistic")
    {
      std::cout << "Enter " << data.getC() - 1 << " elems\n";
      List<double> d;
      for (size_t i = 0; i < data.getC() - 1; ++i)
      {
        double in;
        std::cin >> in;
        d.push_back(in);
      }
      std::cout << modelo.model_predict(d) << '\n';
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
