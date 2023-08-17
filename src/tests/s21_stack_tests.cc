#include "../s21_stack.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(stackTest, TopEmptyStack) {
  stack<int> stack;
  ASSERT_THROW(stack.top(), std::runtime_error);
}

TEST(stackTest, TopNonEmptyStack) {
  stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);

  ASSERT_EQ(stack.top(), 30);
}

TEST(stackTest, TopConstStack) {
  const stack<int> stack({1, 2, 3, 4, 5});

  ASSERT_EQ(stack.top(), 5);
}

TEST(stackTest, TopConstEmptyStack) {
  const stack<int> stack;

  ASSERT_THROW(stack.top(), std::runtime_error);
}

TEST(stackTest, EmptyOnEmptyStack) {
  stack<int> stack;
  ASSERT_TRUE(stack.empty());
}

TEST(stackTest, EmptyOnNonEmptyStack) {
  stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);

  ASSERT_FALSE(stack.empty());
}

TEST(stackTest, EmptyOnConstStack) {
  const stack<int> stack({1, 2, 3, 4, 5});

  ASSERT_FALSE(stack.empty());
}

TEST(stackTest, EmptyOnConstEmptyStack) {
  const stack<int> stack;

  ASSERT_TRUE(stack.empty());
}

TEST(stackTest, SizeOnEmptyStack) {
  stack<int> stack;
  ASSERT_EQ(stack.size(), 0);
}

TEST(stackTest, SizeOnNonEmptyStack) {
  stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);

  ASSERT_EQ(stack.size(), 3);
}

TEST(stackTest, SizeOnConstStack) {
  const stack<int> stack({1, 2, 3, 4, 5});

  ASSERT_EQ(stack.size(), 5);
}

TEST(stackTest, SizeOnConstEmptyStack) {
  const stack<int> stack;

  ASSERT_EQ(stack.size(), 0);
}

TEST(stackTest, PushOnEmptyStack) {
  stack<int> stack;
  const int value = 10;
  stack.push(value);

  ASSERT_EQ(stack.top(), value);
  ASSERT_EQ(stack.size(), 1);
  ASSERT_FALSE(stack.empty());
}

TEST(stackTest, PushOnNonEmptyStack) {
  stack<int> stack;
  stack.push(10);
  stack.push(20);

  const int value = 30;
  stack.push(value);

  ASSERT_EQ(stack.top(), value);
  ASSERT_EQ(stack.size(), 3);
  ASSERT_FALSE(stack.empty());
}

TEST(stackTest, PopOnEmptyStack) {
  stack<int> stack;
  ASSERT_THROW(stack.pop(), std::runtime_error);
}

TEST(stackTest, PopOnNonEmptyStack) {
  stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);

  stack.pop();
  ASSERT_EQ(stack.top(), 20);
  ASSERT_EQ(stack.size(), 2);
  ASSERT_FALSE(stack.empty());

  stack.pop();
  ASSERT_EQ(stack.top(), 10);
  ASSERT_EQ(stack.size(), 1);
  ASSERT_FALSE(stack.empty());

  stack.pop();
  ASSERT_THROW(stack.top(), std::runtime_error);
  ASSERT_EQ(stack.size(), 0);
  ASSERT_TRUE(stack.empty());
}

TEST(stackTest, SwapStacks) {
  stack<int> stack1({1, 2, 3});
  stack<int> stack2({4, 5, 6});

  stack1.swap(stack2);

  ASSERT_EQ(stack1.top(), 6);
  ASSERT_EQ(stack1.size(), 3);
  ASSERT_EQ(stack2.top(), 3);
  ASSERT_EQ(stack2.size(), 3);
}

TEST(stackTest, SwapWithItself) {
  stack<int> stack({1, 2, 3});

  stack.swap(stack);

  ASSERT_EQ(stack.top(), 3);
  ASSERT_EQ(stack.size(), 3);
}

TEST(stackTest, SwapEmptyStacks) {
  stack<int> stack1;
  stack<int> stack2;

  stack1.swap(stack2);

  ASSERT_TRUE(stack1.empty());
  ASSERT_TRUE(stack2.empty());
}
