#include "SList1.h"
#include "SList2.h"
#include "SList3.h"

#include "List4.h"

#include <iostream>

template<class T>
void testSList()
{
  T list;

  list.push_front("Alice");
  list.push_front("Bob");
  list.push_front("Copernicus");
  
  for (typename T::ConstIterator cit = list.begin(); cit != list.end(); ++cit) {
    std::cout << *cit << std::endl;
  }
  std::cout << std::endl;

  for (typename T::Iterator it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  typedef List4<std::string> SList4;

  testSList<SList1>();
  testSList<SList2>();
  testSList<SList3>();
  testSList<SList4>();
}
