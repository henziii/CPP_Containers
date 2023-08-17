#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_CONST_ITERATOR_H_

#include "s21_list_iterator.h"
#include "s21_list_node.h"

namespace s21 {
template <typename T>
class list;

template <typename T>
class ListConstIterator {
 public:
  using value_type = T;
  using reference = const T &;
  using Node = ListNode<value_type>;
  friend class list<T>;

  ListConstIterator() : ptr_{nullptr} {}

  ListConstIterator(Node *ptr) : ptr_{ptr} {}

  ListConstIterator(const ListConstIterator &other) = default;

  ListConstIterator(const ListIterator<value_type> &other) : ptr_{other.ptr_} {}

  ListConstIterator(ListConstIterator &&other) = default;

  ListConstIterator &operator=(const ListConstIterator &other) = default;

  ListConstIterator &operator=(ListConstIterator &&other) = default;

  ~ListConstIterator() {}

  reference operator*() const { return ptr_->get_value(); }

  ListConstIterator &operator++() {
    ptr_ = ptr_->get_next();
    return *this;
  }

  ListConstIterator operator++(int) {
    ListConstIterator temp(*this);
    ptr_ = ptr_->get_next();
    return temp;
  }

  ListConstIterator &operator--() {
    ptr_ = ptr_->get_prev();
    return *this;
  }

  ListConstIterator operator--(int) {
    ListConstIterator temp(*this);
    ptr_ = ptr_->get_prev();
    return temp;
  }

  bool operator==(const ListConstIterator &other) const {
    return this->ptr_ == other.ptr_;
  }

  bool operator!=(const ListConstIterator &other) const {
    return this->ptr_ != other.ptr_;
  }

 private:
  Node *ptr_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_S21_LIST_CONST_ITERATOR_H_