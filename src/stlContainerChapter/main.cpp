#include "SList0.h"
#include "SList1.h"
#include "SList2.h"
#include "SList3.h"

#include "List4.h"
#include "List5.h"
#include "List6.h"
#include "List7.h"

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

template<class T>
void testStdSList()
{
  T list;

  list.push_front("Alice");
  list.push_front("Bob");
  list.push_front("Copernicus");
  
  for (typename T::const_iterator cit = list.begin(); cit != list.end(); ++cit) {
    std::cout << *cit << std::endl;
  }
  std::cout << std::endl;

  for (typename T::iterator it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  typedef List4<std::string> SList4;
  typedef List5<std::string> SList5;
  typedef List6<std::string> SList6;
  typedef List7<std::string> SList7;

  testSList<SList0>();
  testSList<SList1>();
  testSList<SList2>();
  testSList<SList3>();
  testSList<SList4>();
  testSList<SList5>();
  testStdSList<SList6>();
  testStdSList<SList7>();
}
