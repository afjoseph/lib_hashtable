#include "hashtable.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace lib_hashtable;

TEST(HashTableTests, TestFunctional_int_to_string_with_overloaded_hash_func)
{
  // Make a table
  auto table = HashTable<int, std::string, 10>(
    [](const auto key, auto max_size) { return key % max_size; });
  // Add a few elements
  auto err = table.put(111, "111");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put(222, "222");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put(333, "333");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  // Add a value to the same key, and check if it is overridden properly
  err = table.put(333, "new_ccc_value");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  std::string actual_value;
  err = table.get(333, actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("new_ccc_value", actual_value) << " : " << err;
  // Get a value
  err = table.get(111, actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("111", actual_value) << " : " << err;
  // Try to get a bad value
  err = table.get(999, actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Get a value and see if it is still there
  err = table.remove(111);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.get(111, actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  err = table.remove(111);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Add element in a different scope and then check it inside and outside the
  // scope
  {
    err = table.put(444, "my_value");
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    err = table.get(444, actual_value);
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    ASSERT_EQ("my_value", actual_value) << " : " << err;
  }
  err = table.get(444, actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("my_value", actual_value) << " : " << err;
}

TEST(HashTableTests, TestFunctional_int_to_string)
{
  // Make a table
  auto table = HashTable<int, std::string, 10>();
  // Add a few elements
  auto err = table.put(111, "111");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put(222, "222");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put(333, "333");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  // Add a value to the same key, and check if it is overridden properly
  err = table.put(333, "new_ccc_value");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  std::string actual_value;
  err = table.get(333, actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("new_ccc_value", actual_value) << " : " << err;
  // Get a value
  err = table.get(111, actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("111", actual_value) << " : " << err;
  // Try to get a bad value
  err = table.get(999, actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Get a value and see if it is still there
  err = table.remove(111);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.get(111, actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  err = table.remove(111);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Add element in a different scope and then check it inside and outside the
  // scope
  {
    err = table.put(444, "my_value");
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    err = table.get(444, actual_value);
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    ASSERT_EQ("my_value", actual_value) << " : " << err;
  }
  err = table.get(444, actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("my_value", actual_value) << " : " << err;
}

TEST(HashTableTests, TestFunctional_string_to_string)
{
  // Make a table
  auto table = HashTable<std::string, std::string, 10>();
  // Add a few elements
  auto err = table.put("aaa", "111");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put("bbb", "222");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put("ccc", "333");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  // Add a value to the same key, and check if it is overridden properly
  err = table.put("ccc", "new_ccc_value");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  std::string actual_value;
  err = table.get("ccc", actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("new_ccc_value", actual_value) << " : " << err;
  // Get a value
  err = table.get("aaa", actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("111", actual_value) << " : " << err;
  // Try to get a bad value
  err = table.get("bunnyfoofoo", actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Get a value and see if it is still there
  err = table.remove("aaa");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.get("aaa", actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  err = table.remove("aaa");
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Add element in a different scope and then check it inside and outside the
  // scope
  {
    err = table.put("my_key", "my_value");
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    err = table.get("my_key", actual_value);
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    ASSERT_EQ("my_value", actual_value) << " : " << err;
  }
  err = table.get("my_key", actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("my_value", actual_value) << " : " << err;
}

TEST(HashTableTests, TestBenchmarks)
{
  // Make a table
  auto table = HashTable<std::string, std::string, 10>();
  // Add 100 elements, measuring the speed of each
  // Add another 100, measuring the speed of each
  // Add another 100, measuring the speed of each
  // Get 100, measuring the speed of each
  // Get another 100, measuring the speed of each
  // Get another 100, measuring the speed of each
  // Remove 100, measuring the speed of each
  // Remove another 100, measuring the speed of each
  // Remove another 100, measuring the speed of each
  // Add a few elements
  auto err = table.put("aaa", "111");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put("bbb", "222");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.put("ccc", "333");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  // Add a value to the same key, and check if it is overridden properly
  err = table.put("ccc", "new_ccc_value");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  std::string actual_value;
  err = table.get("ccc", actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("new_ccc_value", actual_value) << " : " << err;
  // Get a value
  err = table.get("aaa", actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("111", actual_value) << " : " << err;
  // Try to get a bad value
  err = table.get("bunnyfoofoo", actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Get a value and see if it is still there
  err = table.remove("aaa");
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  err = table.get("aaa", actual_value);
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  err = table.remove("aaa");
  ASSERT_EQ(err, HASHTABLE_ERR_ELEMENT_NOT_FOUND) << " : " << err;
  // Add element in a different scope and then check it inside and outside the
  // scope
  {
    err = table.put("my_key", "my_value");
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    err = table.get("my_key", actual_value);
    ASSERT_EQ(err, ERR_OK) << " : " << err;
    ASSERT_EQ("my_value", actual_value) << " : " << err;
  }
  err = table.get("my_key", actual_value);
  ASSERT_EQ(err, ERR_OK) << " : " << err;
  ASSERT_EQ("my_value", actual_value) << " : " << err;
}

auto
main(int argc, char** argv) -> int
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
