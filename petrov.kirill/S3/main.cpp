#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "../common/list.hpp"
#include "../common/HashTable.hpp"
#include "Graph.hpp"

using GraphTable = petrov::HashTable<std::string, petrov::Graph>;

petrov::HashTable<std::string, int> strToInt;
petrov::HashTable<int, std::string> intToStr;
int nextVertexId = 1;

int getVertId(const std::string& v) {
  for (auto it = strToInt.begin(); it != strToInt.end(); ++it) {
    if (it->first == v) {
      return it->second;
    }
  }
  strToInt.add(v, nextVertexId);
  intToStr.add(nextVertexId, v);
  return nextVertexId++;
}

std::string getVertStr(int id) {
  for (auto it = intToStr.begin(); it != intToStr.end(); ++it) {
    if (it->first == id) {
      return it->second;
    }
  }
  return "";
}

petrov::Graph* findGraph(GraphTable& graphs, const std::string& name) {
  for (auto it = graphs.begin(); it != graphs.end(); ++it) {
    if (it->first == name) {
      return &it->second;
    }
  }
  return nullptr;
}

void processGraphs(std::istream&, std::ostream& out, GraphTable& graphs) {
  if (graphs.isEmpty()) {
    out << "\n";
    return;
  }
  std::vector<std::string> names;
  for (auto it = graphs.begin(); it != graphs.end(); ++it) {
    names.push_back(it->first);
  }
  std::sort(names.begin(), names.end());
  for (const auto& name : names) {
    out << name << "\n";
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
  if (verts.getSize() == 0) {
    out << "\n";
    return;
  }
  std::vector<std::string> names;
  for (auto it = verts.begin(); it != verts.end(); ++it) {
    names.push_back(getVertStr(*it));
  }
  std::sort(names.begin(), names.end());
  for (const auto& name : names) {
    out << name << "\n";
  }
}

void processOutbound(std::istream& in, std::ostream& out, GraphTable& graphs) {
  std::string gname, vname;
  if (!(in >> gname >> vname)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }

  int vid = getVertId(vname);
  if (!g->hasVertex(vid)) {
    throw std::runtime_error("");
  }

  petrov::List<int> outbound = g->getOutbound(vid);
  if (outbound.getSize() == 0) {
    out << "\n";
    return;
  }

  std::vector<std::string> names;
  for (auto it = outbound.begin(); it != outbound.end(); ++it) {
    names.push_back(getVertStr(*it));
  }

  std::sort(names.begin(), names.end());
  names.erase(std::unique(names.begin(), names.end()), names.end());

  for (const auto& name : names) {
    out << name << "\n";
  }
}

void processInbound(std::istream& in, std::ostream& out, GraphTable& graphs) {
  std::string gname, vname;
  if (!(in >> gname >> vname)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }

  int vid = getVertId(vname);
  if (!g->hasVertex(vid)) {
    throw std::runtime_error("");
  }

  petrov::List<int> inbound = g->getInbound(vid);
  if (inbound.getSize() == 0) {
    out << "\n";
    return;
  }

  std::vector<std::string> names;
  for (auto it = inbound.begin(); it != inbound.end(); ++it) {
    names.push_back(getVertStr(*it));
  }

  std::sort(names.begin(), names.end());
  names.erase(std::unique(names.begin(), names.end()), names.end());

  for (const auto& name : names) {
    out << name << "\n";
  }
}

void processBind(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string gname, u_str, v_str;
  int w;
  if (!(in >> gname >> u_str >> v_str >> w)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }

  g->addWeightedEdge(getVertId(u_str), getVertId(v_str), w);
}

void processCut(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string gname, u_str, v_str;
  int w;
  if (!(in >> gname >> u_str >> v_str >> w)) {
    throw std::runtime_error("");
  }
  petrov::Graph* g = findGraph(graphs, gname);
  if (!g) {
    throw std::runtime_error("");
  }

  int u = getVertId(u_str);
  int v = getVertId(v_str);

  if (!g->hasVertex(u) || !g->hasVertex(v)) {
    throw std::runtime_error("");
  }

  g->cut(u, v, w);
}

void processCreate(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string gname;
  if (!(in >> gname)) {
    throw std::runtime_error("");
  }
  if (graphs.has(gname)) {
    throw std::runtime_error("");
  }

  int vcount;
  if (!(in >> vcount)) {
    throw std::runtime_error("");
  }

  petrov::Graph g;
  for (int i = 0; i < vcount; ++i) {
    std::string v;
    if (!(in >> v)) {
      throw std::runtime_error("");
    }
    g.addVertex(getVertId(v));
  }
  graphs.add(gname, g);
}

void processMerge(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string res, g1, g2;
  if (!(in >> res >> g1 >> g2)) {
    throw std::runtime_error("");
  }
  if (!graphs.has(g1) || !graphs.has(g2) || graphs.has(res)) {
    throw std::runtime_error("");
  }

  petrov::Graph* graph1 = findGraph(graphs, g1);
  petrov::Graph* graph2 = findGraph(graphs, g2);

  graphs.add(res, graph1->merge(*graph2));
}

void processExtract(std::istream& in, std::ostream&, GraphTable& graphs) {
  std::string res, gname;
  if (!(in >> res >> gname)) {
    throw std::runtime_error("");
  }
  if (!graphs.has(gname) || graphs.has(res)) {
    throw std::runtime_error("");
  }

  int vcount;
  if (!(in >> vcount)) {
    throw std::runtime_error("");
  }

  petrov::HashTable<int, bool> selected;
  std::vector<int> targetVerts;
  for (int i = 0; i < vcount; ++i) {
    std::string v;
    if (!(in >> v)) {
      throw std::runtime_error("");
    }
    int id = getVertId(v);
    targetVerts.push_back(id);
    selected.add(id, true);
  }

  petrov::Graph* src = findGraph(graphs, gname);
  for (int id : targetVerts) {
    if (!src->hasVertex(id)) {
      throw std::runtime_error("");
    }
  }

  petrov::Graph result;
  for (int id : targetVerts) {
    result.addVertex(id);
  }

  for (int from : targetVerts) {
    petrov::List<int> outbound = src->getOutbound(from);
    for (auto it = outbound.begin(); it != outbound.end(); ++it) {
      int to = *it;
      if (selected.has(to)) {
        result.addWeightedEdge(from, to, 0);
      }
    }
  }

  graphs.add(res, result);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "1 argument expected\n";
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
      std::string u_str, v_str;
      int w;
      if (!(ifs >> u_str >> v_str >> w)) {
        return 1;
      }
      g.addWeightedEdge(getVertId(u_str), getVertId(v_str), w);
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
      } else if (cmd == "create") {
        processCreate(std::cin, std::cout, graphs);
      } else if (cmd == "merge") {
        processMerge(std::cin, std::cout, graphs);
      } else if (cmd == "extract") {
        processExtract(std::cin, std::cout, graphs);
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
