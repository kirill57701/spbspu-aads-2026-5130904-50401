#include "commands.hpp"
#include <fstream>
#include <sstream>

bool petrov::loadDictionaries(const std::string& filename, DatasetStore& datasets) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return 0;
  }
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::stringstream ss(line);
    std::string dict_name;
    ss >> dict_name;
    SubTree new_dict;
    int key = 0;
    std::string value;
    while (ss >> key >> value) {
      new_dict.push(key, value);
    }
    datasets.push(dict_name, std::move(new_dict));
  }
  return 1;
}

void petrov::cmdPrint(std::istream& in, std::ostream& out, DatasetStore& datasets) {
  std::string dict_name;
  if (!(in >> dict_name)) {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!datasets.has(dict_name)) {
    out << "<INVALID COMMAND>\n";
    return;
  }
  const SubTree& dict = datasets.get(dict_name);
  if (dict.cbegin() == dict.cend()) {
    out << "<EMPTY>\n";
    return;
  }
  out << dict_name;
  for (auto it = dict.cbegin(); it != dict.cend(); ++it) {
    out << " " << it->key << " " << it->value;
  }
  out << "\n";
}
