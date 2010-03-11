#include "SList1.h"

#include <iostream>

int main(int argc, char *argv[])
{
  SList1 list1;
  list1.push_front("Alice");
  list1.push_front("Bob");
  list1.push_front("Copernicus");
  for (SList1::ConstIterator cit = list1.begin(); cit != list1.end(); ++cit) {
    std::cout << *cit << std::endl;
  }
}
