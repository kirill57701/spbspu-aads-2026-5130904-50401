#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "hash_table.hpp"
#include <vector>

namespace petrov
{
  class Graph
  {
  private:
    HashTable<int, std::vector<int>> adjList_;

  public:
    Graph() = default;

    void addVertex(int v)
    {
      if (!adjList_.has(v))
      {
        adjList_.add(v, std::vector<int>());
      }
    }

    void addEdge(int u, int v)
    {
      addVertex(u);
      addVertex(v);
      for (auto &pair : adjList_)
      {
        if (pair.first == u)
        {
          pair.second.push_back(v);
        }
        if (pair.first == v)
        {
          pair.second.push_back(u);
        }
      }
    }

    bool hasVertex(int v) const
    {
      return adjList_.has(v);
    }

    void removeVertex(int v)
    {
      if (!adjList_.has(v))
      {
        return;
      }
      for (auto &pair : adjList_)
      {
        auto &neighbors = pair.second;
        for (auto it = neighbors.begin(); it != neighbors.end(); )
        {
          if (*it == v)
          {
            it = neighbors.erase(it);
          }
          else
          {
            ++it;
          }
        }
      }
      adjList_.drop(v);
    }
  };
}

#endif
