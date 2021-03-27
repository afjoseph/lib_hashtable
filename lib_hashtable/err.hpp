#pragma once
namespace lib_hashtable {
using err_t = enum {
  ERR_OK,
  ERR_NO_MEMORY,
  HASHTABLE_ERR_BAD,
  HASHTABLE_ERR_ELEMENT_NOT_FOUND,
  LINKEDLIST_ERR_BAD,
  LINKEDLIST_ERR_ELEMENT_NOT_FOUND,
};
} // namespace
