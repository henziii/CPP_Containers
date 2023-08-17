#include "../s21_vector.h"
#include "gtest/gtest.h"

TEST(InsertManyBackTest, BasicTest) {
  s21::vector<int> numbers = {1, 2, 3};
  numbers.insert_many_back(4, 5, 6);

  ASSERT_EQ(numbers.size(), 6);
  EXPECT_EQ(numbers[0], 1);
  EXPECT_EQ(numbers[1], 2);
  EXPECT_EQ(numbers[2], 3);
  EXPECT_EQ(numbers[3], 4);
  EXPECT_EQ(numbers[4], 5);
  EXPECT_EQ(numbers[5], 6);
}

TEST(InsertManyTest, InsertMultipleElements) {
  s21::vector<int> myList = {1, 2, 3, 4, 5};
  auto pos = myList.begin();

  myList.insert_many(pos, 10, 20, 1, 2, 3, 4, -1);

  s21::vector<int> expectedList = {10, 20, 1, 2, 3, 4, -1, 1, 2, 3, 4, 5};
  ASSERT_TRUE(myList == expectedList);
}

TEST(vectorTest, AtTest) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(2), 3);
  EXPECT_EQ(vec.at(4), 5);

  EXPECT_THROW(vec.at(6), std::length_error);
}

TEST(vectorTest, IndexOperatorTest) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[4], 5);
}

TEST(vectorTest, FrontTest) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(vec.front(), 1);
}

TEST(vectorTest, BackTest) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(vec.back(), 5);
}

TEST(vectorTest, DataTest) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  int* data = vec.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[2], 3);
  EXPECT_EQ(data[4], 5);
}

TEST(vectorTest, EmptyTest) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());

  vec.push_back(1);
  EXPECT_FALSE(vec.empty());
}

TEST(vectorTest, ReserveTest) {
  s21::vector<int> vec;
  vec.reserve(10);
  EXPECT_EQ(vec.capacity(), 10);

  vec.reserve(5);
  EXPECT_EQ(vec.capacity(), 5);

  vec.reserve(15);
  EXPECT_EQ(vec.capacity(), 15);
}

TEST(vectorTest, EraseTest) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  vec.erase(vec.begin() + 1);

  EXPECT_EQ(vec.size(), 2);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
}

TEST(vectorTest, SizeTest) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  EXPECT_EQ(vec.size(), 3);

  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);

  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

TEST(vectorTest, MaxSizeTest) {
  s21::vector<int> v;

  EXPECT_GE(v.max_size(), 0);

  EXPECT_EQ(v.max_size(),
            std::numeric_limits<s21::vector<int>::size_type>::max());

  s21::vector<double> v2;
  EXPECT_EQ(v2.max_size(),
            std::numeric_limits<s21::vector<double>::size_type>::max());
}

TEST(vectorTest, CapacityTest) {
  s21::vector<int> v;

  EXPECT_EQ(v.capacity(), 3);

  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);

  v.reserve(5);
  EXPECT_EQ(v.capacity(), 5);

  v.clear();
  EXPECT_EQ(v.capacity(), 0);
}

TEST(vectorTest, ShrinkToFitTest) {
  s21::vector<int> v;

  v.reserve(10);

  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }

  EXPECT_EQ(v.size(), 10);

  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), v.size());
}

TEST(vectorTest, ClearTest) {
  s21::vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  ASSERT_EQ(vec.size(), 3);

  vec.clear();

  ASSERT_EQ(vec.size(), 0);

  ASSERT_EQ(vec.capacity(), 0);

  ASSERT_TRUE(vec.empty());
}

TEST(vectorTest, InsertTest) {
  s21::vector<int> vec;
  s21::vector<int> vec2({10, 20, 30, 1, 2, 4, 3});
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  auto it = vec.insert(vec.begin() + 2, 4);

  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec[2], 4);

  ASSERT_EQ(*it, 4);

  ASSERT_EQ(*(it + 1), 3);
  vec.insert(vec.begin(), 30);
  vec.insert(vec.begin(), 20);
  vec.insert(vec.begin(), 10);

  ASSERT_TRUE(vec == vec2);
}

TEST(vectorTest, PushBackTest) {
  s21::vector<int> vec;

  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 3);

  vec.push_back(5);

  ASSERT_FALSE(vec.empty());
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 3);
  ASSERT_EQ(vec[0], 5);

  vec.push_back(10);
  vec.push_back(15);

  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec.capacity(), 3);
  ASSERT_EQ(vec[0], 5);
  ASSERT_EQ(vec[1], 10);
  ASSERT_EQ(vec[2], 15);

  vec.push_back(20);

  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.capacity(), 6);
  ASSERT_EQ(vec[0], 5);
  ASSERT_EQ(vec[1], 10);
  ASSERT_EQ(vec[2], 15);
  ASSERT_EQ(vec[3], 20);
}

TEST(vectorTest, PopBackTest) {
  s21::vector<int> vec;

  vec.push_back(5);
  vec.push_back(10);
  vec.push_back(15);

  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec.capacity(), 3);

  vec.pop_back();

  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 3);
  ASSERT_EQ(vec[0], 5);
  ASSERT_EQ(vec[1], 10);

  vec.pop_back();

  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 3);
  ASSERT_EQ(vec[0], 5);

  vec.pop_back();

  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 3);
  ASSERT_TRUE(vec.empty());
}

TEST(vectorTest, SwapTest) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = {4, 5, 6};

  ASSERT_EQ(vec1.size(), 3);
  ASSERT_EQ(vec1[0], 1);
  ASSERT_EQ(vec1[1], 2);
  ASSERT_EQ(vec1[2], 3);
  ASSERT_EQ(vec2.size(), 3);
  ASSERT_EQ(vec2[0], 4);
  ASSERT_EQ(vec2[1], 5);
  ASSERT_EQ(vec2[2], 6);

  vec1.swap(vec2);

  ASSERT_EQ(vec1.size(), 3);
  ASSERT_EQ(vec1[0], 4);
  ASSERT_EQ(vec1[1], 5);
  ASSERT_EQ(vec1[2], 6);
  ASSERT_EQ(vec2.size(), 3);
  ASSERT_EQ(vec2[0], 1);
  ASSERT_EQ(vec2[1], 2);
  ASSERT_EQ(vec2[2], 3);
}

TEST(vectorTest, BeginTest) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  auto it = vec.begin();
  EXPECT_EQ(*it, 1);
}

TEST(vectorTest, EndTest) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  auto it = vec.end();
  EXPECT_EQ(it, vec.begin() + 3);
}