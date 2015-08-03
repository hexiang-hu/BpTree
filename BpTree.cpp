#include "BpTree.h"




////////////////////////////////////////////////////////////////////////
// Node class


unsigned int Node::number  = 0;
unsigned int Node::key_num = 0;

Node::Node() : Entry(CLASS_NODE) {
  pairs.clear();

  extra_entry = NULL; 

  parent = NULL;
  left_sib = NULL
  right_sib = NULL;

  number += 1; // static member access
}


Node::Node(int _key, Node * left, Node * right) : Entry(CLASS_NODE) { // only for making new root
  pairs.clear();

  pairs.push_back( make_pair(_key, (Entry *)left) );
  extra_entry = right;


  left->parent = this;
  right->parent = this;
  parent = NULL;

  left_sib = NULL;
  right_sib = NULL;

  right->becomeRightSibingOf(left);

  number += 1;
}


Node::~Node() {
  number -= 1;
}


Entry * Node::findChild(int _key) {
  auto it = pairs.begin();
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if ( (*it).first > _key ) {
      return (*it)->second;
    }
  }
  return extra_entry;
}


int Node::insert(int _key, Entry * _entry) {
  if ((int)pairs.size() + 1 < key_num) {
    return forceInsert(_key, _entry);
  }
  else {
    return FULL; // full
  }
}


int Node::forceInsert(int _key, Entry * _entry) {
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if ( _key < (*it).first ) {
      pairs.insert(it, make_pair(_key, _entry))
      if ( !isLeaf() ) ((Node *) _entry)->parent = this;
      return SUCCESS;
    }
    else if (_key == (*it).first) {
      return SAME_KEY;
    } 
  }
  pairs.push_back( make_pair(_key, _entry) );
  if ( !isLeaf() ) ((Node *) _entry)->parent = this;
  return SUCCESS;
}


pair<int, Entry *> Node::split(int _key, Entry * _entry) {
  int insert_status = forceInsert(_key, _entry);
  if (insert_status == SAME_KEY) return NULL; // didn't insert anything

  // from: temp_left_sib <---> this
  // to:   temp_left_sib <---> left_node <---> this
  Node * left_node = new Node();

  Node * temp_left_sib = left_sib;
  left_node->becomeRightSibingOf( temp_left_sib );
  becomeRightSibingOf( left_node );

  int new_key;
  if (isLeaf()) {
    if (temp_left_sib != NULL) temp_left_sib->setNextLeaf(left_node);
    left_node.setNextLeaf( getNextLeaf() );
    new_key = pairs[ (pairs.size()+1)/2 ].first;
  }
  else {
    new_key = pairs[ pairs.size()/2 ].first;
  }


  for (auto it = pairs.begin(); it != left; it++) {
    if (*it != new_key) {
      left_node->pairs.push_back( *it );
      if ( !isLeaf() ) (*it).second->parent = left_node;
    }
    else {
      if ( !isLeaf() ) left_node->extra_entry = (*it).second;
      pairs.erase(pairs.begin(), it);
    }
  }

  return make_pair(new_key, (Entry *)left_node);
}

// int Node::getHeight() {
//   int height = 0;
//   Node * current_node = this;
//   while ( current_node->parent != NULL ) {
//     current_node = current_node->parent;
//   }
//   return height;
// }














////////////////////////////////////////////////////////////////////////
// BpTree class


// Constructor
BpTree::BpTree(int _key_num) {
  Node::key_num = _key_num;
  root = new Node();
}


// Copy constructor
BpTree::BpTree(const BpTree& _copy) {
  root = _copy.root;
}


// Deconstructor
BpTree::~BpTree() {
}



void BpTree::makeNewRoot(int _key, Node * left, Node * right) {
  root = new Node(_key, left, right);
}


// Desired assignment overrides
void BpTree::operator =(BpTree&) {
  root = _copy.root;
}


bool BpTree::insert(int _key, string& _value) {
  
  Node * current_node = root;
  while ( !current_node.isLeaf() ) {
    current_node = (Node *)current_node->findChild(_key);
  }

  int key = _key;
  Entry * entry = new Value(_value);
  while ( current_node->insert(_key, entry) == FULL ) {
    auto p = current_node->split(_key, entry);
    key = p.first;
    entry = p.second;
    if (current_node->parent == NULL) {
      makeNewRoot(key, p.second, current_node);
      break;
    }
  }

}


bool BpTree::remove(int _key) {}
string BpTree::find(int _key) {}
void BpTree::printKeys() {}
void BpTree::printValues() {}

