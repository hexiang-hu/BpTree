#ifndef BPTREE_H
#define BPTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {

public:
  // Constructor
  Node(int _key_num){
  }
  // Copy Constructor
  Node(const Node& _copy){
  }
  // Deconstructor
  ~Node(){
  }

};

class BpTree {
private:
  int key_num;
public:
  // Constructor
  BpTree(int _key_num):key_num(_key_num){ }
  // Copy constructor
  BpTree(const BpTree& _copy){
  }
  // Deconstructor
  ~BpTree(){ 
  }

  // Desired assignment overrides
  void operator =(BpTree&);

  // Desired interfaces for BpTree
  bool insert(int _key, string& _val);
  bool remove(int _key);
  bool find(int _key);
  void printKeys();
  void printValues();

};


#endif 
// BPTREE_H
