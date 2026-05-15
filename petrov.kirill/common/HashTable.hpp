#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <cstddef>
#include "list.hpp"

namespace petrov
{
  template<class Key, class Value, class Hash, class Equal>
  class HashTable
  {
    private:
      struct Entry {
        Key key;
        Value value;
      };

    Entry* table;
    size_t size;
    size_t capacity;
    public:
      HashTable();
      ~HashTable();
      void add(Key k, Value v);
      Value drop(Key k);
      bool has(Key k);
      void rehash(size_t slots);
  };
}

#endif
