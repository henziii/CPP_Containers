#include <gtest/gtest.h>

#include <map>

#include "../s21_map.h"

#define kTrue 1
#define kFalse 0

const std::initializer_list<std::pair<int, int>> kInit_1{
    {1, 100},          {-500, 100500}, {-10, 0}, {21, 100}, {19, 16},
    {100000, 1000000}, {50, -21},      {1, 1},   {-10, 777}};

using my_map = s21::map<int, int>;
using original_map = std::map<int, int>;
using m_iterator = my_map::const_iterator;
using o_iterator = original_map::const_iterator;

int Comparsion(my_map m, original_map o) {
  m_iterator m_it = m.cbegin();
  o_iterator o_it = o.cbegin();
  while (m_it != m.end()) {
    if (((*m_it).first != (*o_it).first) &&
        ((*m_it).second != (*o_it).second)) {
      return kFalse;
    }
    m_it++;
    o_it++;
  }
  return kTrue;
}

TEST(default_constructor, test_map) {
  my_map m;
  original_map o;

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(init_list_constructor, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(copy_constructor, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  my_map m_res(m);
  original_map o_res(o);

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
}

TEST(rem_constructor, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  my_map m_res(std::move(m));
  original_map o_res(std::move(o));

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
  ASSERT_EQ(m.size(), o.size());
}

TEST(operators_1, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  my_map m_res = m;
  original_map o_res = o;

  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
}

TEST(operators_2, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});
  m.print();
  my_map m_res = std::move(m);
  original_map o_res = std::move(o);
  ASSERT_EQ(Comparsion(m_res, o_res), kTrue);
  ASSERT_EQ(m.size(), o.size());
}

TEST(iter_begin_end, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  m_iterator m_it = m.begin();
  o_iterator o_it = o.begin();
  ASSERT_EQ((*m_it).first, (*o_it).first);
  ASSERT_EQ((*m_it).second, (*o_it).second);
  m_it++;
  o_it++;
  ASSERT_EQ((*m_it).first, (*o_it).first);
  ASSERT_EQ((*m_it).second, (*o_it).second);
}

TEST(empty, test_map) {
  my_map m;
  original_map o;

  ASSERT_EQ(m.empty(), o.empty());
  m.insert(5, 4);
  o.insert({5, 4});
  ASSERT_EQ(m.empty(), o.empty());
}

TEST(size, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  ASSERT_EQ(m.size(), o.size());
}

TEST(max_size, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  ASSERT_EQ(m.max_size(), o.max_size());
}

TEST(clear, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  ASSERT_EQ(m.size(), o.size());
  m.clear();
  o.clear();
  ASSERT_EQ(m.size(), o.size());
}

TEST(insert, test_map) {
  my_map m;
  original_map o;

  m.insert(1, 10);
  m.insert(1, 20);
  m.insert(0, 500);
  m.insert(-100, -100);

  o.insert({1, 10});
  o.insert({1, 20});
  o.insert({0, 500});
  o.insert({-100, -100});

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert, test_map2) {
  my_map m({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});
  original_map o({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});

  m.insert(-24, 1);
  o.insert({-24, 1});

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert, pair) {
  my_map m({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});
  original_map o({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});

  m.insert(std::make_pair<int, int>(1000, 12345));
  o.insert(std::make_pair<int, int>(1000, 12345));
  m.insert(std::make_pair<int, int>(7, 0));
  o.insert(std::make_pair<int, int>(7, 0));

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(insert_to_assign, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  std::pair<s21::map<int, int>::iterator, bool> mpair;
  std::pair<std::map<int, int>::iterator, bool> opair;

  mpair = m.insert_or_assign(-10, 12345);
  opair = o.insert_or_assign(-10, 12345);

  ASSERT_EQ((*mpair.first).first, (*opair.first).first);
  ASSERT_EQ((*mpair.first).second, (*opair.first).second);
  ASSERT_EQ(mpair.second, opair.second);

  mpair = m.insert_or_assign(2, 12345);
  opair = o.insert_or_assign(2, 12345);

  ASSERT_EQ((*mpair.first).first, (*opair.first).first);
  ASSERT_EQ((*mpair.first).second, (*opair.first).second);
  ASSERT_EQ(mpair.second, opair.second);
}

TEST(insert_many_map, test) {
  my_map m({{1, 100},
            {-500, 100500},
            {-10, 0},
            {21, 100},
            {19, 16},
            {100000, 1000000},
            {50, -21},
            {1, 1},
            {-10, 777}});
  original_map ans({{1, 100},
                    {-500, 100500},
                    {-10, 0},
                    {21, 100},
                    {19, 16},
                    {100000, 1000000},
                    {50, -21},
                    {1, 1},
                    {-10, 777},
                    {1, 100},
                    {-28, 100},
                    {-1, 1},
                    {0, 1512512}});

  m.insert_many(
      std::make_pair<int, int>(1, 100), std::make_pair<int, int>(-28, 100),
      std::make_pair<int, int>(-1, 1), std::make_pair<int, int>(0, 1512512));

  ASSERT_EQ(Comparsion(m, ans), kTrue);
}

TEST(erase, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  m.erase(m.begin());
  m.erase(m.begin());
  m.erase(m.begin());

  o.erase(o.begin());
  o.erase(o.begin());
  o.erase(o.begin());

  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(swap, test_map) {
  my_map m1(kInit_1);
  original_map o1({{1, 100},
                   {-500, 100500},
                   {-10, 0},
                   {21, 100},
                   {19, 16},
                   {100000, 1000000},
                   {50, -21},
                   {1, 1},
                   {-10, 777}});
  my_map m2({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});
  original_map o2({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});

  m1.swap(m2);
  o1.swap(o2);

  ASSERT_EQ(Comparsion(m1, o1), kTrue);
  ASSERT_EQ(Comparsion(m2, o2), kTrue);
}

TEST(merge, test_map) {
  my_map m1(kInit_1);
  original_map o1({{1, 100},
                   {-500, 100500},
                   {-10, 0},
                   {21, 100},
                   {19, 16},
                   {100000, 1000000},
                   {50, -21},
                   {1, 1},
                   {-10, 777}});
  my_map m2({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});
  original_map o2({{3, 10}, {2, 15}, {0, 1}, {10, 2}, {0, 123}, {1, 55555}});

  m1.merge(m2);
  o1.merge(o2);

  ASSERT_EQ(Comparsion(m1, o1), kTrue);
  ASSERT_EQ(Comparsion(m2, o2), kTrue);
}

TEST(at, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  ASSERT_EQ(m.at(100000), 1000000);
  ASSERT_EQ(o.at(100000), 1000000);
  ASSERT_EQ(m[-10], 0);
  ASSERT_EQ(m[-10], 0);

  m.at(100000) = -123;
  m.at(100000) = -123;
  m.at(1) = -987;
  m.at(1) = -987;
  ASSERT_EQ(Comparsion(m, o), kTrue);

  m[-10] = 666;
  o[-10] = 666;
  ASSERT_EQ(Comparsion(m, o), kTrue);
}

TEST(contains, test_map) {
  my_map m(kInit_1);
  original_map o({{1, 100},
                  {-500, 100500},
                  {-10, 0},
                  {21, 100},
                  {19, 16},
                  {100000, 1000000},
                  {50, -21},
                  {1, 1},
                  {-10, 777}});

  ASSERT_EQ(m.contains(19), true);
  ASSERT_EQ(m.contains(1001), false);
}
