#ifndef LIST_H
#define LIST_H

#include <cassert>
// Include for std::allocator
#include <memory>
#include <iterator>

// Two choices:
// 1) Include <iterator>, derive each iterator class from std::iterator publicly
//    Good, what std::iterator is for. Problem: Name clashes => every time we use iterator in a child class, we must say
//    typename List<T, A>::iterator, otherwise if we mean "the list iterator", otherwise the compiler will
//    interpret an iterator as std::iterator! Not a serious problem, though.
// 2) Instead of using std::iterator to provide the typedefs, simply typedef manually. More code, but less notation
//    since no disambiguation needed for iterator (<iterator> also needed since forward_iterator_tag is defined there)
// We may choose between 1) and 2) since (see TC++PL, p. 553: "CAN be used to define those member types")

template<class T, class A = std::allocator<T> >
class List {
private:
  struct Node;

public:
  typedef typename A::value_type value_type;
  typedef typename A::size_type size_type;
  typedef typename A::difference_type difference_type;

  typedef typename A::pointer pointer;
  typedef typename A::const_pointer const_pointer;

  typedef typename A::reference reference;
  typedef typename A::const_reference const_reference;

  class iterator;

  class const_iterator {
  public:
    // Method 2): Manual typedefs
    typedef std::forward_iterator_tag iterator_category;
    // No prefixing needed here, value_type from class above, i.e. List. But maybe better to be explicit (more readable)?
    typedef typename List<T, A>::value_type value_type;
    typedef typename List<T, A>::difference_type difference_type;
    typedef typename List<T, A>::const_pointer pointer;
    typedef typename List<T, A>::const_reference reference;

    const_iterator();
    const_iterator(const iterator &rhs);

    const_iterator &operator++();
    const const_iterator operator++(int);

    const T *operator->() const;
    const T &operator*() const;

    friend bool operator==(const const_iterator &lhs, const const_iterator &rhs)
    {
      return lhs.m_pNode == rhs.m_pNode;
    }
    friend bool operator!=(const const_iterator &lhs, const const_iterator &rhs)
    {
      return lhs.m_pNode != rhs.m_pNode;
    }

  private:
    friend class List;

    explicit const_iterator(const Node *);

    const Node *m_pNode;
  };

  class iterator {
  public:
    // Method 2): Manual typedefs
    typedef std::forward_iterator_tag iterator_category;
    // No prefixing needed here, value_type from class above, i.e. List. But maybe better to be explicit (more readable)? Nope, definitely
    // better since generates errors with g++!
    typedef typename List<T, A>::value_type value_type;
    typedef typename List<T, A>::difference_type difference_type;
    typedef typename List<T, A>::pointer pointer;
    typedef typename List<T, A>::reference reference;

    iterator();

    iterator &operator++();
    const iterator operator++(int);

    T *operator->() const;
    T &operator*() const;

    friend bool operator==(const iterator &lhs, const iterator &rhs)
    {
      return lhs.m_pNode == rhs.m_pNode;
    }
    friend bool operator!=(const iterator &lhs, const iterator &rhs)
    {
      return lhs.m_pNode != rhs.m_pNode;
    }
  
  private:
    friend class List;
    friend class const_iterator;

    explicit iterator(Node *pNode);

    Node *m_pNode;
  };

  List();
  
  List(const List &rhs);
  List &operator=(const List &rhs);

  ~List();

  const_iterator begin() const;
  iterator begin();

  const_iterator end() const;
  iterator end();

  void push_front(const T &value);

private:
  void createFrom(const List &rhs);
  void release();

  Node *m_pFirstNode;
};

template<class T, class A>
struct List<T, A>::Node {
  Node(const T &value, Node *pNextNode);

  T m_value;
  Node *m_pNextNode;
};

template<class T, class A>
List<T, A>::Node::Node(const T &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

template<class T, class A>
List<T, A>::const_iterator::const_iterator()
: m_pNode(0)
{}

template<class T, class A>
List<T, A>::const_iterator::const_iterator(const iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

template<class T, class A>
typename List<T, A>::const_iterator &List<T, A>::const_iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

template<class T, class A>
const typename List<T, A>::const_iterator List<T, A>::const_iterator::operator++(int)
{
  const_iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

template<class T, class A>
const T *List<T, A>::const_iterator::operator->() const
{
  return &m_pNode->m_value;
}

template<class T, class A>
const T &List<T, A>::const_iterator::operator*() const
{
  return m_pNode->m_value;
}

template<class T, class A>
List<T, A>::const_iterator::const_iterator(const Node *pNode)
: m_pNode(pNode)
{}

template<class T, class A>
List<T, A>::iterator::iterator()
: m_pNode(0)
{}

template<class T, class A>
typename List<T, A>::iterator &List<T, A>::iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

template<class T, class A>
const typename List<T, A>::iterator List<T, A>::iterator::operator++(int)
{
  iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

template<class T, class A>
T *List<T, A>::iterator::operator->() const
{
  return &m_pNode->m_value;
}

template<class T, class A>
T &List<T, A>::iterator::operator*() const
{
  return m_pNode->m_value;
}

template<class T, class A>
List<T, A>::iterator::iterator(Node *pNode)
: m_pNode(pNode)
{}

template<class T, class A>
List<T, A>::List()
: m_pFirstNode(0)
{}

template<class T, class A>
List<T, A>::List(const List<T, A> &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

template<class T, class A>
List<T, A> &List<T, A>::operator=(const List<T, A> &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

template<class T, class A>
List<T, A>::~List()
{
  release();
}

template<class T, class A>
typename List<T, A>::const_iterator List<T, A>::begin() const
{
  return const_iterator(m_pFirstNode);
}

template<class T, class A>
typename List<T, A>::iterator List<T, A>::begin()
{
  return iterator(m_pFirstNode);
}

template<class T, class A>
typename List<T, A>::const_iterator List<T, A>::end() const
{
  return const_iterator(0);
}

template<class T, class A>
typename List<T, A>::iterator List<T, A>::end()
{
  return iterator(0);
}

template<class T, class A>
void List<T, A>::push_front(const T &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

/**
 * Function factoring out the code for creating a list from an existing one. Must
 * be called only on an empty list
 */
template<class T, class A>
void List<T, A>::createFrom(const List<T, A> &rhs)
{
  // Ensure that the list is empty
  assert(m_pFirstNode == 0);

  Node *pRhsNode = rhs.m_pFirstNode;
  Node *pNode = 0;
  while (pRhsNode) {
    // Empty list; create first node
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
template<class T, class A>
void List<T, A>::release()
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
