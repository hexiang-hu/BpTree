#include "BpTree.h"


int main() {
  BpTree bptree(3);
  string str = "AAA";

  printf("########################\n"); bptree.printKeys();
  bptree.insert(2, str);
  bptree.insert(21, str);
  bptree.insert(11, str);
  bptree.insert(8, str);
  printf("2, 21, 11, 8 ########################\n"); bptree.printKeys();
  bptree.insert(64, str);
  bptree.insert(5, str);
  printf("64, 5 ########################\n"); bptree.printKeys();
  bptree.insert(23, str);
  printf("23 ########################\n"); bptree.printKeys();
  bptree.insert(6, str);
  printf("6, ########################\n"); bptree.printKeys();
  bptree.insert(19, str);
  bptree.insert(9, str);
  printf("19, 9, ########################\n"); bptree.printKeys();
  bptree.insert(7, str);
  printf("7, ########################\n"); bptree.printKeys();

  return 0;
}