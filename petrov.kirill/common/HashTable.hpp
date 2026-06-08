#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <cstddef>
#include "list.hpp"

namespace petrov
{
  template <class Key, class Value, class HashFunc = Hash<Key>, class Equal = std::equal_to<Key>>
  class HashTable
  {
  private:
    struct Node
    {
      std::pair<Key, Value> kv;
      Node *next;
      Node(const Key &k, const Value &v, Node *n):
        kv(k, v), next(n)
      {}
    };

    Node **buckets_;
    size_t bucketCount_;
    size_t size_;
    HashFunc hasher_;
    Equal equal_;
  public:
    HashTable():
      buckets_(new Node*[16]()), bucketCount_(16), size_(0)
    {}
    ~HashTable()
    {
      clear();
      delete[] buckets_;
    }
    void clear()
    {
      for (size_t i = 0; i < bucketCount_; ++i)
      {
        Node *curr = buckets_[i];
        while (curr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
      }
      buckets_[i] = nullptr;
    }
    size_ = 0;
  }
  void add(const Key &k, const Value &v)
  {
    size_t idx = hasher_(k) % bucketCount_;
    buckets_[idx] = new Node(k, v, buckets_[idx]);
    ++size_;
  }

  bool has(const Key &k) const
  {
    size_t idx = hasher_(k) % bucketCount_;
    Node *curr = buckets_[idx];
    while (curr)
    {
      if (equal_(curr->kv.first, k)) return 1;
      curr = curr->next;
    }
    return 0;
  }
  void rehash(size_t slots)
  {
    Node **newBuckets = new Node*[slots]();
    for (size_t i = 0; i < bucketCount_; ++i)
    {
      Node *curr = buckets_[i];
      while (curr) {
        Node *next = curr->next;
        size_t newIdx = hasher_(curr->kv.first) % slots;
        curr->next = newBuckets[newIdx];
        newBuckets[newIdx] = curr;
        curr = next;
      }
    }
    delete[] buckets_;
    buckets_ = newBuckets;
    bucketCount_ = slots;
  }
};
}


#endif
