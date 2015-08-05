#include "BpTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>

#define CASE_NUM_0 0x00000001
#define CASE_NUM_1 0x00000002
#define CASE_NUM_2 0x00000004
#define CASE_NUM_3 0x00000008


int main(int argc, const char * argv[]) {

  int tCaseNum = -1;

  if( argc > 1){
    switch ( atoi((const char *) argv[1]) )
    {
      case 0:
        tCaseNum = (CASE_NUM_0);
        break;
      case 1:
        tCaseNum = (CASE_NUM_1);
        break;
      case 2:
        tCaseNum = (CASE_NUM_2);
        break;
      case 3:
        tCaseNum = (CASE_NUM_3);
        break;      
      case 4:
        tCaseNum = (CASE_NUM_0 | CASE_NUM_1 | CASE_NUM_2 | CASE_NUM_3);
        break;
      default:
        break;
    } 

    printf("Specified Test Cases: \n");
    printf("- Case 0: %s\n", (((tCaseNum & CASE_NUM_0) != 0)?"On":"Off") );
    printf("- Case 1: %s\n", (((tCaseNum & CASE_NUM_1) != 0)?"On":"Off") );
    printf("- Case 2: %s\n", (((tCaseNum & CASE_NUM_2) != 0)?"On":"Off") );
    printf("- Case 3: %s\n", (((tCaseNum & CASE_NUM_3) != 0)?"On":"Off") );
  }
  else {
    printf("[Usage] testRun.out [case number]\n");
    printf("- [case 0] Test regular BpTree\n");
    printf("- [case 1] Test huge BpTree\n");
    printf("- [case 2] Test delete BpTree\n");
    printf("- [case 3] Test insert/delete BpTree\n");
    printf("- [case 4] Test all BpTree\n");
    return 0;
  }

  /////////////////////////TEST CASE 1
  BpTree bptree(3);
  map<int, string> key_val_map;
  key_val_map[2]  = string("A");
  key_val_map[21] = string("B");
  key_val_map[11] = string("C");
  key_val_map[8]  = string("D");
  key_val_map[64] = string("E");
  key_val_map[5]  = string("F");
  key_val_map[23] = string("G");
  key_val_map[6]  = string("H");
  key_val_map[19] = string("I");
  key_val_map[9]  = string("J");
  key_val_map[7]  = string("K");
  key_val_map[31] = string("L");
  key_val_map[39] = string("M");
  key_val_map[45] = string("N");
  key_val_map[51] = string("O");
  key_val_map[60] = string("P");
  key_val_map[93] = string("Q");
  key_val_map[77] = string("R");




  if(tCaseNum & CASE_NUM_0) {

    printf("#############################################################\n"); 

    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.insert(2, key_val_map[2]);
    bptree.insert(21, key_val_map[21]);
    bptree.insert(11, key_val_map[11]);
    bptree.insert(8, key_val_map[8]);
    
    printf("################ insert 2, 21, 11, 8 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.insert(64, key_val_map[64]);
    bptree.insert(5, key_val_map[5]);
    printf("################ insert 64, 5 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(23, key_val_map[23]);
    printf("################ insert 23 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(6, key_val_map[6]);
    printf("################ insert 6 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
    
    bptree.insert(19, key_val_map[19]);
    bptree.insert(9, key_val_map[9]);
    bptree.insert(5, key_val_map[5]);
    printf("################ insert 19, 9, 5(duplicated) ########################\n"); bptree.printKeys();
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.insert(7, key_val_map[7]);
    printf("################ insert 7 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();


    bptree.insert(31, key_val_map[31]);
    bptree.insert(45, key_val_map[45]);
    bptree.insert(51, key_val_map[51]);
    bptree.insert(60, key_val_map[60]);
    bptree.insert(93, key_val_map[93]);
    bptree.insert(39, key_val_map[39]);
    bptree.insert(77, key_val_map[77]);

    printf("################ insert MORE to test delete ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();


    bptree.remove(19);
    bptree.remove(45);
    printf("################ delete 19, 45 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();


    bptree.remove(9);
    printf("################ delete 9 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(6);
    printf("################ delete 6 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(8);
    printf("################ delete 8 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(23);
    printf("################ delete 23 ########################\n"); 
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

  if(tCaseNum & CASE_NUM_1) {
    int key_num = 50;
    int node_number = 50*50*50;

    BpTree bptree2(key_num);
    srand (time(NULL));
    for (int i=0; i<node_number; i++) {
      bptree2.insert(rand() % (node_number * 2), key_val_map[ 2 ]);
    }

    printf("\n\n\n\n################ Huge tree ########################\n");
    bptree2.printKeys();
  }

  if(tCaseNum & CASE_NUM_2) {
    bptree.insert(2, key_val_map[2]);
    bptree.insert(21, key_val_map[21]);
    bptree.insert(11, key_val_map[11]);
    bptree.insert(8, key_val_map[8]);
    bptree.insert(64, key_val_map[64]);
    bptree.insert(5, key_val_map[5]);
    bptree.insert(23, key_val_map[23]);
    bptree.insert(6, key_val_map[6]);
    bptree.insert(19, key_val_map[19]);
    bptree.insert(9, key_val_map[9]);
    bptree.insert(5, key_val_map[5]);
    bptree.insert(7, key_val_map[7]);
    bptree.insert(31, key_val_map[31]);
    bptree.insert(45, key_val_map[45]);
    bptree.insert(51, key_val_map[51]);
    bptree.insert(60, key_val_map[60]);
    bptree.insert(93, key_val_map[93]);
    bptree.insert(39, key_val_map[39]);
    bptree.insert(77, key_val_map[77]);

    printf("################ Initialized Tree ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(2);
    bptree.remove(5);
    bptree.remove(8);
    printf("################ Deletes 2, 5, 8, 60 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(60);
    printf("################ Deletes 60 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(77);
    bptree.remove(39);
    printf("################ Deletes 77, 39 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(45);
    bptree.remove(64);
    printf("################ Deletes 45, 64 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(51);
    printf("################ Deletes 51 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.insert(31, key_val_map[31]);
    bptree.insert(45, key_val_map[45]);
    bptree.insert(51, key_val_map[51]);
    bptree.insert(60, key_val_map[60]);
    bptree.insert(93, key_val_map[93]);
    bptree.insert(39, key_val_map[39]);
    bptree.insert(77, key_val_map[77]);

    printf("################ Add some entry again (31, 45, 51, 60, 93, 29, 77) ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(51);
    bptree.remove(60);
    bptree.remove(93);

    printf("################ Then remove again (51, 60, 93) ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
  }


  if(tCaseNum & CASE_NUM_3) {

    bptree.insert(2, key_val_map[2]);
    bptree.insert(21, key_val_map[21]);
    bptree.insert(11, key_val_map[11]);
    bptree.insert(8, key_val_map[8]);
    bptree.insert(64, key_val_map[64]);
    bptree.insert(5, key_val_map[5]);
    bptree.insert(23, key_val_map[23]);
    bptree.insert(6, key_val_map[6]);
    bptree.insert(19, key_val_map[19]);
    bptree.insert(9, key_val_map[9]);
    bptree.insert(5, key_val_map[5]); // duplicated insert, should return false and didn't insert
    bptree.insert(7, key_val_map[7]);
    bptree.insert(31, key_val_map[31]);
    bptree.insert(45, key_val_map[45]);
    bptree.insert(51, key_val_map[51]);
    bptree.insert(60, key_val_map[60]);
    bptree.insert(93, key_val_map[93]);
    bptree.insert(39, key_val_map[39]);
    bptree.insert(77, key_val_map[77]);

    printf("################ All Inserts ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(2);
    printf("################ Deletes 2 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(21);
    printf("################ Deletes 21 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(11);
    printf("################ Deletes 11 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(8);
    printf("################ Deletes 8 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(64);
    printf("################ Deletes 64 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(5);
    printf("################ Deletes 5 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(23);
    printf("################ Deletes 23 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(6);
    printf("################ Deletes 6 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(19);    
    printf("################ Deletes 19 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(9);
    printf("################ Deletes 9 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(7);
    printf("################ Deletes 7 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(31);
    printf("################ Deletes 31 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(45);
    printf("################ Deletes 45 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();    

    bptree.remove(51);

    printf("################ Deletes 51 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(60);
    printf("################ Deletes 60 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(93);
    printf("################ Deletes 93 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(39);
    printf("################ Deletes 39 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();

    bptree.remove(77);
    printf("################ Deletes 77 ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();


    bptree.insert(2, key_val_map[2]);
    bptree.insert(21, key_val_map[21]);
    bptree.insert(11, key_val_map[11]);
    bptree.insert(8, key_val_map[8]);
    bptree.insert(64, key_val_map[64]);
    bptree.insert(5, key_val_map[5]);
    bptree.insert(23, key_val_map[23]);
    bptree.insert(6, key_val_map[6]);
    bptree.insert(19, key_val_map[19]);
    bptree.insert(9, key_val_map[9]);
    bptree.insert(5, key_val_map[5]);
    bptree.insert(7, key_val_map[7]);
    bptree.insert(31, key_val_map[31]);
    bptree.insert(45, key_val_map[45]);
    bptree.insert(51, key_val_map[51]);
    bptree.insert(60, key_val_map[60]);
    bptree.insert(93, key_val_map[93]);
    bptree.insert(39, key_val_map[39]);
    bptree.insert(77, key_val_map[77]);

    printf("################ All Inserts again ########################\n"); 
    printf("=> Key Tree:\n");bptree.printKeys();
    printf("=> Value Tree:\n");bptree.printValues();
  }

  for (auto it = key_val_map.begin(); it != key_val_map.end(); ++it)
  {
    printf("key: %d, value: %s\n", it->first, it->second.c_str());
  }

  return 0;
}