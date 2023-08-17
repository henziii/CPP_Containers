#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_ITERATOR_H_

#include "s21_list_node.h"

namespace s21 {

template <typename T>
class list;

template <typename T>
class ListConstIterator;

template <typename T>
class ListIterator {
 public:
  using value_type = T;
  using reference = T &;
  using Node = ListNode<value_type>;

  friend class list<T>;
  friend class ListConstIterator<T>;

  ListIterator() : ptr_{nullptr} {}

  ListIterator(Node *ptr) : ptr_{ptr} {}

  ListIterator(const ListIterator &other) = default;

  ListIterator(ListIterator &&other) = default;

  ListIterator &operator=(const ListIterator &other) = default;

  ListIterator &operator=(ListIterator &&other) = default;

  ~ListIterator() {}

  reference operator*() const { return ptr_->get_value_ref(); }

  ListIterator &operator++() {
    ptr_ = ptr_->get_next();
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp(*this);
    ptr_ = ptr_->get_next();
    return temp;
  }

  ListIterator &operator--() {
    ptr_ = ptr_->get_prev();
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator temp(*this);
    ptr_ = ptr_->get_prev();
    return temp;
  }

  bool operator==(const ListIterator &other) const {
    return this->ptr_ == other.ptr_;
  }

  bool operator!=(const ListIterator &other) const {
    return this->ptr_ != other.ptr_;
  }

 private:
  Node *ptr_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_ITERATOR_H_