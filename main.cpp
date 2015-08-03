#include "BpTree.h"


int main() {
  BpTree bptree(3);
  string str[11] = {  string("AAA"), 
                      string("BBB"), 
                      string("CCC"),
                      string("DD DD"),
                      string("EEEE"),
                      string("FFF"),
                      string("G"),
                      string("HHHHHA"),
                      string("~@#$"),
                      string("123"),
                      string(";;;")  };

  printf("###############################################\n"); bptree.printKeys();
  bptree.insert(2, str[0]);
  bptree.insert(21, str[1]);
  bptree.insert(11, str[2]);
  bptree.insert(8, str[3]);
  printf("################ insert 2, 21, 11, 8 ########################\n"); bptree.printKeys();
  bptree.insert(64, str[4]);
  bptree.insert(5, str[5]);
  printf("################ insert 64, 5 ########################\n"); bptree.printKeys();
  bptree.insert(23, str[6]);
  printf("################ insert 23 ########################\n"); bptree.printKeys();
  bptree.insert(6, str[7]);
  printf("################ insert 6 ########################\n"); bptree.printKeys();
  bptree.insert(19, str[8]);
  bptree.insert(9, str[9]);
  printf("################ insert 19, 9 ########################\n"); bptree.printKeys();
  bptree.insert(7, str[10]);
  printf("################ insert 7 ########################\n"); bptree.printKeys();


  printf("\n");
  string value = bptree.find(23);
  printf("find(23)=\"%s\"\n", value.c_str());
  value = bptree.find(8);
  printf("find(8)=\"%s\"\n", value.c_str()); 
  value = bptree.find(7);
  printf("find(7)=\"%s\"\n", value.c_str()); 
  value = bptree.find(11);
  printf("find(11)=\"%s\"\n", value.c_str()); 

  return 0;
}