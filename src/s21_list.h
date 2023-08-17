#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_

#include <algorithm>
#include <cstddef>
#include <utility>

#include "s21_list_const_iterator.h"
#include "s21_list_iterator.h"
#include "s21_list_node.h"
namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using Node = ListNode<value_type>;

  list() : list(0) {}  // default constructor, creates empty list 

  list(size_type n) : end_node_{new Node()}, size_{0} {
    begin_node_ = end_node_;
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const &items)
      : list(0) {  // initializer list constructor
    for (auto item : items) {
      push_back(item);
    }
  }

  list(const list &l) : list(0) {  // copy constructor
    *this = l;
  }

  list(list &&l) : list(0) {  // move constructor
    *this = std::move(l);
  }

  list &operator=(const list &other) {
    this->clear();
    for (const_iterator it = other.cbegin(); it != other.cend(); it++) {
      this->push_back(*it);
    }
    return *this;
  }

  list &operator=(list &&other) {
    this->clear();
    delete end_node_;
    this->begin_node_ = std::move(other.begin_node_);
    this->end_node_ = std::move(other.end_node_);
    this->size_ = std::move(other.size_);
    other.end_node_ = new Node();
    other.begin_node_ = other.end_node_;
    other.size_ = 0;
    return *this;
  }

  ~list() {  // destructor
    clear();
    delete end_node_;
  }

  const_reference front() const {
    return begin_node_->get_value();
  }  // access the first element
  const_reference back() const {
    return end_node_->get_prev()->get_value();
  }  // access the last element

  iterator begin() { return iterator(begin_node_); }
  iterator end() { return iterator(end_node_); }

  const_iterator cbegin() const { return const_iterator(begin_node_); }
  const_iterator cend() const { return const_iterator(end_node_); }

  bool empty() const noexcept { return begin_node_ == end_node_; }
  size_type size() const noexcept { return size_; }

  // returns the maximum possible number of elements
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }

  void clear() {
    int size = size_;
    for (int i = 0; i < size; i++) {
      NodeEreser(begin_node_);
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    MakeNewNode(value, pos.ptr_->get_prev(), pos.ptr_);
    return ++pos;
  }

  const_iterator insert(const_iterator pos, const_reference value) {
    MakeNewNode(value, pos.ptr_->get_prev(), pos.ptr_);
    return iterator(++(pos.ptr_));
  }

  void erase(iterator pos) { NodeEreser(pos.ptr_); }

  void push_back(const_reference value) {
    MakeNewNode(value, end_node_->get_prev(), end_node_);
  }

  void pop_back() { NodeEreser(end_node_->get_prev()); }

  void push_front(const_reference value) {
    MakeNewNode(value, end_node_, end_node_->get_next());
  }

  void pop_front() { NodeEreser(begin_node_); }

  void swap(list &other) {
    list temp(std::move(*this));
    *this = std::move(other);
    other = std::move(temp);
  }

  void merge(list &other) {
    list res{};
    iterator it_this = this->begin();
    iterator it_other = other.begin();
    iterator it_less{};

    while (it_this != this->end() && it_other != other.end()) {
      it_less = Less(it_this, it_other);
      if (it_less == it_this) {
        ++it_this;
        res.NodePushBack(it_less, *this);
      } else {
        ++it_other;
        res.NodePushBack(it_less, other);
      }
    }
    if (this->empty() == false) {
      res.splice(res.end(), *this);
    }
    if (other.empty() == false) {
      res.splice(res.end(), other);
    }
    swap(res);
  }

  void reverse() {
    for (iterator it = begin(); it != end(); it--) {
      it.ptr_->Reverce();
    }
    end_node_->Reverce();
    begin_node_ = end_node_->get_next();
  }

  void unique() {
    for (iterator it = begin(), it_next = ++begin(); it_next != end();
         it++, it_next++) {
      if (*it == *it_next) {
        erase(it_next);
        it_next = it;
        it--;
      }
    }
  }

  void splice(const_iterator pos, list &other) {
    if (other.empty() == false) {
      Node *last_node = other.end_node_->get_prev();
      Node *first_node = other.begin_node_;
      this->size_ += other.size_;
      other.Reset();
      first_node->set_prev(pos.ptr_->get_prev());
      last_node->set_next(pos.ptr_);
      if (pos.ptr_ == begin_node_) {
        begin_node_ = first_node;
      }
    }
  }

  void sort() {
    if (size_ != 1) {
      list temp = this->Divide();

      temp.sort();
      this->sort();

      this->merge(temp);
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    list temp({args...});
    splice(pos, temp);
    iterator a(pos.ptr_);
    return a;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    insert_many(begin(), args...);
  }

 private:
  Node *begin_node_;
  Node *end_node_;
  size_type size_;

  list Divide() {
    list second{};
    for (size_type temp = this->size_ / 2; size_ > temp;) {
      iterator it = --(this->end());
      second.NodePushBack(it, *this);
    }
    return second;
  }

  iterator &Less(iterator &first, iterator &second) {
    if (*first <= *second) {
      return first;
    }
    return second;
  }

  void NodePushBack(iterator it, list &other) {
    other.MoveNode(it, end(), *this);
  }

  void MoveNode(iterator from, iterator pos, list &other) {
    if (from != this->end()) {
      Node *node = from.ptr_;
      if (this->begin_node_ == node) {
        begin_node_ = node->get_next();
      }
      node->EliminateNode();
      --size_;
      other.size_++;
      node->set_prev(pos.ptr_->get_prev());
      node->set_next(pos.ptr_);
      if (pos == other.begin()) {
        other.begin_node_ = node;
      }
    }
  }

  void MakeNewNode(const_reference value, Node *prev, Node *next) {
    Node *temp = new Node(value, prev, next);
    size_ += 1;
    if (empty() || next == begin_node_) {
      begin_node_ = temp;
    }
  }

  void Reset() {
    size_ = 0;
    begin_node_ = end_node_;
    end_node_->LoopingNode();
  }

  void NodeEreser(Node *node) {
    --size_;
    if (node == begin_node_) {
      begin_node_ = node->get_next();
    }
    if (node != nullptr && node != end_node_) {
      node->EliminateNode();
      delete node;
    }
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_