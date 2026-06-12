#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>
#include "../common/list.hpp"
#include "../common/HashTable.hpp"
#include "Graph.hpp"

using GraphTable = petrov::HashTable<std::string, petrov::Graph>;

petrov::Graph* findGraph(GraphTable& graphs, const std::string& name) {
  for (auto it = graphs.begin(); it != graphs.end(); ++it) {
    if (it->first == name) {
      return &it->second;
    }
  }
  return nullptr;
}

void processGraphs(std::istream&, std::ostream& out, GraphTable& graphs) {
  for (auto it = graphs.begin(); it != graphs.end(); ++it) {
    out << it->first << "\n";
  }
}

void processVertexes(std::istream& in, std::ostream& out, GraphTable& graphs) {
  std::string gname;
  if (!(in >> gname)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }
  petrov::List<int> verts = g->getAllVertices();
  for (auto it = verts.begin(); it != verts.end(); ++it) {
    out << *it << "\n";
  }
}

void processOutbound(std::istream& in, std::ostream& out, GraphTable& graphs) {
  std::string gname;
  int v;
  if (!(in >> gname >> v)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g || !g->hasVertex(v)) {
    throw std::runtime_error("");
  }
  petrov::List<int> res = g->getOutbound(v);
  for (auto it = res.begin(); it != res.end(); ++it) {
    out << *it << "\n";
  }
}

void processInbound(std::istream& in, std::ostream& out, GraphTable& graphs) {
  std::string gname;
  int v;
  if (!(in >> gname >> v)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g || !g->hasVertex(v)) {
    throw std::runtime_error("");
  }
  petrov::List<int> res = g->getInbound(v);
  for (auto it = res.begin(); it != res.end(); ++it) {
    out << *it << "\n";
  }
}

void processBind(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string gname;
  int u, v;
  if (!(in >> gname >> u >> v)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }
  g->addEdge(u, v);
}

void processCut(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string gname;
  int u, v;
  if (!(in >> gname >> u >> v)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }
  g->cut(u, v);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs.is_open()) {
    return 1;
  }

  GraphTable graphs;
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

  std::string cmd;
  while (std::cin >> cmd) {
    try {
      if (cmd == "graphs") {
        processGraphs(std::cin, std::cout, graphs);
      } else if (cmd == "vertexes") {
        processVertexes(std::cin, std::cout, graphs);
      } else if (cmd == "outbound") {
        processOutbound(std::cin, std::cout, graphs);
      } else if (cmd == "inbound") {
        processInbound(std::cin, std::cout, graphs);
      } else if (cmd == "bind") {
        processBind(std::cin, std::cout, graphs);
      } else if (cmd == "cut") {
        processCut(std::cin, std::cout, graphs);
      } else {
        throw std::runtime_error("");
      }
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
