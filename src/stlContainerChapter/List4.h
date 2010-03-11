#ifndef LIST4_H
#define LIST4_H

// See http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
// See also The C++ programming language, p. 854
// Two options: 1) Inline directly (cleanest syntax)
//              2) Use <> to draw the attention of the compiler on the template nature, define function before it is declared
//                 (or declare function, use <>, then define). Does not seem to work here with iterator classes nested in template
//                 classes...
// Other option here available: Make a member function

#include <cassert>

template<class T>
class List4 {
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

    friend bool operator==(const Iterator &lhs, const Iterator &rhs)
    {
      return lhs.m_pNode == rhs.m_pNode;
    }
    friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
    {
      return lhs.m_pNode != rhs.m_pNode;
    }
  
  private:
    friend class List4;
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

    friend bool operator==(const ConstIterator &lhs, const ConstIterator &rhs)
    {
      return lhs.m_pNode == rhs.m_pNode;
    }
    friend bool operator!=(const ConstIterator &lhs, const ConstIterator &rhs)
    {
      return lhs.m_pNode != rhs.m_pNode;
    }

  private:
    friend class List4;

    explicit ConstIterator(const Node *);

    const Node * m_pNode;
  };

  List4();
  
  List4(const List4 &rhs);
  List4 &operator=(const List4 &rhs);

  ~List4();

  ConstIterator begin() const;
  Iterator begin();

  ConstIterator end() const;
  Iterator end();

  void push_front(const T &value);

private:
  void createFrom(const List4 &rhs);
  void release();

  Node *m_pFirstNode;
};

template<class T>
struct List4<T>::Node {
  Node(const T &value, Node *pNextNode);

  T m_value;
  Node *m_pNextNode;
};

template<class T>
List4<T>::Node::Node(const T &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

template<class T>
List4<T>::Iterator::Iterator()
: m_pNode(0)
{}

template<class T>
typename List4<T>::Iterator &List4<T>::Iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

template<class T>
const typename List4<T>::Iterator List4<T>::Iterator::operator++(int)
{
  Iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

template<class T>
T *List4<T>::Iterator::operator->() const
{
  return &m_pNode->m_value;
}

template<class T>
T &List4<T>::Iterator::operator*() const
{
  return m_pNode->m_value;
}

template<class T>
List4<T>::Iterator::Iterator(Node *pNode)
: m_pNode(pNode)
{}

template<class T>
List4<T>::ConstIterator::ConstIterator()
: m_pNode(0)
{}

template<class T>
List4<T>::ConstIterator::ConstIterator(const Iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

template<class T>
typename List4<T>::ConstIterator &List4<T>::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

template<class T>
const typename List4<T>::ConstIterator List4<T>::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

template<class T>
const T *List4<T>::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

template<class T>
const T &List4<T>::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

template<class T>
List4<T>::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

template<class T>
List4<T>::List4()
: m_pFirstNode(0)
{}

template<class T>
List4<T>::List4(const List4<T> &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

template<class T>
List4<T> &List4<T>::operator=(const List4<T> &rhs)
{
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

template<class T>
List4<T>::~List4()
{
  release();
}

template<class T>
typename List4<T>::ConstIterator List4<T>::begin() const
{
  return ConstIterator(m_pFirstNode);
}

template<class T>
typename List4<T>::Iterator List4<T>::begin()
{
  return Iterator(m_pFirstNode);
}

template<class T>
typename List4<T>::ConstIterator List4<T>::end() const
{
  return ConstIterator(0);
}

template<class T>
typename List4<T>::Iterator List4<T>::end()
{
  return Iterator(0);
}

template<class T>
void List4<T>::push_front(const T &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

template<class T>
void List4<T>::createFrom(const List4<T> &rhs)
{
  // Can only create if current list is empty
  assert(m_pFirstNode == 0);

  Node *pRhsNode = rhs.m_pFirstNode;
  Node *pNode = 0;
  while (pRhsNode) {
    if (! m_pFirstNode) {
      m_pFirstNode = new Node(pRhsNode->m_value, 0);
      pNode = m_pFirstNode;
    }
    else {
      pNode->m_pNextNode = new Node(pRhsNode->m_value, 0);
      pNode = pNode->m_pNextNode;
    }
    pRhsNode = pRhsNode->m_pNextNode;
  }
}

template<class T>
void List4<T>::release()
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
