#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <functional>

namespace petrov
{
  template <typename Key, typename Value, typename HashFunc = std::hash<Key>, typename Equal = std::equal_to<Key>>
  class HashTable
  {
  private:
    struct Node
    {
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
    class Iterator;
    class ConstIterator;

    HashTable(size_t slots = 16) :
      buckets_(new Node*[slots]()),
      bucketCount_(slots),
      size_(0)
    {}

    ~HashTable()
    {
      clear();
      delete[] buckets_;
    }

    void add(const Key &k, const Value &v)
    {
      if (has(k)) return;
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
        if (equal_(curr->kv.first, k)) return true;
        curr = curr->next;
      }
      return false;
    }

    void clear()
    {
      for (size_t i = 0; i < bucketCount_; ++i)
      {
        Node *curr = buckets_[i];
        while (curr)
        {
          Node *next = curr->next;
          delete curr;
          curr = next;
        }
        buckets_[i] = nullptr;
      }
      size_ = 0;
    }

    void rehash(size_t slots)
    {
      if (slots == 0) slots = 1;
      Node **newBuckets = new Node*[slots]();
      for (size_t i = 0; i < bucketCount_; ++i)
      {
        Node *curr = buckets_[i];
        while (curr)
        {
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

    size_t getSize() const { return size_; }

    class Iterator
    {
      friend class HashTable;
      HashTable *table_;
      size_t bucketIdx_;
      Node *node_;

      Iterator(HashTable *t, size_t b, Node *n) : table_(t), bucketIdx_(b), node_(n)
      {
        if (!node_ && table_) advance();
      }

    public:
      Iterator() : table_(nullptr), bucketIdx_(0), node_(nullptr) {}
      std::pair<Key, Value> &operator*() { return node_->kv; }
      std::pair<Key, Value> *operator->() { return &node_->kv; }
      bool operator!=(const Iterator &rhs) const { return node_ != rhs.node_; }
      Iterator &operator++()
      {
        if (node_->next) node_ = node_->next;
        else
        {
          bucketIdx_++;
          advance();
        }
        return *this;
      }

    private:
      void advance()
      {
        while (bucketIdx_ < table_->bucketCount_ && !table_->buckets_[bucketIdx_])
          bucketIdx_++;
        node_ = (bucketIdx_ < table_->bucketCount_) ? table_->buckets_[bucketIdx_] : nullptr;
      }
    };

    Iterator begin() { return Iterator(this, 0, buckets_[0]); }
    Iterator end() { return Iterator(this, bucketCount_, nullptr); }
  };
}

#endif
