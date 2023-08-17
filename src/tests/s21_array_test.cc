#include "../s21_array.h"

#include <gtest/gtest.h>

#include <array>

using s21_array = s21::array<int, 7>;
using std_array = std::array<int, 7>;

bool IsSame(s21_array& a, std_array& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < b.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

TEST(constructors, move) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  s21_array b = {std::move(a)};
  std_array c = {1, 2, 3, 4, 5, 6, 7};
  std_array d = {std::move(c)};

  EXPECT_TRUE(IsSame(b, d));
}

TEST(constructors, init) {
  EXPECT_THROW((s21_array({1, 2, 3, 4, 5, 6, 7, 8})), std::out_of_range);
}

TEST(array_access, at) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(a.at(2), b.at(2));
  EXPECT_EQ(a.at(5), b.at(5));
  EXPECT_THROW(a.at(10), std::out_of_range);
}

TEST(array_access, subscript_operator) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(a[3], b[3]);
  EXPECT_EQ(a[0], b[0]);
}

TEST(array_access, front_back) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
}

TEST(array_access, begin_end) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(*a.begin(), *b.begin());
}

TEST(array_capacity, size) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(a.size(), b.size());
}

TEST(array_capacity, max_size) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(array_modifying, fill) {
  s21_array a;
  std_array b;
  a.fill(5);
  b.fill(5);
  EXPECT_TRUE(IsSame(a, b));
}

TEST(array_modifying, swap) {
  s21_array a = {1, 2, 3, 4, 5, 6, 7};
  s21_array c = {8, 9, 10, 11, 12, 13, 14};
  std_array b = {1, 2, 3, 4, 5, 6, 7};
  std_array d = {8, 9, 10, 11, 12, 13, 14};
  s21::array<int, 8> e;
  a.swap(c);
  EXPECT_TRUE(IsSame(a, d));
  EXPECT_TRUE(IsSame(c, b));
}

TEST(array_capacity, empty) {
  s21::array<int, 0> a;
  s21::array<int, 0> b;
  s21_array c;
  EXPECT_FALSE(c.empty());
  EXPECT_TRUE(a.empty());
  EXPECT_THROW(a.at(2), std::out_of_range);
  EXPECT_THROW(a[2], std::out_of_range);
  EXPECT_THROW(a.front(), std::out_of_range);
  EXPECT_THROW(a.back(), std::out_of_range);
  EXPECT_EQ(a.data(), nullptr);
  EXPECT_EQ(a.begin(), nullptr);
  EXPECT_EQ(a.end(), nullptr);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.max_size(), 0);
  EXPECT_THROW(a.swap(b), std::out_of_range);
  EXPECT_THROW(a.fill(2), std::out_of_range);
}
