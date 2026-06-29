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
  };
}

#endif
