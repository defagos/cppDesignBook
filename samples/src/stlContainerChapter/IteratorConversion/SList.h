/**
 * Implementation of a list holding standard strings
 *   - only std::string objects are stored
 *   - no inlining is performed at all
 */

#ifndef SLIST_H
#define SLIST_H

#include <string>

class SList {
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

#endif
