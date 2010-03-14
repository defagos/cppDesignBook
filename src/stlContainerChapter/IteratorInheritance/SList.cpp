#include "SList.h"

#include <cassert>

struct SList::Node {
  Node(const std::string &value, Node *pNextNode);

  std::string m_value;
  Node *m_pNextNode;
};

SList::Node::Node(const std::string &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
{}

SList::ConstIterator::ConstIterator()
: m_pNode(0)
{}

SList::ConstIterator &SList::ConstIterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

const SList::ConstIterator SList::ConstIterator::operator++(int)
{
  ConstIterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

const std::string *SList::ConstIterator::operator->() const
{
  return &m_pNode->m_value;
}

const std::string &SList::ConstIterator::operator*() const
{
  return m_pNode->m_value;
}

bool operator==(const SList::ConstIterator &lhs, const SList::ConstIterator &rhs)
{
  return lhs.m_pNode == rhs.m_pNode;
}

bool operator!=(const SList::ConstIterator &lhs, const SList::ConstIterator &rhs)
{
  return lhs.m_pNode != rhs.m_pNode;
}

SList::ConstIterator::ConstIterator(const Node *pNode)
: m_pNode(pNode)
{}

SList::Iterator::Iterator()
{}

SList::Iterator &SList::Iterator::operator++()
{
  ConstIterator::operator++();
  return *this;
}

const SList::Iterator SList::Iterator::operator++(int)
{
  Iterator tmp(*this);
  // Call post-increment version
  ConstIterator::operator++(0);
  return tmp;
}

std::string *SList::Iterator::operator->() const
{
  // Need to cast constness away here, the price to pay for using inheritance
  return const_cast<std::string *>(ConstIterator::operator->());
}

std::string &SList::Iterator::operator*() const
{
  // Need to cast constness away here, the price to pay for using inheritance
  return const_cast<std::string &>(ConstIterator::operator*());
}

SList::Iterator::Iterator(Node *pNode)
: ConstIterator(pNode)
{}

SList::SList()
: m_pFirstNode(0)
{}

SList::SList(const SList &rhs)
: m_pFirstNode(0)
{
  createFrom(rhs);
}

SList &SList::operator=(const SList &rhs)
{
  // Check for self-assignment
  if (this != &rhs) {
    release();
    createFrom(rhs);
  }
  return *this;
}

SList::~SList()
{
  release();
}

SList::ConstIterator SList::begin() const
{
  return ConstIterator(m_pFirstNode);
}

SList::Iterator SList::begin()
{
  return Iterator(m_pFirstNode);
}

SList::ConstIterator SList::end() const
{
  return ConstIterator(0);
}

SList::Iterator SList::end()
{
  return Iterator(0);
}

void SList::push_front(const std::string &value)
{
  Node *pNode = new Node(value, m_pFirstNode);
  m_pFirstNode = pNode;
}

/**
 * Function factoring out the code for creating a list from an existing one. Must
 * be called only on an empty list
 */
void SList::createFrom(const SList &rhs)
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
void SList::release()
{
  Node *pNode = m_pFirstNode;
  while (pNode) {
    Node *pNextNode = pNode->m_pNextNode;
    delete pNode;
    pNode = pNextNode;
  }
  m_pFirstNode = 0;
}
