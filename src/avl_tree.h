#ifndef CPP2_S21_CONTAINERS_1_SRC_AVL_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_AVL_TREE_H_

#include <exception>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "avl_tree_node.h"

#define kLeft true
#define kRight false
#define kSet true
#define kMap true
#define kMultiset false
#define kErase true
#define kInsert false

namespace s21 {

template <typename T>
class Compare {
 public:
  int8_t operator()(const T& a, const T& b) const noexcept {
    return a < b ? 1 : (a > b ? 2 : 0);
  }
};

template <typename T, typename Comparator = Compare<T>>
class AVLTree {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using Node = AVLTreeNode<value_type>;

  class container_is_full : public std::exception {
   public:
    container_is_full(const char* error) : ex_{error} {}
    void what() noexcept { std::cerr << ex_ << std::endl; }

   private:
    const char* ex_;
  };

  class base_const_iterator {
   public:
    friend class AVLTree<value_type, Comparator>;

    base_const_iterator() noexcept : iter_{nullptr}, obj_{nullptr} {}
    base_const_iterator(const base_const_iterator& obj) noexcept
        : iter_{obj.iter_}, obj_{obj.obj_} {}
    explicit base_const_iterator(Node* node, const AVLTree* obj) noexcept
        : iter_{node}, obj_{obj} {}
    base_const_iterator& operator=(const base_const_iterator& other) {
      if (*this != other) {
        this->iter_ = other.iter_;
        this->obj_ = other.obj_;
      }
      return *this;
    }

    const_reference operator*() noexcept { return iter_->get_value(); }
    bool operator!=(const base_const_iterator& other) noexcept {
      return this->iter_ != other.iter_;
    }
    bool operator==(const base_const_iterator& other) noexcept {
      return this->iter_ == other.iter_;
    }

    base_const_iterator operator++() {
      (*this)++;
      return *this;
    }
    base_const_iterator operator++(int) {
      if (iter_ && obj_ && (obj_->root_ != obj_->end_)) {
        base_const_iterator buff(*this);
        if (iter_->get_right_node() != obj_->end_ && iter_ != obj_->end_) {
          iter_ = iter_->get_right_node();
          while (iter_->get_left_node() != obj_->end_) {
            iter_ = iter_->get_left_node();
          }
        } else {
          Node* temp = iter_->get_parent_node();
          while (temp != obj_->end_ && iter_ == temp->get_right_node()) {
            iter_ = temp;
            temp = temp->get_parent_node();
          }
          iter_ = temp;
        }
        return buff;
      }
      return *this;
    }

    base_const_iterator operator--() {
      (*this)--;
      return *this;
    }
    base_const_iterator operator--(int) {
      if (iter_ && obj_ && (obj_->root_ != obj_->end_)) {
        base_const_iterator buff(*this);
        if (iter_ != obj_->start_) {
          if (iter_ == obj_->end_) {
            iter_ = obj_->end_->get_parent_node();
          } else {
            if (iter_->get_left_node() != obj_->end_ && iter_ != obj_->end_) {
              iter_ = iter_->get_left_node();
              while (iter_->get_right_node() != obj_->end_) {
                iter_ = iter_->get_right_node();
              }
            } else {
              Node* temp = iter_->get_parent_node();
              while (temp != obj_->end_ && iter_ == temp->get_left_node()) {
                iter_ = temp;
                temp = temp->get_parent_node();
              }
              iter_ = temp;
            }
          }
        } else {
          iter_ = obj_->end_;
        }
        return buff;
      }
      return *this;
    }

   protected:
    Node* iter_;
    const AVLTree<value_type, Comparator>* obj_;
  };

  using base_iterator = base_const_iterator;

 public:
  AVLTree();
  AVLTree(std::initializer_list<value_type> const& items, bool container_type);
  AVLTree(const AVLTree<value_type, Comparator>& other);
  AVLTree(AVLTree<value_type, Comparator>&& other);

  AVLTree<value_type, Comparator>& operator=(
      AVLTree<value_type, Comparator>&& other);
  AVLTree<value_type, Comparator>& operator=(
      AVLTree<value_type, Comparator>& other);

  virtual ~AVLTree();

  base_iterator begin() const noexcept;
  base_iterator end() const noexcept;
  base_const_iterator cbegin() const noexcept {
    return (base_const_iterator)begin();
  }
  base_const_iterator cend() const noexcept {
    return (base_const_iterator)end();
  }

  bool empty() const noexcept;
  size_type size() const noexcept;
  virtual size_type max_size() const noexcept;
  void clear() noexcept;
  void erase(base_const_iterator pos) noexcept;
  void erase(const_reference value) noexcept;
  void swap(AVLTree<value_type, Comparator>& other) noexcept;

  base_iterator find(const_reference value) const noexcept;
  bool contains(const_reference value) const noexcept;

  const_reference get_start() noexcept;
  const_reference get_finish() noexcept;

  virtual void print() const noexcept {}

 protected:
  void merge(AVLTree<value_type, Comparator>& other, bool container_type);
  void insert(const_reference value, const bool& container_type,
              bool* result_of_insertion = nullptr,
              base_iterator* place_of_insertion = nullptr);

  void Insert(const_reference value, Node** root, const bool& container_type,
              bool* result_of_insertion = nullptr,
              base_iterator* place_of_insertion = nullptr);
  void CreateNode(Node*& (Node::*func)(void), const_reference value,
                  Node** root, const bool& flag, const bool& container_type,
                  bool* result_of_insertion = nullptr,
                  base_iterator* place_of_insertion = nullptr);
  int8_t BFactor(Node& root);
  void CorrectHeight(Node& root);
  void RotateRight(Node** root, bool& flag);
  void RotateLeft(Node** root, bool& flag);
  void Balance(Node** root, bool flag);
  void BalanceAfterRemove(Node* node) noexcept;

  bool DeleteList(base_const_iterator& it) noexcept;
  void DeleteRootList() noexcept;
  void DeleteStart() noexcept;
  void DeleteFinish() noexcept;
  void DeleteListNode(base_const_iterator& it, bool child_position) noexcept;
  bool CheckChildPosition(base_const_iterator& it) const noexcept;
  Node* FindReplacement(Node* curr) const noexcept;
  void FindAndDeleteReplacement(Node* curr, base_const_iterator pos) noexcept;

 protected:
  Node* root_;
  Node* end_;
  Node* start_;
  Node* finish_;
  size_type size_;
  Comparator comparator;
};

template <typename value_type, typename Comparator>
typename AVLTree<value_type, Comparator>::base_iterator
AVLTree<value_type, Comparator>::begin() const noexcept {
  return AVLTree<value_type, Comparator>::base_iterator(
      this->start_, (const AVLTree<value_type, Comparator>*)this);
}

template <typename value_type, typename Comparator>
typename AVLTree<value_type, Comparator>::base_iterator
AVLTree<value_type, Comparator>::end() const noexcept {
  return AVLTree<value_type, Comparator>::base_iterator(
      this->end_, (const AVLTree<value_type, Comparator>*)this);
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>::AVLTree()
    : end_{new Node(value_type{}, nullptr, nullptr, 0)} {
  end_->set_left(end_);
  end_->set_right(end_);
  root_ = start_ = finish_ = end_;
  size_ = 0;
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>::AVLTree(
    std::initializer_list<value_type> const& items, bool container_type)
    : AVLTree<value_type, Comparator>::AVLTree() {
  if (items.size() != 0) {
    bool temp{};
    root_ = start_ = finish_ = nullptr;
    for (auto& value : items) {
      this->insert(value, container_type, &temp);
    }
  }
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>::AVLTree(const AVLTree& other) : AVLTree() {
  bool temp{};
  for (base_const_iterator iter = other.begin(); iter != other.end(); iter++) {
    this->insert(*iter, kMultiset, &temp);
  }
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>::AVLTree(
    AVLTree<value_type, Comparator>&& other)
    : root_{other.root_},
      end_{other.end_},
      start_{other.start_},
      finish_{other.finish_},
      size_{other.size_} {
  other.end_ = nullptr;
  other.end_ = new Node(value_type{}, nullptr, nullptr, 0);
  other.end_->set_left(end_);
  other.end_->set_right(end_);
  other.root_ = other.start_ = other.finish_ = other.end_;
  other.size_ = 0;
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::swap(
    AVLTree<value_type, Comparator>& other) noexcept {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(end_, other.end_);
    std::swap(start_, other.start_);
    std::swap(finish_, other.finish_);
    std::swap(size_, other.size_);
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::merge(
    AVLTree<value_type, Comparator>& other, bool container_type) {
  bool temp{};
  for (base_const_iterator iter = other.begin(); iter != other.end(); iter++) {
    this->insert(*iter, container_type, &temp);
  }
  other.clear();
}

template <typename value_type, typename Comparator>
typename AVLTree<value_type, Comparator>::base_iterator
AVLTree<value_type, Comparator>::find(const_reference value) const noexcept {
  Node* temp = root_;
  while (temp != end_) {
    if (comparator(value, temp->get_value()) == 1) {
      temp = temp->get_left_node();
    } else if (comparator(value, temp->get_value()) == 2) {
      temp = temp->get_right_node();
    } else {
      return base_iterator(temp, this);
    }
  }
  return base_iterator(end_, this);
}

template <typename value_type, typename Comparator>
bool AVLTree<value_type, Comparator>::contains(
    const_reference value) const noexcept {
  base_iterator check_end(end_, this);
  if (find(value) == check_end) {
    return false;
  }
  return true;
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>& AVLTree<value_type, Comparator>::operator=(
    AVLTree<value_type, Comparator>&& other) {
  if (this != &other) {
    AVLTree temp(std::move(other));
    swap(temp);
  }
  return *this;
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>& AVLTree<value_type, Comparator>::operator=(
    AVLTree<value_type, Comparator>& other) {
  if (this != &other) {
    clear();
    AVLTree<value_type, Comparator> temp(other);
    swap(temp);
  }
  return *this;
}

template <typename value_type, typename Comparator>
AVLTree<value_type, Comparator>::~AVLTree() {
  clear();
  delete end_;
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::clear() noexcept {
  if (root_ != end_) {
    delete root_;
    size_ = 0;
    root_ = start_ = finish_ = end_;
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::erase(base_const_iterator pos) noexcept {
  if (pos.iter_ != end_) {
    Node* left_child = pos.iter_->get_left_node();
    Node* right_child = pos.iter_->get_right_node();
    bool existence_left =
        (left_child != end_);  // true - если у pos существует левый ребенок
    bool existence_right =
        (right_child != end_);  // true - если у pos существует правый ребенок
    if (!existence_left && !existence_right /* если у pos нет детей */) {
      if (DeleteList(pos) == true) {
        size_--;
      }
    } else if (existence_left &&
               existence_right /* если у pos есть оба ребенка */) {
      FindAndDeleteReplacement(FindReplacement(left_child), pos);
    } else if (existence_left /* если у pos есть только левый ребенок */) {
      FindAndDeleteReplacement(left_child, pos);
    } else if (existence_right /* если у pos есть только правый ребенок */) {
      FindAndDeleteReplacement(right_child, pos);
    }
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::erase(const_reference value) noexcept {
  base_const_iterator curr = this->find(value);
  if (curr.iter_ != end_) {
    this->erase(curr);
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::FindAndDeleteReplacement(
    Node* child, base_const_iterator pos) noexcept {
  base_const_iterator replacement(child, this);
  pos.iter_->set_value(child->get_value());
  erase(replacement);
}

template <typename value_type, typename Comparator>
typename AVLTree<value_type, Comparator>::Node*
AVLTree<value_type, Comparator>::FindReplacement(Node* curr) const noexcept {
  Node* max_left_subtree{nullptr};
  if (curr->get_right_node() == end_) {
    return curr;
  } else {
    max_left_subtree = curr->get_right_node();
    while (max_left_subtree->get_right_node() != end_) {
      max_left_subtree = max_left_subtree->get_right_node();
    }
  }
  return max_left_subtree;
}

template <typename value_type, typename Comparator>
bool AVLTree<value_type, Comparator>::DeleteList(
    base_const_iterator& it) noexcept {
  if (size_) {
    if (size_ == 1) {
      DeleteRootList();
    } else if (it.iter_ == start_) {
      DeleteStart();
    } else if (it.iter_ == finish_) {
      DeleteFinish();
    } else {
      DeleteListNode(it, CheckChildPosition(it));
    }
    return true;
  }
  return false;
}

template <typename value_type, typename Comparator>
bool AVLTree<value_type, Comparator>::CheckChildPosition(
    base_const_iterator& it) const noexcept {
  bool child_position{kRight};
  if (it.iter_ == it.iter_->get_parent_node()->get_left_node()) {
    child_position = kLeft;
  }
  return child_position;
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::BalanceAfterRemove(Node* node) noexcept {
  Node* temp = node;
  do {
    temp = temp->get_parent_node();
    CorrectHeight(*temp);
    Balance(&temp, kErase);
  } while (temp != root_);
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::DeleteRootList() noexcept {
  delete root_;
  root_ = start_ = finish_ = end_;
  end_->set_parent(end_);
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::DeleteStart() noexcept {
  Node* new_start = start_->get_parent_node();
  Node* buff = start_;
  new_start->set_left(end_);
  start_ = new_start;
  BalanceAfterRemove(buff);
  delete buff;
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::DeleteFinish() noexcept {
  Node* new_finish = finish_->get_parent_node();
  new_finish->set_right(end_);
  end_->set_parent(new_finish);
  delete finish_;
  finish_ = new_finish;
  BalanceAfterRemove(new_finish->get_right_node());
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::DeleteListNode(
    base_const_iterator& it, bool child_position) noexcept {
  Node* parent = it.iter_->get_parent_node();
  if (child_position == kLeft) {
    parent->set_left(end_);
  } else {
    parent->set_right(end_);
  }
  BalanceAfterRemove(it.iter_);
  delete it.iter_;
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::insert(
    const_reference value, const bool& container_type,
    bool* result_of_insertion, base_iterator* place_of_insertion) {
  if (this->size_ < this->max_size()) {
    Insert(value, &root_, container_type, result_of_insertion,
           place_of_insertion);
  } else {
    throw container_is_full("В контейнере закончилось место");
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::Insert(
    const_reference value, Node** root, const bool& container_type,
    bool* result_of_insertion, base_iterator* place_of_insertion) {
  if (this->empty()) {
    root_ = nullptr;
    root_ = new Node(value, end_, end_, 1);
    end_->set_parent(root_);
    start_ = finish_ = root_;
    size_ = 1;
    if (place_of_insertion) {
      place_of_insertion->iter_ = root_;
      place_of_insertion->obj_ = this;
    }
    *result_of_insertion = true;
  } else {
    int8_t res_compare = comparator(value, (*root)->get_value());
    if (res_compare == 1) {
      CreateNode(&Node::get_left_node, value, root, kLeft, container_type,
                 result_of_insertion, place_of_insertion);
    } else if (res_compare == 2 ||
               (res_compare == 0 && container_type == kMultiset)) {
      CreateNode(&Node::get_right_node, value, root, kRight, container_type,
                 result_of_insertion, place_of_insertion);
    } else {
      if (container_type == kSet || container_type == kMap) {
        if (place_of_insertion) {
          place_of_insertion->iter_ = *root;
          place_of_insertion->obj_ = this;
        }
        *result_of_insertion = false;
      }
    }
    CorrectHeight(**root);
    Balance(root, kInsert);
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::CreateNode(
    Node*& (Node::*func)(void), const_reference value, Node** root,
    const bool& flag, const bool& container_type, bool* result_of_insertion,
    base_iterator* place_of_insertion) {
  Node*& ptr = ((*root)->*func)();
  if (ptr == this->end_) {
    Node* temp = new Node(value, *root, this->end_, 1);

    if (flag == kLeft) {
      (*root)->set_left(temp);
    } else {
      (*root)->set_right(temp);
      if (temp->get_value() >= finish_->get_value()) {
        this->end_->set_parent(temp);
      }
    }

    if (temp->get_value() < start_->get_value()) {
      start_ = temp;
    }
    if (temp->get_value() >= finish_->get_value()) {
      finish_ = temp;
    }

    size_++;

    if (place_of_insertion) {
      place_of_insertion->iter_ = temp;
      place_of_insertion->obj_ = this;
    }
    *result_of_insertion = true;
  } else {
    Insert(value, (&((*root)->*func)()), container_type, result_of_insertion,
           place_of_insertion);
  }
}

template <typename value_type, typename Comparator>
bool AVLTree<value_type, Comparator>::empty() const noexcept {
  return (root_ == end_) || (root_ == nullptr);
}

template <typename value_type, typename Comparator>
size_t AVLTree<value_type, Comparator>::size() const noexcept {
  return this->size_;
}

template <typename value_type, typename Comparator>
size_t AVLTree<value_type, Comparator>::max_size() const noexcept {
  return (std::numeric_limits<size_t>::max()) / sizeof(value_type) / 20;
}

template <typename value_type, typename Comparator>
const value_type& AVLTree<value_type, Comparator>::get_start() noexcept {
  return this->start_->get_value();
}

template <typename value_type, typename Comparator>
const value_type& AVLTree<value_type, Comparator>::get_finish() noexcept {
  return this->finish_->get_value();
}

template <typename value_type, typename Comparator>
int8_t AVLTree<value_type, Comparator>::BFactor(Node& root) {
  return root.get_height(root.get_left_node()) -
         root.get_height(root.get_right_node());
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::CorrectHeight(Node& root) {
  size_type left_height = root.get_height(root.get_left_node());
  size_type right_height = root.get_height(root.get_right_node());
  root.set_height((left_height > right_height ? left_height : right_height) +
                  1);
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::Balance(Node** root, bool flag) {
  int8_t balance = BFactor(**root);
  if (balance == 2) {
    if (BFactor(*(*root)->get_left_node()) < 0) {
      RotateLeft(&(*root)->get_left_node(), flag);
    }
    RotateRight(root, flag);

  } else if (balance == -2) {
    if (BFactor(*(*root)->get_right_node()) > 0) {
      RotateRight(&(*root)->get_right_node(), flag);
    }
    RotateLeft(root, flag);
  }
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::RotateRight(Node** root, bool& flag) {
  Node* temp_root = *root;
  *root = (*root)->get_left_node();

  if (this->root_ == temp_root || this->root_ == temp_root) {
    this->root_ = *root;
    (*root)->set_parent(this->end_);
  } else {
    (*root)->set_parent(temp_root->get_parent_node());
    if (flag == kErase) {
      Node* temp_parent = temp_root->get_parent_node();
      if (temp_root == temp_parent->get_right_node())
        temp_parent->set_right(*root);
      else
        temp_parent->set_left(*root);
    }
  }

  temp_root->set_left((*root)->get_right_node());
  if (temp_root->get_left_node() != end_) {
    temp_root->get_left_node()->set_parent(temp_root);
  }
  temp_root->set_parent(*root);
  (*root)->set_right(temp_root);
  CorrectHeight(*temp_root);
  CorrectHeight(**root);
}

template <typename value_type, typename Comparator>
void AVLTree<value_type, Comparator>::RotateLeft(Node** root, bool& flag) {
  Node* temp_root = *root;
  *root = (*root)->get_right_node();

  if (this->root_ == *root || this->root_ == temp_root) {
    this->root_ = *root;
    (*root)->set_parent(this->end_);
  } else {
    (*root)->set_parent(temp_root->get_parent_node());
    if (flag == kErase) {
      Node* temp_parent = temp_root->get_parent_node();
      if (temp_root == temp_parent->get_right_node())
        temp_parent->set_right(*root);
      else
        temp_parent->set_left(*root);
    }
  }

  temp_root->set_right((*root)->get_left_node());
  if (temp_root->get_right_node() != end_) {
    temp_root->get_right_node()->set_parent(temp_root);
  }
  temp_root->set_parent(*root);
  (*root)->set_left(temp_root);
  CorrectHeight(*temp_root);
  CorrectHeight(**root);
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_AVL_TREE_H_
