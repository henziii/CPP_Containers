#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_

#include <stdexcept>
#include <utility>

#include "s21_list.h"

namespace s21 {
template <class T>
class stack {
 public:
  // types
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using value_type = T;

  stack() : сontainer_() {}

  stack(const stack &q) : сontainer_(q.сontainer_) {}

  stack(stack &&q) : сontainer_(std::move(q.сontainer_)) {}

  stack(std::initializer_list<value_type> const &items) : сontainer_(items) {}

  stack &operator=(stack &&q) { сontainer_ = std::move(q.сontainer_); }

  ~stack() {}

  // element_access
  const_reference top() const {
    if (сontainer_.empty()) {
      throw std::runtime_error("Stack is empty");
    }
    return сontainer_.back();
  }

  // capacity
  bool empty() const { return сontainer_.empty(); }

  size_type size() const { return сontainer_.size(); }

  // modifiers
  void push(const_reference value) { сontainer_.push_back(value); }

  void pop() {
    if (сontainer_.empty()) {
      throw std::runtime_error("Stack is empty");
    }
    сontainer_.pop_back();
  }

  void swap(stack &other) noexcept { сontainer_.swap(other.сontainer_); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    сontainer_.insert_many_front(args...);
  }

 private:
  s21::list<T> сontainer_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_STACK_H_