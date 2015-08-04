#include "BpTree.h"



////////////////////////////////////////////////////////////////////////
// Entry class
Entry::GarbageCollectionPool Entry::GCpool = Entry::GarbageCollectionPool();








////////////////////////////////////////////////////////////////////////
// Node class


Node::Node(BpTree * _tree) : Entry(CLASS_NODE) {
  pairs.clear();

  extra_entry = NULL; 

  parent = NULL;
  left_ptr = NULL;
  right_ptr = NULL;

  tree = _tree;
  tree->node_number += 1;
  // static member access
}


Node::Node(BpTree * _tree, int _key, Node * left, Node * right) : Entry(CLASS_NODE) { // only for making new root
  pairs.clear();

  pairs.push_back( make_pair(_key, (Entry *)left) );
  extra_entry = right;


  left->parent = this;
  right->parent = this;
  parent = NULL;

  left_ptr = NULL;
  right_ptr = NULL;

  right->becomeRightSibingOf(left);

  tree = _tree;
  tree->node_number += 1;
}

// Node::Node(const Node& _copy) {
  
//   parent      = _copy.parent;
//   left_ptr    = _copy.left_ptr;
//   right_ptr   = _copy.right_ptr;
//   extra_entry = _copy.extra_entry;

//   pairs       = _copy.pairs;

//   number += 1;
// }

Node::~Node() {
  tree->node_number -= 1;
}


Entry * Node::findChild(int _key) {
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if ( it->first > _key ) {
      return it->second;
    }
  }
  return extra_entry;
}

Entry * Node::findValueEntry(int _key) {
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if ( it->first == _key ) {
      return it->second;
    }
  }
  return NULL;
}

Entry * Node::findLeftMostChild() {
  if( pairs.size() > 0 )
    return pairs.front().second;
  else
    return NULL;
}

int Node::insert(int _key, Entry * _entry) {
  if ((int)pairs.size() < tree->key_num) {
    return forceInsert(_key, _entry);
  }
  else {
    return FULL; // full
  }
}


int Node::forceInsert(int _key, Entry * _entry) {
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if ( _key < it->first ) {
      pairs.insert(it, make_pair(_key, _entry));
      if ( !isLeaf() ) ((Node *) _entry)->parent = this;
      return SUCCESS;
    }
    else if (_key == it->first) {
      return SAME_KEY;
    } 
  }
  pairs.push_back( make_pair(_key, _entry) );
  if ( !isLeaf() ) ((Node *) _entry)->parent = this;
  return SUCCESS;
}


pair<int, Entry *> Node::split(int _key, Entry * _entry) {
  int insert_status = forceInsert(_key, _entry);
  if (insert_status == SAME_KEY) return pair<int, Entry *>(-1, NULL); // didn't insert anything

  // from: temp_left_ptr <---> this
  // to:   temp_left_ptr <---> left_node <---> this
  Node * left_node = new Node(tree);

  Node * temp_left_ptr = left_ptr;
  left_node->becomeRightSibingOf( temp_left_ptr );
  becomeRightSibingOf( left_node );

  int new_key;
  if (isLeaf()) {
    if (temp_left_ptr != NULL) temp_left_ptr->setNextLeaf(left_node);
    left_node->setNextLeaf( this );
    new_key = pairs[ (pairs.size()+1)/2 ].first;
  }
  else {
    new_key = pairs[ pairs.size()/2 ].first;
  }

  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if (it->first != new_key) {
      left_node->pairs.push_back( *it );
    }
    else {
      if ( !isLeaf() ) {
        left_node->extra_entry = (Node *)(it->second);
        it++;
      }
      pairs.erase(pairs.begin(), it);
      break;
    }
  }

  return make_pair(new_key, (Entry *)left_node);
}

bool Node::hasTooFewKeys() {

#ifdef DEBUG
  if( pairs.size() <= int( tree->key_num / 2 ) )
    cout << "Node::hasTooFewKeys() - Fewer than border key values" << endl;

  if( tree->isRoot(this) )
    cout << "Node::hasTooFewKeys() - Root Key" << endl;
#endif

  return ( pairs.size() <= int( tree->key_num / 2 ) && !tree->isRoot(this) );
}

bool Node::isSibling(Node * _left, Node * _right) {
    if( _left == NULL || _right == NULL) 
      return false;

#ifdef DEBUG
    cout << "_left->parent's 1st child key: " << _left->parent->pairs.front().first 
         << "_right->parent's 1st child key: " << _right->parent->pairs.front().first << endl;
    cout << "Node::isSibling - _left->parent == _right->parent " << ((_left->parent == _right->parent )?"True":"False") << endl;
#endif 
    
    return ( _left->parent == _right->parent );
}

bool Node::removeValueEntry(int _key) {
  auto it = pairs.begin();
  while(it != pairs.end())
  {
    if ( it->first == _key)
    {
      pairs.erase(it);
      return true;
    }
    it++;
  }

  // Note:
  // since we already introduced an external memory management tool 
  // for entries, set pointer to an unused entry is good enough, and 
  // may not cause issues like memory leak in the end of the program
  // execution
  
  return false;
}

int Node::remove(int _key) {

  if( removeValueEntry(_key) == false)
    return KEY_NOT_FOUND;
  
  if( hasTooFewKeys() )
    return TOO_FEW_KEYS;

  return SUCCESS;
}

bool Node::redistribute( Node * _left, Node * _right, bool right_to_left) {
  Node * distribute_from  = _left;
  Node * distribute_to    = _right;

  if( right_to_left ){ 
    distribute_from = _right; distribute_to = _left;
    
    auto entry = distribute_from->pairs.front();
    distribute_from->pairs.erase(distribute_from->pairs.begin());
    distribute_to->pairs.insert( distribute_to->pairs.end(), entry);
  }
  else {
    // Left to Right
    auto entry = distribute_from->pairs.back();
    distribute_from->pairs.erase(distribute_from->pairs.end());
    distribute_to->pairs.insert( distribute_to->pairs.begin(), entry);
  }
  
  return true;
}

bool Node::coalesce( Node * _left, Node * _right) {
  return true;
}









////////////////////////////////////////////////////////////////////////
// BpTree class


// Constructor
BpTree::BpTree(int _key_num) {
  node_number = 0;
  root = new Node(this);
  height = 1;
  key_num = _key_num;
}


// Copy constructor
BpTree::BpTree(const BpTree& _copy) {
  (*this) = _copy; // use operator =
}


// Deconstructor
BpTree::~BpTree() {
}


// Desired assignment overrides
BpTree& BpTree::operator =(const BpTree& _other) {
  root = _other.root;
  height = _other.height;
  key_num = _other.key_num;
  node_number = _other.node_number;
  return *this;
}


bool BpTree::insert(int _key, string& _value) {
  
  Node * current_node = root;
  while ( !current_node->isLeaf() ) {
    current_node = (Node *)current_node->findChild(_key);
  }

  int key = _key;
  Entry * entry = new Value(_value);
  int insert_status;
  while ( (insert_status = current_node->insert(key, entry)) == FULL ) {
    auto p = current_node->split(key, entry);
    if (p.second == NULL) break;
    key = p.first;
    entry = p.second;
    if (current_node->parent == NULL) {
      makeNewRoot(key, (Node *)entry, current_node);
      insert_status = SUCCESS;
      break;
    }
    else {
      current_node = current_node->parent;
    }
  }

  return ( insert_status == SUCCESS );
}


bool BpTree::remove(int _key) {
  
  Node * current_node = root;
  while( !current_node->isLeaf() ){
    current_node = (Node *) current_node->findChild(_key);
  }
  
  int delete_status = current_node->remove(_key); 

#ifdef DEBUG
      cout << "#############################################################" << endl; 
      cout << "BpTree::remove - Delete status: " << delete_status << endl;
#endif

  if( delete_status == KEY_NOT_FOUND) 
    // The case that there is no such key in the bpTree
    return false;
  else if( delete_status == TOO_FEW_KEYS) 
  {
#ifdef DEBUG
      cout << "BpTree::remove - Current Node has too few keys..." << endl;
#endif

    if( current_node->left_ptr != NULL                      && 
      Node::isSibling(current_node->left_ptr, current_node) && 
      !current_node->left_ptr->hasTooFewKeys() ){

#ifdef DEBUG
      cout << "BpTree::remove - Redistribute: from left sibling to right node..." << endl;
#endif
        // 1. Redistribute to left sibling
      Node::redistribute( current_node->left_ptr, current_node );
    }else if( current_node->right_ptr != NULL                &&
      Node::isSibling(current_node, current_node->right_ptr) && 
      !current_node->right_ptr->hasTooFewKeys()        ){
        // 2. Redistribute to right sibling
#ifdef DEBUG
      cout << "BpTree::remove - Redistribute: from right sibling to left node..." << endl;
#endif
      Node::redistribute( current_node, current_node->right_ptr, true );
    }else if( current_node->left_ptr != NULL                && 
      Node::isSibling(current_node->left_ptr, current_node) && 
      current_node->left_ptr->hasTooFewKeys()         ){
        // 3. Coalesce left sibling

#ifdef DEBUG
      cout << "BpTree::remove - Coalesce: left sibling and current node" << endl;
#endif

    }else if( current_node->right_ptr != NULL                 && 
      Node::isSibling(current_node, current_node->right_ptr)  && 
      current_node->right_ptr->hasTooFewKeys()          ){
        // 4. Coalesce right sibling

#ifdef DEBUG
      cout << "BpTree::remove - Coalesce: current node and right sibling" << endl;
#endif
    }else {

    }

  }


  return ( delete_status == SUCCESS );
}


string BpTree::find(int _key) {
  Node * current_node = root;
  while ( !current_node->isLeaf() ) {
    current_node = (Node *)current_node->findChild(_key);
  }
  Entry * valueEntry = current_node->findValueEntry(_key);
  if (valueEntry == NULL) {
    return string("");
  }
  else {
    return ((Value *)valueEntry)->getValue();
  }
}


void BpTree::printKeys() {
  queue< pair<int, Node *> > que;
  que.push( make_pair(1, root) ); 
  int cur_level = 1;
  while ( !que.empty() ) {
    auto cur = que.front();
    que.pop();
    if ( !cur.second->isLeaf() ) {
      for (auto it = cur.second->pairs.begin(); it != cur.second->pairs.end(); it++) { 
        que.push( make_pair(cur.first + 1, (Node *)it->second) );
      }
      que.push( make_pair(cur.first + 1, (Node *)cur.second->extra_entry) );
    }
    if (cur.first > cur_level) {
      printf("\n");
      cur_level = cur.first;
    }
    cur.second->printKeys();
  }
  printf("\n");
}


void BpTree::printValues() {
  // Find leftmost key and print out values for the bpTree
  Node * current_node = root;
  while ( !current_node->isLeaf() ) {
    current_node = (Node *)current_node->findLeftMostChild();
  }

  // Iterate the leaf level tree nodes
  do{
    current_node->printValues();
    current_node = current_node->extra_entry;
  }
  while ( current_node );

  printf("\n");  
}

