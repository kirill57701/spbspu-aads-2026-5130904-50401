#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <cstddef>
#include "list.hpp"

namespace petrov {
  template <class Key, class Value, class HashFunc = Hash<Key>, class Equal = std::equal_to<Key>>
  class HashTable {
  private:
    struct Node {
      std::pair<Key, Value> kv;
      Node *next;
      Node(const Key &k, const Value &v, Node *n) : kv(k, v), next(n) {}
    };

    Node **buckets_;
    size_t bucketCount_;
    size_t size_;
    HashFunc hasher_;
    Equal equal_;
  public:
    HashTable() : buckets_(new Node*[16]()), bucketCount_(16), size_(0) {}
  };
}


#endif
