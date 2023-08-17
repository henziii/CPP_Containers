#ifndef CPP2_S21_CONTAINERS_1_SRC_AVL_TREE_NODE_H_
#define CPP2_S21_CONTAINERS_1_SRC_AVL_TREE_NODE_H_

#include "avl_tree.h"

namespace s21 {

template <typename T>
class AVLTreeNode {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using Node = AVLTreeNode<value_type>;
  using size_type = std::size_t;

  AVLTreeNode(const_reference value, Node* parent, Node* end, size_type height)
      : value_{value},
        left_{end},
        right_{end},
        parent_{parent},
        height_{height} {};

  ~AVLTreeNode() {
    if (this->height_ > 1) {
      if (this->left_->height_ != 0) delete this->left_;
      if (this->right_->height_ != 0) delete this->right_;
    }
  }

  //гетеры
  const_reference get_value() noexcept { return this->value_; }
  Node*& get_left_node() noexcept { return this->left_; }
  Node*& get_right_node() noexcept { return this->right_; }
  Node*& get_parent_node() noexcept { return this->parent_; }
  size_type get_height(Node* node) noexcept { return node ? node->height_ : 0; }

  //сетеры
  void set_value(value_type val) noexcept { this->value_ = val; }
  void set_height(size_type height) noexcept { this->height_ = height; }
  void set_parent(Node* node) noexcept { this->parent_ = node; }
  void set_left(Node* node) noexcept { this->left_ = node; }
  void set_right(Node* node) noexcept { this->right_ = node; }

 private:
  value_type value_;
  Node* left_;
  Node* right_;
  Node* parent_;
  size_type height_;

  AVLTreeNode(){};
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_AVL_TREE_NODE_H_