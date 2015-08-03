#ifndef BPTREE_H
#define BPTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <queue>
#include <set>

#define SUCCESS       0
#define UNKNOWN_ERROR 1
#define FULL          2
#define SAME_KEY      3
#define KEY_NOT_FOUND 4
#define TOO_FEW_KEYS  5

#define CLASS_VALUE   1
#define CLASS_NODE    2



using namespace std;



class Entry {
private:
  class GarbageCollectionPool {
  private:
    set<Entry *> pool;
    bool is_accessable;
  public:
    GarbageCollectionPool() {
      is_accessable = true;
    };
    ~GarbageCollectionPool() {
      is_accessable = false;
      for (auto it = pool.begin(); it != pool.end(); it++) {
        delete *it;
      }
    }

    void insert(Entry * e) {
      if (is_accessable) pool.insert(e);
    }
    void erase(Entry * e) {
      if (is_accessable) pool.erase(e);
    }

  };
<<<<<<< HEAD
  static GarbageCollectionPool GC;
=======
  static GarbageCollectionPool GCpool;
>>>>>>> 3991e37... Modify GCPool to adapt local Entry variable

  int type;

public:
  Entry(int _type) { 
    // Type=1 is Value, Type=2 is Node
    type = _type;
<<<<<<< HEAD
    GC.pool.push_back(this);
=======
    GCpool.insert(this);
  }
  virtual ~Entry() {
    GCpool.erase(this);
>>>>>>> 3991e37... Modify GCPool to adapt local Entry variable
  }
  virtual ~Entry() {}
  int getType() {
    return type;
  }
};


class Value: public Entry {
private:
  string value;
public:
  Value(string _value): Entry(CLASS_VALUE) {
    value = _value;
  }
  string getValue() {
    return value;
  }
};


class BpTree;


class Node: public Entry {

public:

  vector< pair<int, Entry *> > pairs;

  // Note:
  //   If it is a leaf node, extra_entry is the pointer to next leaf node 
  //   If it is an interior node, extra_entry is the right most entry
  Node * extra_entry;    

  // The following 3 attributes are for the sake of easier implementaion in insert() and remove()
  // Those should not be implemented with shared_ptr
  // John recommends to store this value
  Node * parent;    

  BpTree * tree;

  // Louis recommends to store this value
  Node * left_sib;  

  // Louis recommends to store this value, the same as extra_entry when this node is a leaf node
  Node * right_sib; 

  // Constructor
  Node(BpTree * _tree);
  // only for making new root
  Node(BpTree * _tree, int _key, Node * left, Node * right);
  
  // Deconstructor
  ~Node();

  int insert(int _key, Entry * _entry);
  int forceInsert(int _key, Entry * _entry);
  pair<int, Entry *> split(int _key, Entry * _entry);

  Entry * findChild(int _key);
  Entry * findValueEntry(int _key);
  Entry * findLeftMostChild();
  
  bool removeValueEntry(int _key);
  int  remove(int _key);
  
  pair<int, Entry *> coalesce( Node * _sibling);
  int redistribute(Node * _sibling);

  bool isLeaf() {
    return (pairs.size() == 0) || (pairs[0].second->getType() == CLASS_VALUE);
  }

  Node * getNextLeaf() {
    return extra_entry;
  }
  
  void setNextLeaf(Node * _next_leaf) {
    extra_entry = _next_leaf;
  }

  void becomeRightSibingOf(Node * _left) {
    if (_left != NULL) _left->right_sib = this;
    this->left_sib = _left;
  }

  void printKeys() {
    printf("[");
    for (auto it = pairs.begin(); it != pairs.end(); it++) {
      if (it == pairs.begin()) printf("%d", it->first);
      else printf(",%d", it->first);
    }
    printf("] ");
  }

  void printValues() {
    printf("[");
    for (auto it = pairs.begin(); it != pairs.end(); it++) {
      if (it == pairs.begin()) 
        printf("%s", ((Value *)it->second)->getValue().c_str() );
      else 
        printf(",%s", ((Value *)it->second)->getValue().c_str() );
    }
    printf("] ");
  }
};




class BpTree {
private:
  Node * root;
  int height;

  void makeNewRoot(int _key, Node * _left, Node * _right) {
    root = new Node(this, _key, _left, _right);
    height += 1;
  }

public:

  int node_number;
  int key_num;

  // Constructor
  BpTree(int _key_num);
  // Copy constructor
  BpTree(const BpTree& _copy);
  
  // Deconstructor
  ~BpTree();

  // Desired assignment overrides
  BpTree& operator =(const BpTree& _other);

  // Desired interfaces for BpTree
  bool insert(int _key, string& _value);
  bool remove(int _key);
  string find(int _key);
  void printKeys();
  void printValues();

};


#endif 
// BPTREE_H
