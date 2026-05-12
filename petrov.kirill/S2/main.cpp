#include <iostream>
#include <fstream>
#include <exception>
#include "utils.hpp"
#include "../common/Queue.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "err\n";
    return 1;
  }

  try
  {
    std::ifstream ifs;
    if (argc == 2)
    {
      ifs.open(argv[1]);
      if (!ifs.is_open())
      {
        std::cerr << "err\n";
        return 1;
      }
    }

    std::istream& in = (argc == 2) ? ifs : std::cin;
    petrov::Queue<long long int> results = petrov::calcStream(in);

    if (results.empty())
    {
      return 0;
    }

    while (!results.empty())
    {
      std::cout << results.drop();
      if (!results.empty())
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  catch (...)
  {
    std::cerr << "err\n";
    return 1;
  }

  return 0;
}

