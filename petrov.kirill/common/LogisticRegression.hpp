#ifndef LOGISTICREGRESSION_HPP
#define LOGISTICREGRESSION_HPP
#include "list.hpp"
#include <fstream>
#include <string>
#include <cmath>

namespace petrov
{
  struct LogisticRegression
  {
    LogisticRegression()
    {
      W.push_back(0.1);
    }
    void add_we(double we)
    {
      W.push_back(we);
    }
    void Log_loss_model_init(dataset data)
    {
      while (W.getSize())
      {
        W.pop_back();
      }
      if (data.getC())
      {
        double wd = 0.1;
        while(W.getSize() < data.getC() - 1)
        {
          W.push_back(wd);
          wd += 0.1;
        }
      }
      else
      {
        throw std::logic_error("err");
      }
    }
    double model_predict(List<double> d)
    {
      if (d.getSize() == W.getSize())
      {
        double out = 0;
        LIter<double> di = d.begin();
        LIter<double> wi = W.begin();
        while (di != d.end())
        {
          out += (*di) * (*wi);
          ++di;
          ++wi;
        }
        return 1/(1 + exp(-out));
      }
      else
      {
        throw std::logic_error("err\n");
      }
    }
    List<double> model_predict(List<List<double>> inp)
    {
      List<double> pred;
      for (LIter<List<double>> ii = inp.begin(); ii != inp.end(); ++ii)
      {
        LIter<double> wi = W.begin();
        double ou = 0;
        for (LIter<double> i1 = (*ii).begin(); i1 != (*ii).end(); ++i1, ++wi)
        {
          ou += (*i1) * (*wi);
        }
        pred.push_back(1/(1 + exp(-ou)));
      }
      return pred;
    }
    void model_fit(List<double> inp, double g, double pred, double a)
    {
      LIter<double> wi = W.begin();
      for (LIter<double> ii = inp.begin(); ii != inp.end(); ++ii)
      {
        (*wi) -= a * (pred - g) * (*ii);
        ++wi;
      }
    }
    void model_fit(List<List<double>> inp, List<double> g, List<double> pred, double a)
    {
      LIter<double> gi = g.begin(), pi = pred.begin();
      for (LIter<List<double>> ii = inp.begin(); ii != inp.end(); ++ii, ++gi, ++pi)
      {
        LIter<double> wi = W.begin();
        for (LIter<double> i1 = (*ii).begin(); i1 != (*ii).end(); ++i1, ++wi)
        {
          (*wi) -= a * ((*pi) - (*gi)) * (*i1);
        }
      }
    }
    void save_predict(std::istream& in, double pred)
    {
      std::ofstream out;
      std::string s;
      in >> s;
      bool isnorm = 0;
      for (size_t i = 0; i < s.size(); ++i)
      {
        if (s[i] == '.')
        {
          isnorm = 1;
          break;
        }
      }
      if (!isnorm)
      {
        out.open(s + ".predict");
      }
      else
      {
        out.open(s);
      }
      out << pred;
      out.close();
    }
    void save_model(std::istream& in)
    {
      std::ofstream out;
      std::string s;
      in >> s;
      bool isnorm = 0;
      for (size_t i = 0; i < s.size(); ++i)
      {
        if (s[i] == '.')
        {
          isnorm = 1;
          break;
        }
      }
      if (!isnorm)
      {
        out.open(s + ".model");
      }
      else
      {
        out.open(s);
      }
      for (LIter<double> wi = W.begin(); wi != W.end(); ++wi)
      {
        out << (*wi) << '\n';
      }
      out.close();
    }
    void load_model(std::istream& in)
    {
      std::ifstream i;
      std::string s;
      in >> s;
      i.open(s);
      LIter<double> wi = W.begin();
      for (; W.getSize(); ++wi)
      {
        W.pop_back();
      }
      for (; !i.eof();)
      {
        double q;
        i >> q;
        W.push_back(q);
      }
      W.pop_back();
    }
    void model_info(std::ostream& out)
    {
      for (LIter<double> wi = W.begin(); wi != W.end(); ++wi)
      {
        out << (*wi) << ' ';
      }
    }
    void show_predict(List<double> inp)
    {
      double ou = 0;
      for (LIter<double> wi = W.begin(), ii = inp.begin(); wi != W.end(); ++wi, ++ii)
      {
        ou += (*wi) * (*ii);
      }
      std::cout << ou;
    }
    size_t getWsize()
    {
      return W.getSize();
    }
    private:
      List<double> W;
  };
}

#endif
