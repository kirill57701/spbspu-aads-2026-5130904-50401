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
