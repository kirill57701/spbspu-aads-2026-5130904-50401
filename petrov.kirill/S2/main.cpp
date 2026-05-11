#include <iostream>
#include <fstream>
#include <exception>
#include "utils.hpp"
#include "Stack.hpp"

int main(int argc, char* argv[])
{
  try
  {
    std::ifstream ifs;
    if (argc > 1)
    {
      file.open(argv[1]);
      if (!ifs.is_open())
      {
        std::cerr << "err\n";
        return 1;
      }
    }
    std::istream& in = (argc > 1) ? ifs : std::cin;
    petrov::Stack<long long int> results = petrov::calcStream(in);

    while (!results.empty())
    {
      std::cout << results.drop() << (results.empty() ? "" : " ");
    }
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
