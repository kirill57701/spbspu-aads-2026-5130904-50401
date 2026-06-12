#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../common/HashTable.hpp"
#include "../common/list.hpp"

namespace petrov
{
  struct Edge
  {
    int to;
    int weight;
    bool operator==(const Edge& other) const { return to == other.to && weight == other.weight; }
  };

  class Graph
  {
  private:
    HashTable<int, List<Edge>> adjList_;

  public:
    Graph() = default;
    Graph(const Graph& other) : adjList_(other.adjList_) {}

    Graph& operator=(const Graph& other)
    {
      if (this != &other)
      {
        adjList_ = other.adjList_;
      }
      return *this;
    }

    void addVertex(int v)
    {
      if (!adjList_.has(v))
      {
        adjList_.add(v, List<Edge>());
      }
    }

    void addWeightedEdge(int u, int v, int w)
    {
      addVertex(u);
      addVertex(v);
      adjList_.get(u).push_back({v, w});
      adjList_.get(v).push_back({u, w});
    }

    void addEdge(int u, int v)
    {
      addWeightedEdge(u, v, 0);
    }

    void cut(int u, int v, int w)
    {
      if (!adjList_.has(u)) return;
      List<Edge>& neighbors = adjList_.get(u);
      for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
      {
        if (it->to == v && it->weight == w)
        {
          neighbors.erase(it);
          break;
        }
      }
    }

    void swap(Graph& other) noexcept
    {
      adjList_.swap(other.adjList_);
    }

    bool hasVertex(int v) const
    {
      return adjList_.has(v);
    }

    void removeVertex(int v)
    {
      if (!adjList_.has(v)) return;
      adjList_.drop(v);
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        List<Edge>& list = it->second;
        for (auto nIt = list.begin(); nIt != list.end(); )
        {
          if (nIt->to == v) nIt = list.erase(nIt);
          else ++nIt;
        }
      }
    }

    size_t getVertexCount() const
    {
      return adjList_.getSize();
    }

    List<int> getAllVertices() const
    {
du      List<int> vertices;
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        vertices.push_back(it->first);
      }
      return vertices;
    }

    List<int> getOutbound(int v) const
    {
      List<int> res;
      if (adjList_.has(v))
      {
        for (const auto& edge : adjList_.get(v))
        {
          res.push_back(edge.to);
        }
      }
      return res;
    }

    List<int> getInbound(int v) const
    {
      List<int> inbound;
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        for (const auto& edge : it->second)
        {
          if (edge.to == v)
          {
            inbound.push_back(it->first);
          }
        }
      }
      return inbound;
    }

    Graph merge(const Graph& other) const
    {
      Graph result = *this;
      for (auto it = other.adjList_.begin(); it != other.adjList_.end(); ++it)
      {
        result.addVertex(it->first);
        for (const auto& edge : it->second)
        {
          result.addWeightedEdge(it->first, edge.to, edge.weight);
        }
      }
      return result;
    }
  };
}

#endif
