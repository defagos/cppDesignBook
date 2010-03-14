/**
 * Implementation of a list holding standard strings
 *   - only std::string objects are stored
 *   - inlining is performed, but as long as the Node structure definition can remain hidden
 *     in the implementation file
 */

#ifndef SLIST2_H
#define SLIST2_H

#include <string>

class SList2 {
private:
  struct Node;

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
    friend class SList2;
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
    friend class SList2;

    explicit ConstIterator(const Node *);

    const Node *m_pNode;
  };

  SList2();
  
  SList2(const SList2 &rhs);
  SList2 &operator=(const SList2 &rhs);

  ~SList2();

  ConstIterator begin() const;
  Iterator begin();

  ConstIterator end() const;
  Iterator end();

  void push_front(const std::string &value);

private:
  void createFrom(const SList2 &rhs);
  void release();

  Node *m_pFirstNode;
};

inline SList2::Iterator::Iterator()
: m_pNode(0)
{}

inline bool operator==(const SList2::Iterator &lhs, const SList2::Iterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

inline bool operator!=(const SList2::Iterator &lhs, const SList2::Iterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

inline SList2::Iterator::Iterator(Node *pNode)
: m_pNode(pNode)
{}

inline SList2::ConstIterator::ConstIterator()
: m_pNode(0)
{}

inline SList2::ConstIterator::ConstIterator(const Iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

inline bool operator==(const SList2::ConstIterator &lhs, const SList2::ConstIterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

inline bool operator!=(const SList2::ConstIterator &lhs, const SList2::ConstIterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

inline SList2::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

inline SList2::SList2()
: m_pFirstNode(0)
{}

inline SList2::SList2(const SList2 &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

inline SList2 &SList2::operator=(const SList2 &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

inline SList2::~SList2()
{
  release();
}

inline SList2::ConstIterator SList2::begin() const
{
  return ConstIterator(m_pFirstNode);
}

inline SList2::Iterator SList2::begin()
{
  return Iterator(m_pFirstNode);
}

inline SList2::ConstIterator SList2::end() const
{
  return ConstIterator(0);
}

inline SList2::Iterator SList2::end()
{
  return Iterator(0);
}

#endif
