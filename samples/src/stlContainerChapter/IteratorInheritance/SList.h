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
  class ConstIterator {
  public:
    ConstIterator();

    ConstIterator &operator++();
    const ConstIterator operator++(int);

    const std::string *operator->() const;
    const std::string &operator*() const;

    friend bool operator==(const ConstIterator &lhs, const ConstIterator &rhs);
    friend bool operator!=(const ConstIterator &lhs, const ConstIterator &rhs);

  protected:
    // Protected since needs to be accessed for construction of derived classes
    explicit ConstIterator(const Node *);

  private:
    friend class SList;

    // No need to make protected: Avoids duplicate code by calling base class version. Small price
    // to pay: Function call overhead, which can be removed using inlining
    const Node *m_pNode;
  };

class Iterator : public ConstIterator {
  public:
    Iterator();

    Iterator &operator++();
    const Iterator operator++(int);

    std::string *operator->() const;
    std::string &operator*() const;
  
  private:
    friend class SList;

    explicit Iterator(Node *pNode);
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
