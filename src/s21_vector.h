#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_VECTOR_H_

#include <stddef.h>

#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class vector {
 public:
  // types
  using size_type = size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;

  vector() : size_(0), capacity_(3), pointer_(nullptr) {}

  vector(size_type n) : size_(n), capacity_(2 * n), pointer_(new T[n]) {}

  vector(const vector& v) noexcept
      : size_(v.size_), capacity_(v.capacity_), pointer_(new T[v.capacity_]) {
    for (int i = 0; i < v.size_; i++) {
      pointer_[i] = v.pointer_[i];
    }
  }

  vector(vector&& v) noexcept
      : size_(v.size_), capacity_(v.capacity_), pointer_(v.pointer_) {
    v.size_ = 0;
    v.capacity_ = 0;
    v.pointer_ = nullptr;
  }

  vector(std::initializer_list<value_type> const& items)
      : size_(items.size()),
        capacity_(items.size()),
        pointer_(new T[capacity_]) {
    std::uninitialized_copy(items.begin(), items.end(), pointer_);
  }

  vector<T>& operator=(vector&& v) {
    if (this != &v) {
      delete[] pointer_;
      size_ = std::exchange(v.size_, 0);
      capacity_ = std::exchange(v.capacity_, 0);
      pointer_ = std::exchange(v.pointer_, nullptr);
    }
    return *this;
  }

  ~vector() { delete[] pointer_; }

  reference at(size_type pos) {
    if (pos > size_) {
      throw std::length_error("Incorrect input");
    }
    return pointer_[pos];
  }

  reference operator[](size_type pos) { return pointer_[pos]; }

  const_reference front() const { return pointer_[0]; }

  const_reference back() const { return pointer_[size_ - 1]; }

  iterator data() noexcept { return pointer_; }

  bool empty() const noexcept { return (size_ == 0); }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  void reserve(size_type size) {
    if (pointer_ == 0) {
      size_ = 0;
      capacity_ = 0;
    }
    T* Newbuffer = new T[size];

    int l_Size = size < size_ ? size : size_;

    for (int i = 0; i < l_Size; i++) {
      Newbuffer[i] = pointer_[i];
    }

    capacity_ = size;
    delete[] pointer_;
    pointer_ = Newbuffer;
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      T* newPointer = new T[size_];
      for (size_type i = 0; i < size_; ++i) {
        newPointer[i] = pointer_[i];
      }
      capacity_ = size_;
      delete[] pointer_;
      pointer_ = newPointer;
    }
  }

  void clear() noexcept {
    delete[] pointer_;
    pointer_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  bool operator==(vector& v) {
    if (size() != v.size()) {
      return false;
    }
    for (size_t i = 0; i < size(); ++i) {
      if ((*this)[i] != v[i]) {
        return false;
      }
    }
    return true;
  }

  iterator insert(iterator pos, const_reference value) {
    size_type newSize = size_ + 1;
    size_type index = pos - pointer_;
    if (newSize > capacity_) {
      reserve(newSize);
      pos = pointer_ + index;
    }
    for (size_type i = size_; i > index; i--) {
      pointer_[i] = pointer_[i - 1];
    }
    pointer_[index] = value;
    ++size_;
    return pos;
  }

  void erase(iterator pos) {
    size_type index = pos - pointer_;
    for (size_type i = index; i < size_ - 1; i++) {
      pointer_[i] = pointer_[i + 1];
    }
    --size_;
  }

  void push_back(const_reference value) {
    if (size_ == 0) {
      reserve(3);
    } else if (size_ == capacity_) {
      reserve(2 * capacity_);
    }
    pointer_[size_] = value;
    ++size_;
  }

  void pop_back() { erase(iterator(size_ - 1)); }

  void swap(vector& other) {
    T* tempPointer = pointer_;
    pointer_ = other.pointer_;
    other.pointer_ = tempPointer;

    size_type tempSize = size_;
    size_ = other.size_;
    other.size_ = tempSize;

    size_type tempCapacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tempCapacity;
  }

  iterator begin() noexcept { return pointer_; }

  iterator end() noexcept { return pointer_ + size_; }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    s21::vector aboba({args...});
    iterator temp = (iterator)pos;
    for (int i = aboba.size() - 1; i >= 0; i--) {
      temp = insert(temp, aboba[i]);
    }
    return temp;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    s21::vector aboba({args...});
    for (size_t i = 0; i < aboba.size(); i++) {
      push_back(aboba[i]);
    }
  }

 private:
  size_type size_, capacity_;
  iterator pointer_;

  void CopyData(iterator newPointer, size_type newSize) {
    iterator tempPointer = pointer_;

    pointer_ = newPointer;
    size_ = newSize;
    capacity_ = newSize;

    for (size_type i = 0; i < size_; ++i) {
      pointer_[i] = tempPointer[i];
    }
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_VECTOR_H_