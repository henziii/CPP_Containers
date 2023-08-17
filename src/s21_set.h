#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_

#include "avl_tree.h"

namespace s21 {

template <typename Key>
class set : public AVLTree<Key> {
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

  set() : Avl() {}

  set(std::initializer_list<value_type> const& items) : Avl(items, kSet) {}

  set(const set& other) : Avl(other) {}

  set(set&& other) : Avl(std::move(other)) {}

  std::pair<iterator, bool> insert(const_reference value) {
    std::pair<iterator, bool> result{};
    iterator place_of_insertion{};
    bool result_of_insertion{};
    Avl::insert(value, kSet, &result_of_insertion, &place_of_insertion);
    result.first = place_of_insertion;
    result.second = result_of_insertion;
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vec;
    (vec.push_back(this->insert(std::forward<Args>(args))), ...);
    return vec;
  }

  void merge(set& other) { Avl::merge(other, kSet); }

  void print() const noexcept override {
    if (!this->empty()) {
      for (iterator it = this->begin(); it != this->end(); ++it) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;
    }
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_