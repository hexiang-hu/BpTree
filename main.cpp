#include "BpTree.h"

#include <time.h>

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
  bptree.insert(5, str[2]);
  printf("################ insert 19, 9, 5(duplicated) ########################\n"); bptree.printKeys();
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


  /////////////////////////

  int key_num = 50;
  int node_number = 50*50*50;

  BpTree bptree2(key_num);
  srand (time(NULL));
  for (int i=0; i<node_number; i++) {
    bptree2.insert(rand() % (node_number * 2), str[ rand() % 11 ]);
  }

  printf("\n\n\n\n################ Huge tree ########################\n");
  bptree2.printKeys();

  return 0;
}