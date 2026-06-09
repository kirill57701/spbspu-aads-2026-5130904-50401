#include <iostream>
#include <fstream>
#include <string>
#include "../common/list.hpp"
#include "../common/HashTable.hpp"
#include "Graph.hpp"

petrov::List<std::string> splitString(const std::string& str) {
  petrov::List<std::string> res;
  std::string cur;
  for (char c : str) {
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
      if (!cur.empty()) { res.push_back(cur); cur.clear(); }
    } else {
      cur += c;
    }
  }
  if (!cur.empty()) res.push_back(cur);
  return res;
}

void printError() {
  std::cout << "<INVALID COMMAND>\n";
}

petrov::Graph* findGraph(petrov::HashTable<std::string, petrov::Graph>& graphs, const std::string& name) {
  for (auto it = graphs.begin(); it != graphs.end(); ++it) {
    if (it->first == name) return &it->second;
  }
  return nullptr;
}

int main(int argc, char* argv[]) {
  if (argc < 2) return 1;
  std::ifstream ifs(argv[1]);
  if (!ifs.is_open()) return 1;

  petrov::HashTable<std::string, petrov::Graph> graphs;
  std::string gname;
  int ecount;
  while (ifs >> gname >> ecount) {
    petrov::Graph g;
    for (int i = 0; i < ecount; ++i) {
      int u, v;
      ifs >> u >> v;
      g.addEdge(u, v);
    }
    graphs.add(gname, g);
  }

  std::string line;
  while (std::getline(std::cin, line)) {
    petrov::List<std::string> tokens = splitString(line);
    if (tokens.IsEmpty()) continue;

    auto it = tokens.begin();
    std::string cmd = *it;

    try {
      if (cmd == "graphs") {
        for (auto graphIt = graphs.begin(); graphIt != graphs.end(); ++graphIt) {
          std::cout << graphIt->first << "\n";
        }
      } else if (cmd == "vertexes") {
        if (tokens.getSize() != 2) { printError(); continue; }
        petrov::Graph* g = findGraph(graphs, *(++it));
        if (!g) { printError(); continue; }
        petrov::List<int> verts = g->getAllVertices();
        for (auto vIt = verts.begin(); vIt != verts.end(); ++vIt) std::cout << *vIt << "\n";
      } else if (cmd == "outbound" || cmd == "inbound") {
        if (tokens.getSize() != 3) { printError(); continue; }
        petrov::Graph* g = findGraph(graphs, *(++it));
        int v = std::stoi(*(++it));
        if (!g || !g->hasVertex(v)) { printError(); continue; }
        petrov::List<int> res = (cmd == "outbound") ? g->getOutbound(v) : g->getInbound(v);
        for (auto rIt = res.begin(); rIt != res.end(); ++rIt) std::cout << *rIt << "\n";
      } else if (cmd == "bind" || cmd == "cut") {
        if (tokens.getSize() != 4) { printError(); continue; }
        petrov::Graph* g = findGraph(graphs, *(++it));
        int u = std::stoi(*(++it));
        int v = std::stoi(*(++it));
        if (!g) { printError(); continue; }
        if (cmd == "bind") g->addEdge(u, v);
        else g->cut(u, v);
      } else {
        printError();
      }
    } catch (...) {
      printError();
    }
  }
  return 0;
}
