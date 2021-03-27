#include "linkedlist.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace lib_hashtable;

TEST(LinkedListTests, TestFunctional)
{
  // Make a list
  auto list = LinkedList<std::string>();
  // Insert few things & check
  auto err = list.insert_at_head("aaa");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ(1, list.size()) << " : " << err;
  ASSERT_EQ("aaa", list.head()->value());
  err = list.insert_at_head("bbb");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ(2, list.size()) << " : " << err;
  ASSERT_EQ("bbb", list.head()->value());
  err = list.insert_at_head("ccc");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ(3, list.size()) << " : " << err;
  ASSERT_EQ("ccc", list.head()->value());
  err = list.insert_at_head("ddd");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ(4, list.size()) << " : " << err;
  ASSERT_EQ("ddd", list.head()->value());
  // Remove an element
  std::string torn_value;
  err = list.remove_head_and_return(torn_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ(3, list.size()) << " : " << err;
  ASSERT_EQ("ccc", list.head()->value());
  ASSERT_EQ("ddd", torn_value);
  // Iterate list and make sure order is as expected
  auto node = list.head();
  ASSERT_EQ("ccc", node->value());
  node = node->next();
  auto target_node = node;
  ASSERT_EQ("bbb", node->value());
  node = node->next();
  ASSERT_EQ("aaa", node->value());
  node = node->next();
  ASSERT_EQ(nullptr, node);
  // Remove random node and check if order is as expected
  err = list.remove_node(target_node);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  node = list.head();
  ASSERT_EQ("ccc", node->value());
  node = node->next();
  ASSERT_EQ("aaa", node->value());
  node = node->next();
  ASSERT_EQ(nullptr, node);
  ASSERT_EQ(2, list.size()) << " : " << err;
  // Add element in a different scope and then check it inside and outside the
  // scope
  {
    err = list.insert_at_head("bunnyfoofoo");
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    ASSERT_EQ(3, list.size()) << " : " << err;
    ASSERT_EQ("bunnyfoofoo", list.head()->value());
  }
  ASSERT_EQ(3, list.size()) << " : " << err;
  ASSERT_EQ("bunnyfoofoo", list.head()->value());
}

auto
main(int argc, char** argv) -> int
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
