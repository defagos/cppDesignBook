#include "List.h"

#include <iostream>
#include <string>

void testNonStdList()
{
  typedef List<std::string> SList;

  SList list;

  list.push_front("Alice");
  list.push_front("Bob");
  list.push_front("Copernicus");
  
  for (SList::ConstIterator cit = list.begin(); cit != list.end(); ++cit) {
    std::cout << *cit << std::endl;
  }
  std::cout << std::endl;

  for (SList::Iterator it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  testNonStdList();
}
