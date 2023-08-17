#include "../s21_list.h"

#include <gtest/gtest.h>

#include <list>
template class s21::list<int>;

using s21_list = s21::list<int>;
using std_list = std::list<int>;

bool IsSame(s21_list& a, s21_list& b) {
  if (a.size() != b.size()) {
    return false;
  }
  auto it2 = b.begin();
  for (auto& value : a) {
    if (value != *it2) {
      return false;
    }
    ++it2;
  }
  return true;
}

bool IsSame(s21_list& a, std_list& b) {
  if (a.size() != b.size()) {
    return false;
  }
  auto it2 = a.begin();
  for (auto& value : b) {
    if (value != *it2) {
      return false;
    }
    ++it2;
  }
  return true;
}

TEST(constructors, copy_const) {
  s21_list m({2, 5, 6, 7, 1, 6, 34, 13, 6, 2, 46});
  s21_list a(m);

  EXPECT_TRUE(IsSame(m, a));
}

TEST(constructors, move_const) {
  s21_list m({2, 5, 6, 7, 1, 6, 34, 13, 6, 2, 46});
  s21_list a(std::move(m));
  s21_list c({2, 5, 6, 7, 1, 6, 34, 13, 6, 2, 46});
  EXPECT_TRUE(IsSame(a, c));
  EXPECT_TRUE(m.empty());
}

TEST(list_iterator, iterator_begin) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  EXPECT_EQ(*m.begin(), *n.begin());
}

TEST(list_inserting, push_front) {
  s21_list m(3);
  std_list n(3);
  m.push_front(4);
  n.push_front(4);
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_inserting, push_back) {
  s21_list m(3);
  std_list n(3);
  m.push_back(4);
  n.push_back(4);
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, pop_front) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  m.pop_front();
  n.pop_front();
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, pop_back) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  m.pop_back();
  n.pop_back();
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, insert) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  auto it_m = m.begin();
  auto it_n = n.begin();
  ++it_m;
  ++it_n;
  m.insert(it_m, 8);
  n.insert(it_n, 8);
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, erase) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  auto it_m = m.begin();
  auto it_n = n.begin();
  ++it_m;
  ++it_n;
  m.erase(it_m);
  n.erase(it_n);
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, erase_first) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  auto it_m = m.begin();
  auto it_n = n.begin();
  m.erase(it_m);
  n.erase(it_n);
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, erase_last) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  auto it_m = m.end();
  auto it_n = n.end();
  --it_m;
  --it_n;
  m.erase(it_m);
  n.erase(it_n);
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, clear) {
  s21_list m({2, 5, 6, 1, 6});
  m.clear();
  EXPECT_TRUE(m.empty());
}

TEST(list_modifying, swap) {
  s21_list m({2, 5, 6, 1, 6});
  s21_list a({8, 3, 7});
  std_list n({2, 5, 6, 1, 6});
  std_list b({8, 3, 7});
  m.swap(a);
  n.swap(b);
  EXPECT_TRUE(IsSame(m, n));
  EXPECT_TRUE(IsSame(a, b));
}

TEST(list_modifying, merge) {
  s21_list m({2, 5, 6});
  s21_list a({1, 6, 7});
  std_list n({2, 5, 6});
  std_list b({1, 6, 7});
  m.merge(a);
  n.merge(b);
  EXPECT_TRUE(IsSame(m, n));
  EXPECT_TRUE(a.empty());
  EXPECT_TRUE(b.empty());
}

TEST(list_modifying, splice) {
  s21_list m({2, 5, 6, 1, 6});
  s21_list a({8, 3, 7});
  std_list n({2, 5, 6, 1, 6});
  std_list c({8, 3, 7});
  auto it_m = m.begin();
  auto it_n = n.begin();
  ++it_m;
  ++it_n;
  m.splice(it_m, a);
  n.splice(it_n, c);
  EXPECT_TRUE(IsSame(m, n));
  EXPECT_TRUE(IsSame(a, c));
}

TEST(list_modifying, reverse) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  m.reverse();
  n.reverse();
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, unique) {
  s21_list m({2, 2, 5, 5, 5, 6, 6});
  std_list n({2, 2, 5, 5, 5, 6, 6});
  m.unique();
  n.unique();
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_modifying, sort) {
  s21_list m({2, 5, 1, 6, 3});
  std_list n({2, 5, 1, 6, 3});
  m.sort();
  n.sort();
  EXPECT_TRUE(IsSame(m, n));
}

TEST(list_access, front) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  EXPECT_EQ(m.front(), n.front());
}

TEST(list_access, back) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  EXPECT_EQ(m.back(), n.back());
}

TEST(list_capacity, max_size) {
  s21_list m;
  std_list n;
  EXPECT_EQ(m.max_size(), n.max_size());
}

TEST(list_capacity, size) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  EXPECT_EQ(m.size(), n.size());
}

TEST(list_modifying, insert_const) {
  s21_list m({2, 5, 6, 1, 6});
  std_list n({2, 5, 6, 1, 6});
  s21_list::const_iterator it_m = m.begin();
  std_list::const_iterator it_n = n.begin();
  ++it_m;
  ++it_n;
  m.insert(it_m, 8);
  n.insert(it_n, 8);
  EXPECT_TRUE(IsSame(m, n));
}