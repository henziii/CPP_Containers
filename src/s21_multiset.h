#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_MULTISET_H_

#include "avl_tree.h"

namespace s21 {

template <typename Key>
class multiset : public AVLTree<Key> {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using Node = AVLTreeNode<value_type>;
  using Avl = AVLTree<value_type>;
  using iterator = typename Avl::base_iterator;
  using const_iterator = typename Avl::base_const_iterator;

  multiset() : Avl() {}

  multiset(std::initializer_list<value_type> const& items)
      : Avl(items, kMultiset) {}

  multiset(const multiset& other) : Avl(other) {}

  multiset(multiset&& other) : Avl(std::move(other)) {}

  iterator insert(const_reference value) {
    iterator place_of_insertion{};
    bool result_of_insertion{};
    Avl::insert(value, kMultiset, &result_of_insertion, &place_of_insertion);
    return place_of_insertion;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vec;
    (vec.push_back(std::make_pair<iterator, bool>(
         this->insert(std::forward<Args>(args)), true)),
     ...);
    return vec;
  }

  void merge(multiset& other) { Avl::merge(other, kMultiset); }

  size_type count(const_reference key) {
    size_type count{0};
    for (iterator iter = this->begin(); iter != this->end(); iter++) {
      if (*iter == key) count++;
    }
    return count;
  }

  std::pair<iterator, iterator> equal_range(const_reference key) {
    std::pair<iterator, iterator> range{};
    range.first = lower_bound(key);
    range.second = upper_bound(key);
    return range;
  }

  iterator lower_bound(const_reference key) {
    for (auto it = this->begin(); it != this->end(); it++) {
      if (*it >= key) {
        return it;
      }
    }
    return iterator(this->end_, this);
  }

  iterator upper_bound(const_reference key) {
    for (auto it = this->begin(); it != this->end(); it++) {
      if (*it > key) {
        return it;
      }
    }
    return iterator(this->end_, this);
  }

  void print() const noexcept override {
    if (!this->empty()) {
      for (const_iterator it = this->begin(); it != this->end(); ++it) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;
    }
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_MULTISET_H_