#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_

#include <list>
#include <utility>

#include "s21_list.h"

namespace s21 {
template <class T>
class queue {
 public:
  // types
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using value_type = T;

  queue() : сontainer_() {}

  queue(const queue &q) : сontainer_(q.сontainer_) {}

  queue(queue &&q) : сontainer_(q.сontainer_) { q.сontainer_ = nullptr; }

  queue(std::initializer_list<value_type> const &items)
      : сontainer_(items.begin(), items.end()) {}

  queue<T> &operator=(queue &&q) {
    if (this != q) {
      сontainer_ = q.сontainer_;
    }
    return *this;
  }

  ~queue() {}

  const_reference front() const { return сontainer_.front(); }

  const_reference back() const { return сontainer_.back(); }

  bool empty() const { return сontainer_.empty(); }

  size_type size() const { return сontainer_.size(); }

  void push(const_reference value) { сontainer_.push_back(value); }

  void pop() { сontainer_.pop_front(); }

  void swap(queue &other) noexcept { сontainer_.swap(other.сontainer_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    сontainer_.insert_many_back(args...);
  }

 private:
  s21::list<T> сontainer_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_