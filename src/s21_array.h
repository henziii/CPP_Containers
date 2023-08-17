#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T, size_t Size>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() {}

  array(std::initializer_list<value_type> const &items) {
    if (items.size() > Size) {
      throw std::out_of_range("Out of range");
    }
    int i = 0;
    for (auto &&value : items) {
      elems_[i++] = value;
    }
  }
  array(const array &a) = default;

  array(array &&a) = default;

  array &operator=(array &&a) = default;
  array &operator=(const array &a) = default;

  ~array() = default;

  reference at(size_type pos) {
    if (pos >= Size) {
      throw std::out_of_range("Out of range");
    }
    return elems_[pos];
  }

  reference operator[](size_type pos) { return elems_[pos]; }

  const_reference front() { return elems_[0]; }
  const_reference back() { return elems_[Size - 1]; }

  iterator data() { return elems_; }

  iterator begin() { return iterator(data()); }
  iterator end() { return iterator(data() + Size); }

  bool empty() { return Size == 0; }
  size_type size() { return Size; }
  size_type max_size() { return Size; }

  void swap(array &other) {
    std::swap_ranges(elems_, elems_ + Size, other.elems_);
  }

  void fill(const_reference value) {
    for (auto &&i : elems_) {
      i = value;
    }
  }

 private:
  value_type elems_[Size]{};
};

template <typename T>
class array<T, 0> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() {}

  array(std::initializer_list<value_type> const &items) {
    throw std::out_of_range("Array is zero size");
  }
  array(const array &a) = default;

  array(array &&a) = default;

  array &operator=(array &&a) = default;
  array &operator=(const array &a) = default;

  ~array() = default;

  reference at(size_type) {
    throw std::out_of_range(
        "Cannot call array<T, 0>::at(); Array is zero size");
  }

  reference operator[](size_type) {
    throw std::out_of_range(
        "Cannot call array<T, 0>::operator[]; Array is zero size");
  }

  const_reference front() {
    throw std::out_of_range(
        "Cannot call array<T, 0>::front(); Array is zero size");
  }
  const_reference back() {
    throw std::out_of_range(
        "Cannot call array<T, 0>::back(); Array is zero size");
  }

  iterator data() { return nullptr; }

  iterator begin() { return iterator(data()); }
  iterator end() { return iterator(data()); }

  bool empty() { return true; }
  size_type size() { return 0; }
  size_type max_size() { return 0; }

  void swap(array) {
    throw std::out_of_range(
        "Cannot call array<T, 0>::swap(); Array is zero size");
  }

  void fill(const_reference) {
    throw std::out_of_range(
        "Cannot call array<T, 0>::fill(); Array is zero size");
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_