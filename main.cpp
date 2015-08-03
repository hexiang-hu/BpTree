#include "BpTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>

#define CASE_NUM_1 0x00000001
#define CASE_NUM_2 0x00000002


int main(int argc, const char * argv[]) {

  int tCaseNum = -1;

  if( argc > 1){
    switch ( atoi((const char *) argv[1]) )
    {
      case 0:
        tCaseNum = (CASE_NUM_1);
        break;
      case 1:
        tCaseNum = (CASE_NUM_2);
        break;
      case 2:
        tCaseNum = (CASE_NUM_1 | CASE_NUM_2);
        break;
      default:
        break;
    } 

    printf("Specified Test Cases: \n");
    printf("- Case 0: %s\n", (((tCaseNum & CASE_NUM_1) != 0)?"On":"Off") );
    printf("- Case 1: %s\n", (((tCaseNum & CASE_NUM_2) != 0)?"On":"Off") );

  }
  else {
    printf("[Usage] testRun.out [case number]\n");
    printf("- [case 0] Test regular BpTree\n");
    printf("- [case 1] Test huge BpTree\n");
    printf("- [case 2] Test all BpTree\n");
    return 0;
  }

  /////////////////////////TEST CASE 1
  BpTree bptree(3);
  map<int, string> str;
  str[2]  = string("A");
  str[21] = string("B");
  str[11] = string("C");
  str[8]  = string("D");
  str[64] = string("E");
  str[5]  = string("F");
  str[23] = string("G");
  str[6]  = string("H");
  str[19] = string("I");
  str[9]  = string("J");
  str[7]  = string("K");

  if(tCaseNum & CASE_NUM_1) {

    printf("###############################################\n"); 

    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.insert(2, str[0]);
    bptree.insert(21, str[1]);
    bptree.insert(11, str[2]);
    bptree.insert(8, str[3]);
    
    printf("################ insert 2, 21, 11, 8 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.insert(64, str[4]);
    bptree.insert(5, str[5]);
    printf("################ insert 64, 5 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(23, str[6]);
    printf("################ insert 23 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(6, str[7]);
    printf("################ insert 6 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(19, str[8]);
    bptree.insert(9, str[9]);
    bptree.insert(5, str[2]);
    printf("################ insert 19, 9, 5(duplicated) ########################\n"); bptree.printKeys();
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(7, str[10]);
    printf("################ insert 7 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();


    printf("\n");
    string value = bptree.find(23);
    printf("find(23)=\"%s\"\n", value.c_str());
    value = bptree.find(8);
    printf("find(8)=\"%s\"\n", value.c_str()); 
    value = bptree.find(7);
    printf("find(7)=\"%s\"\n", value.c_str()); 
    value = bptree.find(11);
    printf("find(11)=\"%s\"\n", value.c_str()); 

  }


  /////////////////////////TEST CASE 2

  if(tCaseNum & CASE_NUM_2) {
    int key_num = 50;
    int node_number = 50*50*50;

    BpTree bptree2(key_num);
    srand (time(NULL));
    for (int i=0; i<node_number; i++) {
      bptree2.insert(rand() % (node_number * 2), str[ rand() % 11 ]);
    }

    printf("\n\n\n\n################ Huge tree ########################\n");
    bptree2.printKeys();
  }

  return 0;
}