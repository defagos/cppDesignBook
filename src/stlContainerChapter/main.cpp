#include "SList1.h"
#include "SList2.h"
#include "SList3.h"

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
}

int main(int argc, char *argv[])
{
  testSList<SList1>();
  testSList<SList2>();
  testSList<SList3>();
}
