#include "SList1.h"

#include <cassert>

struct SList1::Node {
  Node(const std::string &value, Node *pNextNode);

  std::string m_value;
  Node *m_pNextNode;
};

SList1::Node::Node(const std::string &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

SList1::Iterator::Iterator()
: m_pNode(0)
{}

SList1::Iterator &SList1::Iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

const SList1::Iterator SList1::Iterator::operator++(int)
{
  Iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

std::string *SList1::Iterator::operator->() const
{
  return &m_pNode->m_value;
}

std::string &SList1::Iterator::operator*() const
{
  return m_pNode->m_value;
}

bool operator==(const SList1::Iterator &lhs, const SList1::Iterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

bool operator!=(const SList1::Iterator &lhs, const SList1::Iterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

SList1::Iterator::Iterator(Node *pNode)
: m_pNode(pNode)
{}

SList1::ConstIterator::ConstIterator()
: m_pNode(0)
{}

SList1::ConstIterator::ConstIterator(const Iterator &rhs)
: m_pNode(rhs.m_pNode)
{}

SList1::ConstIterator &SList1::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

const SList1::ConstIterator SList1::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

const std::string *SList1::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

const std::string &SList1::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

bool operator==(const SList1::ConstIterator &lhs, const SList1::ConstIterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

bool operator!=(const SList1::ConstIterator &lhs, const SList1::ConstIterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

SList1::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

SList1::SList1()
: m_pFirstNode(0)
{}

SList1::SList1(const SList1 &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

SList1 &SList1::operator=(const SList1 &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

SList1::~SList1()
{
  release();
}

SList1::ConstIterator SList1::begin() const
{
  return ConstIterator(m_pFirstNode);
}

SList1::Iterator SList1::begin()
{
  return Iterator(m_pFirstNode);
}

SList1::ConstIterator SList1::end() const
{
  return ConstIterator(0);
}

SList1::Iterator SList1::end()
{
  return Iterator(0);
}

void SList1::push_front(const std::string &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

/**
 * Function factoring out the code for creating a list from an existing one. Must
 * be called only on an empty list
 */
void SList1::createFrom(const SList1 &rhs)
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
void SList1::release()
{
  Node *pNode = m_pFirstNode;
  while (pNode) {
    Node *pNextNode = pNode->m_pNextNode;
    delete pNode;
    pNode = pNextNode;
  }
  m_pFirstNode = 0;
}
