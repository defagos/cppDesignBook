#include "SList0.h"

#include <cassert>

struct SList0::Node {
  Node(const std::string &value, Node *pNextNode);

  std::string m_value;
  Node *m_pNextNode;
};

SList0::Node::Node(const std::string &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

SList0::ConstIterator::ConstIterator()
: m_pNode(0)
{}

SList0::ConstIterator &SList0::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

const SList0::ConstIterator SList0::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

const std::string *SList0::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

const std::string &SList0::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

bool operator==(const SList0::ConstIterator &lhs, const SList0::ConstIterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

bool operator!=(const SList0::ConstIterator &lhs, const SList0::ConstIterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

SList0::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

SList0::Iterator::Iterator()
{}

SList0::Iterator &SList0::Iterator::operator++()
{
  ConstIterator::operator++();
  return *this;
}

const SList0::Iterator SList0::Iterator::operator++(int)
{
  Iterator tmp(*this);
  // Call post-increment version
  ConstIterator::operator++(0);
  return tmp;
}

std::string *SList0::Iterator::operator->() const
{
  // Need to cast constness away here, the price to pay for using inheritance
  return const_cast<std::string *>(ConstIterator::operator->());
}

std::string &SList0::Iterator::operator*() const
{
  // Need to cast constness away here, the price to pay for using inheritance
  return const_cast<std::string &>(ConstIterator::operator*());
}

SList0::Iterator::Iterator(Node *pNode)
: ConstIterator(pNode)
{}

SList0::SList0()
: m_pFirstNode(0)
{}

SList0::SList0(const SList0 &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

SList0 &SList0::operator=(const SList0 &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

SList0::~SList0()
{
  release();
}

SList0::ConstIterator SList0::begin() const
{
  return ConstIterator(m_pFirstNode);
}

SList0::Iterator SList0::begin()
{
  return Iterator(m_pFirstNode);
}

SList0::ConstIterator SList0::end() const
{
  return ConstIterator(0);
}

SList0::Iterator SList0::end()
{
  return Iterator(0);
}

void SList0::push_front(const std::string &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

/**
 * Function factoring out the code for creating a list from an existing one. Must
 * be called only on an empty list
 */
void SList0::createFrom(const SList0 &rhs)
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
void SList0::release()
{
  Node *pNode = m_pFirstNode;
  while (pNode) {
    Node *pNextNode = pNode->m_pNextNode;
    delete pNode;
    pNode = pNextNode;
  }
  m_pFirstNode = 0;
}
