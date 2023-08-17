#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_

#include "avl_tree.h"

namespace s21 {

template <typename Key, typename T>
class MapCompare {
 public:
  int8_t operator()(const std::pair<Key, T>& a,
                    const std::pair<Key, T>& b) const noexcept {
    return a.first < b.first ? 1 : (a.first > b.first ? 2 : 0);
  }
};

template <typename Key, typename T>
class map : public AVLTree<std::pair<Key, T>, MapCompare<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using Node = AVLTreeNode<value_type>;
  using Avl = AVLTree<value_type, MapCompare<Key, T>>;
  using const_iterator = typename Avl::base_const_iterator;

  class iterator : public Avl::base_const_iterator {
   public:
    friend class map<Key, T>;

    iterator() : Avl::base_const_iterator() {}
    iterator(typename Avl::base_const_iterator other) noexcept
        : Avl::base_const_iterator(other) {}
    iterator(Node* node, const Avl* obj) noexcept
        : Avl::base_const_iterator(node, obj) {}

    std::pair<const key_type, mapped_type&> operator*() {
      reference temp = const_cast<reference>(map::iterator::iter_->get_value());
      return std::pair<const key_type, mapped_type&>(temp.first, temp.second);
    };
  };

  map() : Avl() {}

  map(std::initializer_list<value_type> const& items) : Avl(items, kMap) {}

  map(const map& other) : Avl(other) {}

  map(map&& other) : Avl(std::move(other)) {}

  mapped_type& operator[](const Key& key) noexcept { return at(key); }

  iterator begin() const noexcept {
    return static_cast<iterator>(Avl::begin());
  }

  iterator end() const noexcept { return static_cast<iterator>(Avl::end()); }

  mapped_type& at(const Key& key) {
    iterator res;
    std::pair<Key, T> a{key, T()};
    if ((res = (iterator)this->find(a)) == this->end()) {
      throw std::exception();
    }
    return (*res).second;
  }

  size_type max_size() const noexcept override {
    return (std::numeric_limits<size_t>::max()) / sizeof(value_type) / 10;
  }

  std::pair<iterator, bool> insert(const_reference value) {
    std::pair<iterator, bool> result{};
    iterator place_of_insertion{};
    bool result_of_insertion{};
    Avl::insert(value, kMap, &result_of_insertion, &place_of_insertion);
    result.first = place_of_insertion;
    result.second = result_of_insertion;
    return result;
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return insert(std::make_pair<const Key&, const T&>(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    std::pair<iterator, bool> result = insert(key, obj);
    if (result.second == false) {
      (*result.first).second = obj;
    }
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vec;
    (vec.push_back(this->insert(std::forward<Args>(args))), ...);
    return vec;
  }

  void merge(map& other) { Avl::merge(other, kMap); }

  bool contains(const Key& key) const noexcept {
    for (iterator it = this->begin(); it != this->end(); it++) {
      if ((*it).first == key) {
        return true;
      }
    }
    return false;
  }

  void print() const noexcept override {
    for (iterator it = this->begin(); it != this->end(); it++) {
      std::cout << (*it).first << "  " << (*it).second << std::endl;
    }
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_