#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_NODE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_NODE_H_

namespace s21 {
template <typename T>
class ListNode {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using Node = ListNode<value_type>;

  ListNode() : ListNode(value_type{}, this, this) {}

  ListNode(const_reference value, Node *prev, Node *next)
      : value_{value}, prev_{prev}, next_{next} {
    if (next_ != this && next_ != nullptr) {
      next_->prev_ = this;
    }
    if (prev_ != this && prev_ != nullptr) {
      prev_->next_ = this;
    }
  }

  ListNode(Node *prev, Node *next) : ListNode(value_type(), prev, next) {}

  ListNode(const Node &other) = default;

  ListNode(Node &&other) = default;

  Node &operator=(const Node &other) = default;

  Node &operator=(Node &&other) = default;

  ~ListNode() {}
  bool operator==(const Node &other) { return this->value_ == other.value_; }

  void set_prev(Node *new_prev) {
    prev_ = new_prev;
    prev_->next_ = this;
  }

  void set_next(Node *new_next) {
    next_ = new_next;
    next_->prev_ = this;
  }

  void set_value(value_type new_value) { value_ = new_value; }

  void EliminateNode() {
    if (next_ != this && next_ != nullptr) {
      next_->prev_ = prev_;
    }
    if (prev_ != this && prev_ != nullptr) {
      prev_->next_ = next_;
    }
  }

  void LoopingNode() {
    prev_ = this;
    next_ = this;
  }

  void Reverce() {
    Node *temp = prev_;
    prev_ = next_;
    next_ = temp;
  }

  reference get_value_ref() { return value_; }
  const_reference get_value() { return value_; }
  Node *get_next() { return next_; }
  Node *get_prev() { return prev_; }

 private:
  value_type value_;
  Node *prev_;
  Node *next_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_NODE_H_