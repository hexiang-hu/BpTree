#ifndef BPTREE_H
#define BPTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
  int * pKeys;
  (Node *) * pNodes;
public:
  // Constructor
  Node(int _key_num){
    pKeys  = new int(_key_num);
    pNodes = new (Node *)(_key_num + 1);
  }
  // Copy Constructor
  Node(const Node& _copy){
    pKeys  = new int( *(_copy.pKeys) );
    pNodes = new (Node *)(*(_copy.pNodes) );
  }
  // Deconstructor
  ~Node(){
    delete pKeys;
    delete pNodes;
  }

};

class BpTree {
private:
  Node * pRoot;
  int key_num;
public:
  // Constructor
  BpTree(int _key_num):key_num(_key_num){ }
  // Copy constructor
  BpTree(const BpTree& _copy){
    key_num = _copy.key_num;
    pRoot   = new Node( *(_copy.pRoot) );
  }
  // Deconstructor
  ~BpTree(){ 
    // First traversal the B+ tree and delete all the nodes

    // delete pRoot;
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