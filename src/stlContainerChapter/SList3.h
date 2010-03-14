/**
 * Implementation of a list holding standard strings
 *   - only std::string objects are stored
 *   - inlining is performed. We allow the Node structure definition to be revealed
 */

#ifndef SLIST3_H
#define SLIST3_H

#include <string>

class SList3 {
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
    friend class SList3;
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
    friend class SList3;

    explicit ConstIterator(const Node *);

    const Node *m_pNode;
  };

  SList3();
  
  SList3(const SList3 &rhs);
  SList3 &operator=(const SList3 &rhs);

  ~SList3();

  ConstIterator begin() const;
  Iterator begin();

  ConstIterator end() const;
  Iterator end();

  void push_front(const std::string &value);

private:
  void createFrom(const SList3 &rhs);
  void release();

  Node *m_pFirstNode;
};

inline SList3::Node::Node(const std::string &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

inline SList3::Iterator::Iterator()
: m_pNode(0)
{}

inline SList3::Iterator &SList3::Iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

inline const SList3::Iterator SList3::Iterator::operator++(int)
{
  Iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

inline std::string *SList3::Iterator::operator->() const
{
  return &m_pNode->m_value;
}

inline std::string &SList3::Iterator::operator*() const
{
  return m_pNode->m_value;
}

inline bool operator==(const SList3::Iterator &lhs, const SList3::Iterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

inline bool operator!=(const SList3::Iterator &lhs, const SList3::Iterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

inline SList3::Iterator::Iterator(Node *pNode)
: m_pNode(pNode)
{}

inline SList3::ConstIterator::ConstIterator()
: m_pNode(0)
{}

inline SList3::ConstIterator::ConstIterator(const Iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

inline SList3::ConstIterator &SList3::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

inline const SList3::ConstIterator SList3::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

inline const std::string *SList3::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

inline const std::string &SList3::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

inline bool operator==(const SList3::ConstIterator &lhs, const SList3::ConstIterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

inline bool operator!=(const SList3::ConstIterator &lhs, const SList3::ConstIterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

inline SList3::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

inline SList3::SList3()
: m_pFirstNode(0)
{}

inline SList3::SList3(const SList3 &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

inline SList3 &SList3::operator=(const SList3 &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

inline SList3::~SList3()
{
  release();
}

inline SList3::ConstIterator SList3::begin() const
{
  return ConstIterator(m_pFirstNode);
}

inline SList3::Iterator SList3::begin()
{
  return Iterator(m_pFirstNode);
}

inline SList3::ConstIterator SList3::end() const
{
  return ConstIterator(0);
}

inline SList3::Iterator SList3::end()
{
  return Iterator(0);
}

inline void SList3::push_front(const std::string &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

#endif
