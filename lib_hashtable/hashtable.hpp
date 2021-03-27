#pragma once
#include "err.hpp"
#include "linkedlist.hpp"
#include <array>

#define UNUSED(x)                                                              \
  do {                                                                         \
    (void)(x);                                                                 \
  } while (0);

namespace lib_hashtable {
template<typename K, typename V>
class HashTableNode
{
public:
  HashTableNode(K a_key, V a_value)
    : m_key(std::move(a_key))
    , m_value(std::move(a_value))
  {}
  auto value() -> V& { return m_value; }
  auto key() -> K& { return m_key; }
  auto set_value(V a_value) { m_value = std::move(a_value); }

private:
  K m_key;
  V m_value;
};

template<typename K, typename V, size_t buckets_size>
class HashTable
{
private:
  std::array<LinkedList<HashTableNode<K, V>>*, buckets_size> m_buckets;
  const size_t m_buckets_size;
  std::function<size_t(const K&, const size_t)> m_get_key_hash_func;
  static size_t get_key_hash__default(const K& key, const size_t max_size)
  {
    return std::hash<K>{}(key) % max_size;
  }

public:
  HashTable()
    : m_buckets()
    , m_buckets_size(buckets_size)
    , m_get_key_hash_func(get_key_hash__default)
  {}
  HashTable(std::function<size_t(const K&, const size_t)> get_key_hash_func)
    : m_buckets()
    , m_buckets_size(buckets_size)
    , m_get_key_hash_func(get_key_hash_func)
  {}
  ~HashTable()
  {
    // Loop over all buckets and delete them
    for (size_t i = 0; i < m_buckets_size; i++) {
      delete m_buckets[i];
      m_buckets[i] = nullptr;
    }
  }

  auto size() -> size_t { return m_buckets_size; };

  // put takes "key", creates a hashcode from it, and uses that hashcode as an
  // index to where it would copy "value" in the buckets. This happens by
  // making a LinkedList in the indexed location and inserting "value" to be
  // the first element in the index.  In higher-level languages, this would
  // means something like this:
  //
  //    def put(table, key, value):
  //       if not table[hash(key)]:
  //           table[hash(key)] = LinkedList()
  //       table[hash(key)].append(value)
  auto put(const K& key, const V& value) -> err_t
  {
    // Calculate hashcode from key
    /* const size_t key_hash = std::hash<K>{}(key) % m_buckets_size; */
    size_t key_hash = m_get_key_hash_func(key, m_buckets_size);
    // Take the result and place it in m_buckets
    if (!m_buckets[key_hash]) {
      // If there's no value there, make a new linkedlist
      m_buckets[key_hash] =
        new (std::nothrow) LinkedList<HashTableNode<K, V>>();
      if (!m_buckets[key_hash]) {
        return ERR_NO_MEMORY;
      }
    }
    // If there is, check if the key exists in the list
    LinkedListNode<HashTableNode<K, V>>* iter = m_buckets[key_hash]->head();
    bool did_find = false;
    while (iter) {
      if (iter->value().key() == key) {
        // if we found a duplicate, just replace the value
        iter->value().set_value(value);
        did_find = true;
        break;
      }
      iter = iter->next();
    }
    // If we didn't find a duplicate, insert this value in the list
    if (!did_find) {
      auto err =
        m_buckets[key_hash]->insert_at_head(HashTableNode<K, V>(key, value));
      if (err != ERR_OK) {
        return err;
      }
    }
    return ERR_OK;
  }

  // get takes "const &key" and the value in "out_value" if it was found, or
  // HASHTABLE_ERR_ELEMENT_NOT_FOUND if not found
  auto get(const K& key, V& out_value) -> err_t
  {
    // Calculate hashcode from key
    const size_t key_hash = std::hash<K>{}(key) % m_buckets_size;
    if (!m_buckets[key_hash]) {
      return HASHTABLE_ERR_ELEMENT_NOT_FOUND;
    }
    // loop over all nodes in the linked list
    auto iter = m_buckets[key_hash]->head();
    bool did_find = false;
    while (iter) {
      //   if node.key == key, return a copy of node.value
      if (iter->value().key() == key) {
        out_value = iter->value().value();
        did_find = true;
      }
      iter = iter->next();
    }
    if (!did_find) {
      //   else, return HASHTABLE_ERR_ELEMENT_NOT_FOUND
      return HASHTABLE_ERR_ELEMENT_NOT_FOUND;
    }
    return ERR_OK;
  }

  // remove takes "const &key" and removes it and value if it found it
  // HASHTABLE_ERR_ELEMENT_NOT_FOUND if not found
  auto remove(const K& key) -> err_t
  {
    // Calculate hashcode from key
    const size_t key_hash = std::hash<K>{}(key) % m_buckets_size;
    if (!m_buckets[key_hash]) {
      return HASHTABLE_ERR_ELEMENT_NOT_FOUND;
    }
    // loop over all nodes in the linked list
    auto iter = m_buckets[key_hash]->head();
    bool did_find = false;
    while (iter) {
      //   if node.key == key, remove that specific node from the list
      if (iter->value().key() == key) {
        auto err = m_buckets[key_hash]->remove_node(iter);
        if (err != ERR_OK) {
          return err;
        }
        did_find = true;
        break;
      }
      iter = iter->next();
    }
    if (!did_find) {
      //   else, return HASHTABLE_ERR_ELEMENT_NOT_FOUND
      return HASHTABLE_ERR_ELEMENT_NOT_FOUND;
    }
    return ERR_OK;
  }
}; // class HashTable
} // namespace
