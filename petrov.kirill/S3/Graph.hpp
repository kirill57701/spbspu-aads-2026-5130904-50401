#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "common/HashTable.hpp"
#include "common/list.hpp"

namespace petrov
{
  class Graph
  {
  private:
    HashTable<int, List<int>> adjList_;

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
        adjList_.add(v, List<int>());
      }
    }

    void addEdge(int u, int v)
    {
      addVertex(u);
      addVertex(v);

      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        if (it->first == u)
        {
          it->second.push_back(v);
        }
        else if (it->first == v)
        {
          it->second.push_back(u);
        }
      }
    }

    void cut(int u, int v)
    {
      if (!adjList_.has(u) || !adjList_.has(v))
      {
        return;
      }

      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        if (it->first == u)
        {
          it->second.remove(v);
        }
        else if (it->first == v)
        {
          it->second.remove(u);
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
      if (!adjList_.has(v))
      {
        return;
      }

      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        it->second.remove(v);
      }
      adjList_.drop(v);
    }

    size_t getVertexCount() const
    {
      return adjList_.getSize();
    }

    bool hasEdge(int u, int v) const
    {
      if (!adjList_.has(u))
      {
        return 0;
      }

      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        if (it->first == u)
        {
          const auto& neighbors = it->second;
          for (int neighbor : neighbors)
          {
            if (neighbor == v)
            {
              return 1;
            }
          }
          return 0;
        }
      }
      return 0;
    }

    struct EdgeTarget
    {
      int vertex;
      List<int> weights;
    };

    List<int> getNeighbors(int v) const
    {
      if (adjList_.has(v))
      {
        for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
        {
          if (it->first == v)
          {
            return it->second;
          }
        }
      }
      return List<int>();
    }

    List<int> getAllVertices() const
    {
      List<int> vertices;
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        vertices.push_back(it->first);
      }
      return vertices;
    }

    bool isConnected(int u, int v) const
    {
      return hasEdge(u, v);
    }

    void clear()
    {
      List<int> allVertices = getAllVertices();
      for (int v : allVertices)
      {
        removeVertex(v);
      }
    }

    bool isEmpty() const
    {
      return adjList_.getSize() == 0;
    }

    void printGraph() const
    {
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        int v = it->first;
        const auto& neighbors = it->second;
        for (int neighbor : neighbors)
        {
          if (v < neighbor)
          {
          }
        }
      }
    }

    size_t getDegree(int v) const
    {
      if (adjList_.has(v))
      {
        for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
        {
          if (it->first == v)
          {
            return it->second.getSize();
          }
        }
      }
      return 0;
    }

    void addWeightedEdge(int u, int v, int weight)
    {
      addVertex(u);
      addVertex(v);
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        if (it->first == u)
        {
          it->second.push_back(v);
        }
        else if (it->first == v)
        {
          it->second.push_back(u);
        }
      }
    }

    List<int> getOutbound(int v) const
    {
      return getNeighbors(v);
    }

    List<int> getInbound(int v) const
    {
      List<int> inbound;
      for (auto it = adjList_.begin(); it != adjList_.end(); ++it)
      {
        for (int neighbor : it->second)
        {
          if (neighbor == v)
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
        for (int neighbor : it->second)
        {
          result.addEdge(it->first, neighbor);
        }
      }
      return result;
    }
  };
}

#endif
