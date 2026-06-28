#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <functional>
#include <memory>

namespace petrov
{
  template < typename Key, typename Value >
  struct HashTableNode
  {
    std::pair< Key, Value > kv;
    HashTableNode *next;

    HashTableNode(const Key &k, const Value &v, HashTableNode *n):
      kv(k, v),
      next(n)
    {
    }
  };

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  class HashTable;

  template < typename Key, typename Value, typename HashFunc = std::hash< Key >, typename Equal = std::equal_to< Key > >
  class HashTableIterator
  {
    friend class HashTable< Key, Value, HashFunc, Equal >;

  private:
    HashTable< Key, Value, HashFunc, Equal > *table_;
    size_t bucketIdx_;
    HashTableNode< Key, Value > *node_;

    HashTableIterator(HashTable< Key, Value, HashFunc, Equal > *t, size_t b, HashTableNode< Key, Value > *n);

    void advance();

  public:
    HashTableIterator();

    std::pair< Key, Value > &operator*();
    std::pair< Key, Value > *operator->();
    bool operator!=(const HashTableIterator &rhs) const;
    HashTableIterator &operator++();
  };

  template < typename Key, typename Value, typename HashFunc = std::hash< Key >, typename Equal = std::equal_to< Key > >
  class HashTableConstIterator
  {
    friend class HashTable< Key, Value, HashFunc, Equal >;

  private:
    const HashTable< Key, Value, HashFunc, Equal > *table_;
    size_t bucketIdx_;
    const HashTableNode< Key, Value > *node_;

    HashTableConstIterator(const HashTable< Key, Value, HashFunc, Equal > *t, size_t b, const HashTableNode< Key, Value > *n);

    void advance();

  public:
    HashTableConstIterator();

    const std::pair< Key, Value > &operator*() const;
    const std::pair< Key, Value > *operator->() const;
    bool operator!=(const HashTableConstIterator &rhs) const;
    HashTableConstIterator &operator++();
  };

  template < typename Key, typename Value, typename HashFunc = std::hash< Key >, typename Equal = std::equal_to< Key > >
  class HashTable
  {
  public:
    using Node = HashTableNode< Key, Value >;
    using Iterator = HashTableIterator< Key, Value, HashFunc, Equal >;
    using ConstIterator = HashTableConstIterator< Key, Value, HashFunc, Equal >;

    friend class HashTableIterator< Key, Value, HashFunc, Equal >;
    friend class HashTableConstIterator< Key, Value, HashFunc, Equal >;

  private:
    Node **buckets_;
    size_t bucketCount_;
    size_t size_;
    HashFunc hasher_;
    Equal equal_;
    double maxLoadFactor_;

  public:
    explicit HashTable(size_t slots = 16);
    HashTable(const HashTable &other);
    ~HashTable();

    HashTable &operator=(const HashTable &other);

    void setMaxLoadFactor(double maxLoad);
    void add(const Key &k, const Value &v);
    size_t erase(const Key &key);
    bool contains(const Key &k) const;
    bool empty() const;
    size_t capacity() const;
    size_t size() const;
    void swap(HashTable &rhs) noexcept;
    void clear();
    void rehash(size_t slots);

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator find(const Key &k);
    ConstIterator find(const Key &k) const;
  };

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableIterator< Key, Value, HashFunc, Equal >::HashTableIterator(HashTable< Key, Value, HashFunc, Equal > *t, size_t b, HashTableNode< Key, Value > *n):
    table_(t),
    bucketIdx_(b),
    node_(n)
  {
    if (!node_ && table_)
    {
      advance();
    }
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTableIterator< Key, Value, HashFunc, Equal >::advance()
  {
    while (bucketIdx_ < table_->bucketCount_ && !table_->buckets_[bucketIdx_])
    {
      bucketIdx_++;
    }
    node_ = (bucketIdx_ < table_->bucketCount_) ? table_->buckets_[bucketIdx_] : nullptr;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableIterator< Key, Value, HashFunc, Equal >::HashTableIterator():
    table_(nullptr),
    bucketIdx_(0),
    node_(nullptr)
  {
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  std::pair< Key, Value > &HashTableIterator< Key, Value, HashFunc, Equal >::operator*()
  {
    return node_->kv;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  std::pair< Key, Value > *HashTableIterator< Key, Value, HashFunc, Equal >::operator->()
  {
    return &node_->kv;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  bool HashTableIterator< Key, Value, HashFunc, Equal >::operator!=(const HashTableIterator &rhs) const
  {
    return node_ != rhs.node_;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableIterator< Key, Value, HashFunc, Equal > &HashTableIterator< Key, Value, HashFunc, Equal >::operator++()
  {
    if (node_->next)
    {
      node_ = node_->next;
    }
    else
    {
      bucketIdx_++;
      advance();
    }
    return *this;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableConstIterator< Key, Value, HashFunc, Equal >::HashTableConstIterator(const HashTable< Key, Value, HashFunc, Equal > *t, size_t b, const HashTableNode< Key, Value > *n):
    table_(t),
    bucketIdx_(b),
    node_(n)
  {
    if (!node_ && table_)
    {
      advance();
    }
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTableConstIterator< Key, Value, HashFunc, Equal >::advance()
  {
    while (bucketIdx_ < table_->bucketCount_ && !table_->buckets_[bucketIdx_])
    {
      bucketIdx_++;
    }
    node_ = (bucketIdx_ < table_->bucketCount_) ? table_->buckets_[bucketIdx_] : nullptr;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableConstIterator< Key, Value, HashFunc, Equal >::HashTableConstIterator():
    table_(nullptr),
    bucketIdx_(0),
    node_(nullptr)
  {
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  const std::pair< Key, Value > &HashTableConstIterator< Key, Value, HashFunc, Equal >::operator*() const
  {
    return node_->kv;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  const std::pair< Key, Value > *HashTableConstIterator< Key, Value, HashFunc, Equal >::operator->() const
  {
    return &node_->kv;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  bool HashTableConstIterator< Key, Value, HashFunc, Equal >::operator!=(const HashTableConstIterator &rhs) const
  {
    return node_ != rhs.node_;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableConstIterator< Key, Value, HashFunc, Equal > &HashTableConstIterator< Key, Value, HashFunc, Equal >::operator++()
  {
    if (node_->next)
    {
      node_ = node_->next;
    }
    else
    {
      bucketIdx_++;
      advance();
    }
    return *this;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTable< Key, Value, HashFunc, Equal >::HashTable(size_t slots):
    buckets_(new Node*[slots]()),
    bucketCount_(slots),
    size_(0),
    hasher_(HashFunc()),
    equal_(Equal()),
    maxLoadFactor_(0.75)
  {
    for (size_t i = 0; i < bucketCount_; ++i)
    {
      buckets_[i] = nullptr;
    }
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTable< Key, Value, HashFunc, Equal >::HashTable(const HashTable &other):
    buckets_(new Node*[other.bucketCount_]()),
    bucketCount_(other.bucketCount_),
    size_(0),
    hasher_(other.hasher_),
    equal_(other.equal_),
    maxLoadFactor_(other.maxLoadFactor_)
  {
    try
    {
      for (size_t i = 0; i < bucketCount_; ++i)
      {
        Node *curr = other.buckets_[i];
        while (curr)
        {
          add(curr->kv.first, curr->kv.second);
          curr = curr->next;
        }
      }
    }
    catch (...)
    {
      clear();
      delete[] buckets_;
      throw;
    }
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTable< Key, Value, HashFunc, Equal >::~HashTable()
  {
    clear();
    delete[] buckets_;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTable< Key, Value, HashFunc, Equal > &HashTable< Key, Value, HashFunc, Equal >::operator=(const HashTable &other)
  {
    if (this != std::addressof(other))
    {
      HashTable temp(other);
      this->swap(temp);
    }
    return *this;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTable< Key, Value, HashFunc, Equal >::setMaxLoadFactor(double maxLoad)
  {
    maxLoadFactor_ = maxLoad;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTable< Key, Value, HashFunc, Equal >::add(const Key &k, const Value &v)
  {
    if (contains(k))
    {
      return;
    }
    if (static_cast< double >(size_ + 1) / bucketCount_ > maxLoadFactor_)
    {
      throw std::overflow_error("HashTable is full");
    }
    size_t idx = hasher_(k) % bucketCount_;
    buckets_[idx] = new Node(k, v, buckets_[idx]);
    ++size_;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  size_t HashTable< Key, Value, HashFunc, Equal >::erase(const Key &key)
  {
    size_t idx = hasher_(key) % bucketCount_;
    Node *curr = buckets_[idx];
    Node *prev = nullptr;

    while (curr)
    {
      if (equal_(curr->kv.first, key))
      {
        if (prev)
        {
          prev->next = curr->next;
        }
        else
        {
          buckets_[idx] = curr->next;
        }
        delete curr;
        --size_;
        return 1;
      }
      prev = curr;
      curr = curr->next;
    }
    return 0;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  bool HashTable< Key, Value, HashFunc, Equal >::contains(const Key &k) const
  {
    size_t idx = hasher_(k) % bucketCount_;
    Node *curr = buckets_[idx];
    while (curr)
    {
      if (equal_(curr->kv.first, k))
      {
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  bool HashTable< Key, Value, HashFunc, Equal >::empty() const
  {
    return size_ == 0;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  size_t HashTable< Key, Value, HashFunc, Equal >::capacity() const
  {
    return bucketCount_;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  size_t HashTable< Key, Value, HashFunc, Equal >::size() const
  {
    return size_;
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTable< Key, Value, HashFunc, Equal >::swap(HashTable &rhs) noexcept
  {
    std::swap(buckets_, rhs.buckets_);
    std::swap(bucketCount_, rhs.bucketCount_);
    std::swap(size_, rhs.size_);
    std::swap(hasher_, rhs.hasher_);
    std::swap(equal_, rhs.equal_);
    std::swap(maxLoadFactor_, rhs.maxLoadFactor_);
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTable< Key, Value, HashFunc, Equal >::clear()
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

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  void HashTable< Key, Value, HashFunc, Equal >::rehash(size_t slots)
  {
    if (slots == 0)
    {
      slots = 1;
    }
    HashTable temp(slots);
    temp.maxLoadFactor_ = maxLoadFactor_;
    for (size_t i = 0; i < bucketCount_; ++i)
    {
      Node *curr = buckets_[i];
      while (curr)
      {
        temp.add(curr->kv.first, curr->kv.second);
        curr = curr->next;
      }
    }
    this->swap(temp);
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableIterator< Key, Value, HashFunc, Equal > HashTable< Key, Value, HashFunc, Equal >::begin()
  {
    return Iterator(this, 0, buckets_[0]);
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableIterator< Key, Value, HashFunc, Equal > HashTable< Key, Value, HashFunc, Equal >::end()
  {
    return Iterator(this, bucketCount_, nullptr);
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableConstIterator< Key, Value, HashFunc, Equal > HashTable< Key, Value, HashFunc, Equal >::begin() const
  {
    return ConstIterator(this, 0, buckets_[0]);
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableConstIterator< Key, Value, HashFunc, Equal > HashTable< Key, Value, HashFunc, Equal >::end() const
  {
    return ConstIterator(this, bucketCount_, nullptr);
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableIterator< Key, Value, HashFunc, Equal > HashTable< Key, Value, HashFunc, Equal >::find(const Key &k)
  {
    size_t idx = hasher_(k) % bucketCount_;
    Node *curr = buckets_[idx];
    while (curr)
    {
      if (equal_(curr->kv.first, k))
      {
        return Iterator(this, idx, curr);
      }
      curr = curr->next;
    }
    return end();
  }

  template < typename Key, typename Value, typename HashFunc, typename Equal >
  HashTableConstIterator< Key, Value, HashFunc, Equal > HashTable< Key, Value, HashFunc, Equal >::find(const Key &k) const
  {
    size_t idx = hasher_(k) % bucketCount_;
    const Node *curr = buckets_[idx];
    while (curr)
    {
      if (equal_(curr->kv.first, k))
      {
        return ConstIterator(this, idx, curr);
      }
      curr = curr->next;
    }
    return end();
  }
}

#endif
