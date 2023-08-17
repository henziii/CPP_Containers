#include "../s21_queue.h"
#include "gtest/gtest.h"

TEST(queueTest, FrontTest) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  const auto& frontElement = queue.front();

  EXPECT_EQ(frontElement, 1);
}

TEST(queueTest, BackTest) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  const auto& backElement = queue.back();

  EXPECT_EQ(backElement, 3);
}

TEST(queueTest, EmptyTest) {
  s21::queue<int> queue;

  EXPECT_TRUE(queue.empty());

  queue.push(1);
  queue.push(2);

  EXPECT_FALSE(queue.empty());

  queue.pop();
  queue.pop();

  EXPECT_TRUE(queue.empty());
}

TEST(queueTest, SizeTest) {
  s21::queue<int> queue;

  EXPECT_EQ(queue.size(), 0);

  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_EQ(queue.size(), 3);

  queue.pop();

  EXPECT_EQ(queue.size(), 2);
}

TEST(queueTest, PushTest) {
  s21::queue<int> queue;

  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_EQ(queue.front(), 1);

  EXPECT_EQ(queue.size(), 3);
}

TEST(queueTest, PopAndSwapTest) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;

  queue1.push(1);
  queue1.push(2);
  queue1.push(3);

  EXPECT_EQ(queue1.size(), 3);

  queue1.pop();

  EXPECT_EQ(queue1.size(), 2);

  queue1.swap(queue2);

  EXPECT_TRUE(queue1.empty());

  EXPECT_EQ(queue2.size(), 2);
}