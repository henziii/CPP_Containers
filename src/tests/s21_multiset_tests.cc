#include <gtest/gtest.h>

#include <set>

#include "../s21_multiset.h"

#define kTrue 1
#define kFalse 0

const std::initializer_list<int> kInit_1_m{-10,  12,  -7,  1, 7, 21, 9,
                                           -100, -10, -10, 7, 7, 13};
const std::initializer_list<int> kInit_2_m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                           1, 2, 3, 4, 5, 6, 7, 8, 9};
const std::initializer_list<int> kInit_3_m{100, -100, 100, 3, -4, 7, 100};

using my_multiset = s21::multiset<int>;
using original_multiset = std::multiset<int>;
using m_iterator_m = s21::multiset<int>::const_iterator;
using o_iterator_o = std::multiset<int>::const_iterator;

int Comparsion(my_multiset m, original_multiset o) {
  m_iterator_m m_it = m.cbegin();
  o_iterator_o o_it = o.cbegin();
  while (m_it != m.cend()) {
    if (*m_it++ != *o_it++) return kFalse;
  }
  return kTrue;
}

TEST(default_constructor_multiset, test) {
  my_multiset m;
  original_multiset o;
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(init_list_constructor_multiset, test) {
  my_multiset m(kInit_1_m);
  original_multiset o(kInit_1_m);
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(copy_constructor_multiset, test) {
  my_multiset m(kInit_3_m);
  original_multiset o(kInit_3_m);

  my_multiset m_res(m);
  original_multiset o_res(o);
  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
}

TEST(rem_constructor_multiset, test) {
  my_multiset m(kInit_2_m);
  original_multiset o(kInit_2_m);

  my_multiset m_res(std::move(m));
  original_multiset o_res(std::move(o));

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
  ASSERT_EQ(m.size(), o.size());
}

TEST(operators_1_multiset, test) {
  my_multiset m(kInit_1_m);
  original_multiset o(kInit_1_m);

  my_multiset m_res = m;
  original_multiset o_res = o;

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
}

TEST(operators_2_multiset, test) {
  my_multiset m(kInit_1_m);
  original_multiset o(kInit_1_m);
  m.print();

  my_multiset m_res = std::move(m);
  original_multiset o_res = std::move(o);

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
  ASSERT_EQ(m.size(), o.size());
}

TEST(iter_begin_end_multiset, test) {
  my_multiset m(kInit_2_m);
  original_multiset o(kInit_2_m);

  ASSERT_EQ(*m.begin(), *o.begin());
  ASSERT_EQ(*(--m.end()), *(--o.end()));
}

TEST(empty_multiset, test) {
  my_multiset m;
  original_multiset o;

  ASSERT_EQ(m.empty(), o.empty());
  m.insert(5);
  o.insert(5);
  ASSERT_EQ(m.empty(), o.empty());
}

TEST(size_multiset, test) {
  my_multiset m(kInit_3_m);
  original_multiset o(kInit_3_m);

  ASSERT_EQ(m.size(), o.size());
}

TEST(max_size_multiset, test) {
  my_multiset m(kInit_3_m);
  original_multiset o(kInit_3_m);

  ASSERT_EQ(m.max_size(), o.max_size());
}

TEST(clear_multiset, test) {
  my_multiset m(kInit_3_m);
  original_multiset o(kInit_3_m);

  m.clear();
  o.clear();
  ASSERT_EQ(m.size(), o.size());
}

TEST(insert_multiset, test_1) {
  my_multiset m;
  original_multiset o;

  m.insert(1);
  m.insert(2);
  m.insert(3);

  o.insert(1);
  o.insert(2);
  o.insert(3);

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert, test2) {
  my_multiset m({20, 34, -150, 11, 54, 1, 0, 0, 177, -1025, 51, 15, 76});
  original_multiset o({20, 34, -150, 11, 54, 1, 0, 0, 177, -1025, 51, 15, 76});

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert_multiset, test3) {
  my_multiset m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  original_multiset o(
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  m.insert(-24);
  o.insert(-24);

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert_many_multiset, test) {
  my_multiset m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  original_multiset ans({1,  2,  3,  4,  5,  6, 7,   8,  9,   10, 11, 12,
                         13, 14, 15, -5, -1, 0, 100, 50, 250, 17, 16, 24});
  m.insert_many(100, 50, 250, 17, 16, 24);

  ASSERT_EQ(Comparsion(m, ans), kTrue);
}

TEST(erase_multiset, test_1) {
  my_multiset m(kInit_2_m);
  original_multiset o(kInit_2_m);

  m.erase(m.begin());
  m.erase(m.begin());
  m.erase(m.begin());

  o.erase(o.begin());
  o.erase(o.begin());
  o.erase(o.begin());

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(erase, test_2) {
  my_multiset m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  original_multiset o(
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  m.insert(-24);
  o.insert(-24);

  for (int i = 14; i >= -1; i--) {
    m.erase(i);
    o.erase(i);
  }
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(erase_multiset, test_3) {
  my_multiset m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  original_multiset o({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  m.insert(-24);
  o.insert(-24);

  for (int i = 15; i >= -25; i--) {
    m.erase(i);
    o.erase(i);
  }
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(swap_multiset, test) {
  my_multiset m1(kInit_1_m);
  my_multiset m2(kInit_2_m);
  original_multiset o1(kInit_1_m);
  original_multiset o2(kInit_2_m);

  m1.swap(m2);
  o1.swap(o2);

  ASSERT_EQ(Comparsion(m1, o1), kTrue);
  ASSERT_EQ(Comparsion(m2, o2), kTrue);
}

TEST(merge_multiset, test) {
  my_multiset m1(kInit_1_m);
  my_multiset m2(kInit_2_m);
  original_multiset o1(kInit_1_m);
  original_multiset o2(kInit_2_m);
  std::set<int> a;
  m1.merge(m2);
  o1.merge(o2);

  ASSERT_EQ(Comparsion(m1, o1), kTrue);
}

TEST(count_multiset, test) {
  my_multiset m(
      {1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4});
  original_multiset o(
      {1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4});

  ASSERT_EQ(m.count(1), o.count(1));
}

TEST(find_multiset, test) {
  my_multiset m(kInit_2_m);
  original_multiset o(kInit_2_m);

  ASSERT_EQ(*(++m.find(7)), *(++o.find(7)));
}

TEST(contains_multiset, test) {
  my_multiset m(kInit_1_m);
  original_multiset o(kInit_1_m);

  ASSERT_EQ(m.contains(-7), true);
  ASSERT_EQ(m.contains(1001), false);
}

TEST(equal_range_multiset, test) {
  my_multiset m({1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 51});
  original_multiset o({1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 51});

  std::pair<m_iterator_m, m_iterator_m> mp = m.equal_range(6);
  auto op = o.equal_range(6);

  ASSERT_EQ(*mp.first, *op.first);
  ASSERT_EQ(*mp.second, *op.second);
  ASSERT_EQ(*mp.first--, *op.first--);
  ASSERT_EQ(*mp.second--, *op.second--);
  ASSERT_EQ(*(--mp.first), *(--op.first));
  ASSERT_EQ(*(--mp.second), *(--op.second));
  ASSERT_EQ(*(--mp.first), *(--op.first));
  ASSERT_EQ(*(--mp.second), *(--op.second));
  ASSERT_EQ(*(--mp.first), *(--op.first));
  ASSERT_EQ(*(--mp.second), *(--op.second));
}
