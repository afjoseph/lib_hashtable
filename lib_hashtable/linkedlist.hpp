#pragma once
#include "err.hpp"
#include <new>
#include <utility>

namespace lib_hashtable {
template<typename T>
class LinkedListNode
{
public:
  explicit LinkedListNode(const T& a_value)
    : m_value(std::move(a_value))
    , m_next(nullptr)
  {}
  auto value() -> T& { return m_value; }
  auto next() -> LinkedListNode<T>*
  {
    if (m_next) {
      return m_next;
    }
    return nullptr;
  }
  void set_next(LinkedListNode<T>* a_next) { m_next = a_next; }

private:
  T m_value;
  LinkedListNode<T>* m_next;
};

template<typename T>
class LinkedList
{
private:
  LinkedListNode<T>* m_head_node;
  size_t m_size{ 0 };

public:
  LinkedList()
    : m_head_node(nullptr){};
  ~LinkedList()
  {
    while (m_head_node != nullptr) {
      remove_head();
    }
    delete m_head_node;
    m_head_node = nullptr;
  };

  auto head() -> LinkedListNode<T>* { return m_head_node; }
  auto size() -> size_t { return m_size; }
  auto empty() -> bool { return m_size == 0; }

  // insert a node at the end
  auto insert_at_head(const T& value) -> err_t
  {
    // Make a new node
    auto* new_node = new (std::nothrow) LinkedListNode<T>(value);
    if (!new_node) {
      return ERR_NO_MEMORY;
    }

    // Switch head
    /* 2 -> 1 -> 0 */
    /* 3 */
    if (!m_head_node) {
      m_head_node = new_node;
    } else {
      new_node->set_next(m_head_node);
      m_head_node = new_node;
    }
    m_size++;
    return ERR_OK;
  }

  auto remove_node(LinkedListNode<T>* target_node) -> err_t
  {
    if (!m_head_node) {
      return LINKEDLIST_ERR_ELEMENT_NOT_FOUND;
    }
    LinkedListNode<T>* curr_node = m_head_node;
    LinkedListNode<T>* prev_node = nullptr;
    bool did_find = false;
    while (curr_node) {
      if (curr_node == target_node) {
        if (curr_node == m_head_node) {
          // Assuming we wanna remove 2
          //    before: 2 -> 1 -> 0
          //    after: 1 -> 0
          // So, we loop. We see target_node == iter == 2
          // we make m_head_node = curr->next
          // and remove target_node
          m_head_node = curr_node->next();
        } else {
          // Assuming we wanna remove 1
          //    before: 2 -> 1 -> 0
          //    after: 2 -> 0
          // So, we loop. We see target_node == iter == 1
          // m_head_node doesn't change
          // now, we need to tell 2 to point to 0, not to 1
          // we can have a curr and prev iter.
          // prev->next = curr->next
          // 2->next = 1->next
          //
          // Assuming we wanna remove 0
          //    before: 2 -> 1 -> 0
          //    after: 2 -> 1
          // So, we loop. We see target_node == iter == 0
          // m_head_node doesn't change
          // prev->next = curr->next
          // 1->next = 0->next = nullptr
          prev_node->set_next(curr_node->next());
        }
        did_find = true;
        m_size--;
        delete target_node;
        target_node = nullptr;
        break;
      }
      prev_node = curr_node;
      curr_node = curr_node->next();
    }

    if (!did_find) {
      return LINKEDLIST_ERR_ELEMENT_NOT_FOUND;
    }
    return ERR_OK;
  }

  auto remove_head() -> err_t
  {
    if (!m_head_node) {
      return LINKEDLIST_ERR_ELEMENT_NOT_FOUND;
    }
    // Get current head node
    auto* popped_node = m_head_node;
    // Switch head node
    // before: 2 -> 1 -> 0
    // after: 1 -> 0
    m_head_node = m_head_node->next();
    // delete node
    delete popped_node;
    popped_node = nullptr;
    m_size--;
    return ERR_OK;
  }

  auto remove_head_and_return(T& out_value) -> err_t
  {
    if (!m_head_node) {
      return LINKEDLIST_ERR_ELEMENT_NOT_FOUND;
    }
    // Get current head node
    auto* popped_node = m_head_node;
    // Switch head node
    // before: 2 -> 1 -> 0
    // after: 1 -> 0
    m_head_node = m_head_node->next();
    // Assign out_value
    out_value = popped_node->value();
    // delete node
    delete popped_node;
    popped_node = 0;
    m_size--;
    return ERR_OK;
  }
};
} // namespace
