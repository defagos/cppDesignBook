#include "SList.h"

#include <cassert>

struct SList::Node {
  Node(const std::string &value, Node *pNextNode);

  std::string m_value;
  Node *m_pNextNode;
};

inline SList::Node::Node(const std::string &value, Node *pNextNode)
: m_value(value),
  m_pNextNode(pNextNode)
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

SList::Iterator &SList::Iterator::operator++()
{
  m_pNode = m_pNode->m_pNextNode;
  return *this;
}

const SList::Iterator SList::Iterator::operator++(int)
{
  Iterator tmp(*this);
  m_pNode = m_pNode->m_pNextNode;
  return tmp;
}

std::string *SList::Iterator::operator->() const
{
  return &m_pNode->m_value;
}

std::string &SList::Iterator::operator*() const
{
  return m_pNode->m_value;
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
