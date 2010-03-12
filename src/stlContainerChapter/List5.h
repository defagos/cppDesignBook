/**
 * Implementation of a list container
 *   - does not conform to the STL conventions
 *   - iterator comparison operators as member functions
 */

#ifndef LIST5_H
#define LIST5_H

#include <cassert>

template<class T>
class List5 {
private:
  struct Node;

public:
  class ConstIterator;

  class Iterator {
  public:
    Iterator();

    Iterator &operator++();
    const Iterator operator++(int);

    T *operator->() const;
    T &operator*() const;

    bool operator==(const Iterator &rhs);
    bool operator!=(const Iterator &rhs);
  
  private:
    friend class List5;
    friend class ConstIterator;

    explicit Iterator(Node *pNode);

    Node * m_pNode;
  };

  class ConstIterator {
  public:
    ConstIterator();
    ConstIterator(const Iterator &rhs);

    ConstIterator &operator++();
    const ConstIterator operator++(int);

    const T *operator->() const;
    const T &operator*() const;

    bool operator==(const ConstIterator &rhs);
    bool operator!=(const ConstIterator &rhs);

  private:
    friend class List5;

    explicit ConstIterator(const Node *);

    const Node * m_pNode;
  };

  List5();
  
  List5(const List5 &rhs);
  List5 &operator=(const List5 &rhs);

  ~List5();

  ConstIterator begin() const;
  Iterator begin();

  ConstIterator end() const;
  Iterator end();

  void push_front(const T &value);

private:
  void createFrom(const List5 &rhs);
  void release();

  Node *m_pFirstNode;
};

template<class T>
struct List5<T>::Node {
  Node(const T &value, Node *pNextNode);

  T m_value;
  Node *m_pNextNode;
};

template<class T>
List5<T>::Node::Node(const T &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

template<class T>
List5<T>::Iterator::Iterator()
: m_pNode(0)
{}

template<class T>
typename List5<T>::Iterator &List5<T>::Iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

template<class T>
const typename List5<T>::Iterator List5<T>::Iterator::operator++(int)
{
  Iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

template<class T>
T *List5<T>::Iterator::operator->() const
{
  return &m_pNode->m_value;
}

template<class T>
T &List5<T>::Iterator::operator*() const
{
  return m_pNode->m_value;
}

template<class T>
bool List5<T>::Iterator::operator==(const typename List5<T>::Iterator &rhs)
{
  return m_pNode == rhs.m_pNode;
}

template<class T>
bool List5<T>::Iterator::operator!=(const typename List5<T>::Iterator &rhs)
{
  return m_pNode != rhs.m_pNode;
}

template<class T>
List5<T>::Iterator::Iterator(Node *pNode)
: m_pNode(pNode)
{}

template<class T>
List5<T>::ConstIterator::ConstIterator()
: m_pNode(0)
{}

template<class T>
List5<T>::ConstIterator::ConstIterator(const Iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

template<class T>
typename List5<T>::ConstIterator &List5<T>::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

template<class T>
const typename List5<T>::ConstIterator List5<T>::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

template<class T>
const T *List5<T>::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

template<class T>
const T &List5<T>::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

template<class T>
bool List5<T>::ConstIterator::operator==(const typename List5<T>::ConstIterator &rhs)
{
  return m_pNode == rhs.m_pNode;
}

template<class T>
bool List5<T>::ConstIterator::operator!=(const typename List5<T>::ConstIterator &rhs)
{
  return m_pNode != rhs.m_pNode;
}

template<class T>
List5<T>::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

template<class T>
List5<T>::List5()
: m_pFirstNode(0)
{}

template<class T>
List5<T>::List5(const List5<T> &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

template<class T>
List5<T> &List5<T>::operator=(const List5<T> &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

template<class T>
List5<T>::~List5()
{
  release();
}

template<class T>
typename List5<T>::ConstIterator List5<T>::begin() const
{
  return ConstIterator(m_pFirstNode);
}

template<class T>
typename List5<T>::Iterator List5<T>::begin()
{
  return Iterator(m_pFirstNode);
}

template<class T>
typename List5<T>::ConstIterator List5<T>::end() const
{
  return ConstIterator(0);
}

template<class T>
typename List5<T>::Iterator List5<T>::end()
{
  return Iterator(0);
}

template<class T>
void List5<T>::push_front(const T &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

/**
 * Function factoring out the code for creating a list from an existing one. Must
 * be called only on an empty list
 */
template<class T>
void List5<T>::createFrom(const List5<T> &rhs)
{
  // Can only create if current list is empty
  assert(m_pFirstNode == 0);

  Node *pRhsNode = rhs.m_pFirstNode;
  Node *pNode = 0;
  while (pRhsNode) {
    // Ensure that the list is empty
    if (! m_pFirstNode) {
      m_pFirstNode = new Node(pRhsNode->m_value, 0);
      pNode = m_pFirstNode;
    }
    // Add following nodes
    else {
      pNode->m_pNextNode = new Node(pRhsNode->m_value, 0);
      pNode = pNode->m_pNextNode;
    }
    pRhsNode = pRhsNode->m_pNextNode;
  }
}

/**
 * Function factoring out the cleanup code
 */
template<class T>
void List5<T>::release()
{
  Node *pNode = m_pFirstNode;
  while (pNode) {
    Node *pNextNode = pNode->m_pNextNode;
    delete pNode;
    pNode = pNextNode;
  }
  m_pFirstNode = 0;
}

#endif
