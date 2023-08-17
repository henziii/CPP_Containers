#include <gtest/gtest.h>

#include <set>

#include "../s21_set.h"

#define kTrue 1
#define kFalse 0

const std::initializer_list<int> kInit_1{-10, 12, -7, 1, 7, 21, 9, -100};
const std::initializer_list<int> kInit_2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const std::initializer_list<int> kInit_3{100, -100, 100, 3, -4, 7, 100};

using my_set = s21::set<int>;
using original_set = std::set<int>;
using m_iterator = s21::set<int>::const_iterator;
using o_iterator = std::set<int>::const_iterator;

int Comparsion(my_set m, original_set o) {
  m_iterator m_it = m.cbegin();
  o_iterator o_it = o.cbegin();
  while (m_it != m.cend()) {
    if (*m_it++ != *o_it++) return kFalse;
  }
  return kTrue;
}

TEST(default_constructor, test_set) {
  my_set m;
  original_set o;
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(init_list_constructor, test_set) {
  my_set m(kInit_1);
  original_set o(kInit_1);
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(copy_constructor, test_set) {
  my_set m(kInit_3);
  original_set o(kInit_3);

  my_set m_res(m);
  original_set o_res(o);
  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
}

TEST(rem_constructor, test_set) {
  my_set m(kInit_2);
  original_set o(kInit_2);

  my_set m_res(std::move(m));
  original_set o_res(std::move(o));

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
  ASSERT_EQ(m.size(), o.size());
}

TEST(operators_1, test_set) {
  my_set m(kInit_1);
  original_set o(kInit_1);

  my_set m_res = m;
  original_set o_res = o;

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
}

TEST(operators_2, test_set) {
  my_set m(kInit_1);
  original_set o(kInit_1);

  my_set m_res = std::move(m);
  original_set o_res = std::move(o);

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
  ASSERT_EQ(m.size(), o.size());
}

TEST(iter_begin_end, test_set) {
  my_set m(kInit_2);
  original_set o(kInit_2);

  ASSERT_EQ(*m.begin(), *o.begin());
  ASSERT_EQ(*(--m.end()), *(--o.end()));
}

TEST(empty, test_set) {
  my_set m;
  original_set o;

  ASSERT_EQ(m.empty(), o.empty());
  m.insert(5);
  o.insert(5);
  ASSERT_EQ(m.empty(), o.empty());
}

TEST(size, test_set) {
  my_set m(kInit_3);
  original_set o(kInit_3);

  ASSERT_EQ(m.size(), o.size());
}

TEST(max_size, test_set) {
  my_set m(kInit_3);
  original_set o(kInit_3);

  ASSERT_EQ(m.max_size(), o.max_size());
}

TEST(clear, test_set) {
  my_set m(kInit_3);
  original_set o(kInit_3);

  m.clear();
  o.clear();
  ASSERT_EQ(m.size(), o.size());
}

TEST(insert, test1_set) {
  my_set m;
  original_set o;

  m.insert(1);
  m.insert(2);
  m.insert(3);

  o.insert(1);
  o.insert(2);
  o.insert(3);

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert, test2_set) {
  my_set m({20, 34, -150, 11, 54, 1, 0, 0, 177, -1025, 51, 15, 76});
  original_set o({20, 34, -150, 11, 54, 1, 0, 0, 177, -1025, 51, 15, 76});

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert, test3_set) {
  my_set m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  original_set o(
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  m.insert(-24);
  o.insert(-24);

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert_many_set, test) {
  my_set m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  original_set ans({1,  2,  3,  4,  5, 6,   7,  8,   9,  10, 11, 12, 13,
                    14, 15, -5, -1, 0, 100, 50, 250, 17, 16, 24, 100});
  m.insert_many(100, 50, 250, 17, 16, 24, 100);

  ASSERT_EQ(Comparsion(m, ans), kTrue);
}

TEST(erase, test_1_set) {
  my_set m(kInit_2);
  original_set o(kInit_2);

  m.erase(m.begin());
  m.erase(m.begin());
  m.erase(m.begin());

  o.erase(o.begin());
  o.erase(o.begin());
  o.erase(o.begin());

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(erase, test_2_set) {
  my_set m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  original_set o(
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -1, 0});
  m.insert(-24);
  o.insert(-24);

  for (int i = 14; i >= -1; i--) {
    m.erase(i);
    o.erase(i);
  }
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(erase, test_3_set) {
  my_set m({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  original_set o({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  m.insert(-24);
  o.insert(-24);

  for (int i = 15; i >= -25; i--) {
    m.erase(i);
    o.erase(i);
  }
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(swap, test_set) {
  my_set m1(kInit_1);
  my_set m2(kInit_2);
  original_set o1(kInit_1);
  original_set o2(kInit_2);

  m1.swap(m2);
  o1.swap(o2);

  ASSERT_EQ(Comparsion(m1, o1), kTrue);
  ASSERT_EQ(Comparsion(m2, o2), kTrue);
}

TEST(merge, test_set) {
  my_set m1(kInit_1);
  my_set m2(kInit_2);
  m1.print();

  original_set o1(kInit_1);
  original_set o2(kInit_2);
  std::set<int> a;
  m1.merge(m2);
  o1.merge(o2);

  ASSERT_EQ(Comparsion(m1, o1), kTrue);
}

TEST(find, test_set) {
  my_set m(kInit_2);
  original_set o(kInit_2);

  ASSERT_EQ(*(++m.find(7)), *(++o.find(7)));
}

TEST(contains, test_set) {
  my_set m(kInit_1);
  original_set o(kInit_1);

  ASSERT_EQ(m.contains(-7), true);
  ASSERT_EQ(m.contains(1001), false);
}
