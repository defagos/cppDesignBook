/**
 * Implementation of a list holding standard strings
 *   - only std::string objects are stored
 *   - inlining is performed. We allow the Node structure definition to be revealed
 */

#ifndef SLIST_H
#define SLIST_H

#include <string>

class SList {
private:
  struct Node {
    Node(const std::string &value, Node *pNextNode);

    std::string m_value;
    Node *m_pNextNode;
  };

public:
  class ConstIterator;

  class Iterator {
  public:
    Iterator();

    Iterator &operator++();
    const Iterator operator++(int);

    std::string *operator->() const;
    std::string &operator*() const;

    friend bool operator==(const Iterator &lhs, const Iterator &rhs);
    friend bool operator!=(const Iterator &lhs, const Iterator &rhs);
  
  private:
    friend class SList;
    friend class ConstIterator;

    explicit Iterator(Node *pNode);

    Node *m_pNode;
  };

  class ConstIterator {
  public:
    ConstIterator();
    ConstIterator(const Iterator &rhs);

    ConstIterator &operator++();
    const ConstIterator operator++(int);

    const std::string *operator->() const;
    const std::string &operator*() const;

    friend bool operator==(const ConstIterator &lhs, const ConstIterator &rhs);
    friend bool operator!=(const ConstIterator &lhs, const ConstIterator &rhs);

  private:
    friend class SList;

    explicit ConstIterator(const Node *);

    const Node *m_pNode;
  };

  SList();
  
  SList(const SList &rhs);
  SList &operator=(const SList &rhs);

  ~SList();

  ConstIterator begin() const;
  Iterator begin();

  ConstIterator end() const;
  Iterator end();

  void push_front(const std::string &value);

private:
  void createFrom(const SList &rhs);
  void release();

  Node *m_pFirstNode;
};

inline SList::Node::Node(const std::string &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

inline SList::Iterator::Iterator()
: m_pNode(0)
{}

inline SList::Iterator &SList::Iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

inline const SList::Iterator SList::Iterator::operator++(int)
{
  Iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

inline std::string *SList::Iterator::operator->() const
{
  return &m_pNode->m_value;
}

inline std::string &SList::Iterator::operator*() const
{
  return m_pNode->m_value;
}

inline bool operator==(const SList::Iterator &lhs, const SList::Iterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

inline bool operator!=(const SList::Iterator &lhs, const SList::Iterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

inline SList::Iterator::Iterator(Node *pNode)
: m_pNode(pNode)
{}

inline SList::ConstIterator::ConstIterator()
: m_pNode(0)
{}

inline SList::ConstIterator::ConstIterator(const Iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

inline SList::ConstIterator &SList::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

inline const SList::ConstIterator SList::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

inline const std::string *SList::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

inline const std::string &SList::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

inline bool operator==(const SList::ConstIterator &lhs, const SList::ConstIterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

inline bool operator!=(const SList::ConstIterator &lhs, const SList::ConstIterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

inline SList::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

inline SList::SList()
: m_pFirstNode(0)
{}

inline SList::SList(const SList &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

inline SList &SList::operator=(const SList &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

inline SList::~SList()
{
  release();
}

inline SList::ConstIterator SList::begin() const
{
  return ConstIterator(m_pFirstNode);
}

inline SList::Iterator SList::begin()
{
  return Iterator(m_pFirstNode);
}

inline SList::ConstIterator SList::end() const
{
  return ConstIterator(0);
}

inline SList::Iterator SList::end()
{
  return Iterator(0);
}

inline void SList::push_front(const std::string &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

#endif
