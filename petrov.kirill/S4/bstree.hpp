#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <stdexcept>
#include <functional>
#include <utility>

namespace petrov {
  template< class Key, class Value >
  struct BSTNode {
    Key key;
    Value value;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;
  };

template< class Key, class Value >
  class BSTConstIterator {
  public:
    BSTNode< Key, Value >* node_;
    BSTNode< Key, Value >* nil_;
    BSTNode< Key, Value >* header_;

    BSTConstIterator(BSTNode< Key, Value >* n, BSTNode< Key, Value >* nil_ptr, BSTNode< Key, Value >* header_ptr):
      node_(n),
      nil_(nil_ptr),
      header_(header_ptr)
    {}

    const BSTNode< Key, Value >* operator->() const {
      return node_;
    }

    const BSTNode< Key, Value >& operator*() const {
      return *node_;
    }

    BSTConstIterator& operator++() {
      if (node_ == header_) {
        return *this;
      }
      if (node_->right != nil_) {
        node_ = node_->right;
        while (node_->left != nil_) {
          node_ = node_->left;
        }
      } else {
        BSTNode< Key, Value >* p = node_->parent;
        while (p != header_ && node_ == p->right) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    bool operator!=(const BSTConstIterator& other) const {
      return node_ != other.node_;
    }

    bool operator==(const BSTConstIterator& other) const {
      return node_ == other.node_;
    }
  };

  template< class Key, class Value >
  class BSTIterator: public BSTConstIterator< Key, Value > {
  public:
    BSTIterator(BSTNode< Key, Value >* n, BSTNode< Key, Value >* nil_ptr, BSTNode< Key, Value >* header_ptr):
      BSTConstIterator< Key, Value >(n, nil_ptr, header_ptr)
    {}

    BSTNode< Key, Value >* operator->() {
      return this->node_;
    }

    BSTNode< Key, Value >& operator*() {
      return *(this->node_);
    }

    BSTIterator& operator++() {
      BSTConstIterator< Key, Value >::operator++();
      return *this;
    }
  };

  template< class Key, class Value, class Compare = std::less< Key > >
  class BSTree {
  private:
    BSTNode< Key, Value >* header_;
    BSTNode< Key, Value >* nil_;
    Compare comp_;

    void init() {
      nil_ = new BSTNode< Key, Value >{Key(), Value(), nullptr, nullptr, nullptr};
      nil_->left = nil_->right = nil_->parent = nil_;
      header_ = new BSTNode< Key, Value >{Key(), Value(), nil_, nil_, nil_};
    }

    void clear(BSTNode< Key, Value >* node) {
      if (node != nil_) {
        clear(node->left);
        clear(node->right);
        delete node;
      }
    }

    BSTNode< Key, Value >* copyTree(BSTNode< Key, Value >* other_node, BSTNode< Key, Value >* parent, BSTNode< Key, Value >* other_nil) {
      if (other_node == other_nil) {
        return nil_;
      }
      BSTNode< Key, Value >* new_node = new BSTNode< Key, Value >{other_node->key, other_node->value, nil_, nil_, parent};
      new_node->left = copyTree(other_node->left, new_node, other_nil);
      new_node->right = copyTree(other_node->right, new_node, other_nil);
      return new_node;
    }
  public:
    BSTree() {
      init();
    }

    ~BSTree() {
      if (header_) {
        clear(header_->left);
        delete header_;
      }
      if (nil_) {
        delete nil_;
      }
    }

    using const_iterator = BSTConstIterator< Key, Value >;
    using iterator = BSTIterator< Key, Value >;

    const_iterator cbegin() const {
      BSTNode< Key, Value >* curr = header_->left;
      if (curr == nil_) {
        return const_iterator(header_, nil_, header_);
      }
      while (curr->left != nil_) {
        curr = curr->left;
      }
      return const_iterator(curr, nil_, header_);
    }

    const_iterator cend() const {
      return const_iterator(header_, nil_, header_);
    }
    BSTree(const BSTree& other):
      comp_(other.comp_)
    {
      init();
      if (other.header_->left != other.nil_) {
        header_->left = copyTree(other.header_->left, header_, other.nil_);
      }
    }

    BSTree(BSTree&& other) noexcept:
      header_(other.header_),
      nil_(other.nil_),
      comp_(std::move(other.comp_))
    {
      other.init();
    }

    BSTree& operator=(BSTree other) {
      std::swap(comp_, other.comp_);
      std::swap(header_, other.header_);
      std::swap(nil_, other.nil_);
      return *this;
    }
bool has(Key k) const {
      BSTNode< Key, Value >* z = header_->left;
      while (z != nil_) {
        if (comp_(k, z->key)) {
          z = z->left;
        } else if (comp_(z->key, k)) {
          z = z->right;
        } else {
          return true;
        }
      }
      return false;
    }

    void push(Key k, Value v) {
      BSTNode< Key, Value >* z = new BSTNode< Key, Value >{k, v, nil_, nil_, nil_};
      BSTNode< Key, Value >* y = header_;
      BSTNode< Key, Value >* x = header_->left;
      while (x != nil_) {
        y = x;
        if (comp_(k, x->key)) {
          x = x->left;
        } else if (comp_(x->key, k)) {
          x = x->right;
        } else {
          x->value = v;
          delete z;
          return;
        }
      }
      z->parent = y;
      if (y == header_) {
        header_->left = z;
      } else if (comp_(z->key, y->key)) {
        y->left = z;
      } else {
        y->right = z;
      }
    }

    Value get(Key k) const {
      BSTNode< Key, Value >* z = header_->left;
      while (z != nil_) {
        if (comp_(k, z->key)) {
          z = z->left;
        } else if (comp_(z->key, k)) {
          z = z->right;
        } else {
          return z->value;
        }
      }
      throw std::out_of_range("Key not found");
    }
  };
}

#endif
