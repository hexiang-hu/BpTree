#include "BpTree.h"



////////////////////////////////////////////////////////////////////////
// Entry class
Entry::GarbageCollectionPool Entry::GCpool = Entry::GarbageCollectionPool();
#ifdef DEBUG
int Entry::global_id_counter = 1;
#endif







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

Node::~Node() {}

bool Node::isLeaf() {
  return ( tree->node_number == 1 ) || (pairs[0].second->getType() == CLASS_VALUE);
}

void Node::setNextLeaf(Node * _next_leaf) {
  extra_entry = _next_leaf;
}

void Node::becomeRightSibingOf(Node * _left) {
  if (_left != NULL) _left->right_ptr = this;
  this->left_ptr = _left;
}

Node * Node::getNextLeaf() {
  return extra_entry;
}

void Node::printKeys() {

#ifdef DEBUG
  printf("%d,%d,", id, parent == NULL ? 0 : parent->id);
#endif

  printf("[");
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if (it == pairs.begin()) printf("%d", it->first);
    else printf(",%d", it->first);
  }
  printf("] ");
}

void Node::printValues() {
  printf("[");
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if (it == pairs.begin()) 
      printf("%s", ((Value *)it->second)->getValue().c_str() );
    else 
      printf(",%s", ((Value *)it->second)->getValue().c_str() );
  }
  printf("] ");
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
      if ( !isLeaf() ) ((Node *)it->second)->parent = left_node;
    }
    else {
      if ( !isLeaf() ) {
        left_node->extra_entry = (Node *)(it->second);
        left_node->extra_entry->parent = left_node;
        it++;
      }
      pairs.erase(pairs.begin(), it);
      break;
    }
  }

  return make_pair(new_key, (Entry *)left_node);
}

int Node::numOfEntries() {
  if( isLeaf() )
    return ( pairs.size() );
  else
    return ( pairs.size() + int(extra_entry != NULL) ); 
}

bool Node::hasEnoughKeys() {

//  #ifdef DEBUG
//   cout << "Node::hasEnoughKeys - isLeaf(): " << isLeaf() << endl;
//   cout << "Node::hasEnoughKeys - numOfEntries(): " << numOfEntries() << endl;
//   cout << "Node::hasEnoughKeys - ( numOfEntries() >= FLOOR(tree->key_num + 1, 2) ): " << (numOfEntries() >= FLOOR(tree->key_num + 1, 2)) << endl;
//   cout << "Node::hasEnoughKeys - ( numOfEntries() >= CEIL(tree->key_num + 1, 2) ): " << ( numOfEntries() >= CEIL(tree->key_num + 1, 2) ) << endl;
// #endif

  if( isLeaf() )
    return ( numOfEntries() >= FLOOR(tree->key_num + 1, 2) );
  else
    return ( numOfEntries() >= CEIL(tree->key_num + 1, 2) );
}

bool Node::hasExtraKeys() {
  if( isLeaf() )
    return ( numOfEntries() > FLOOR(tree->key_num + 1, 2) );
  else
    return ( numOfEntries() > CEIL(tree->key_num + 1, 2) );
}

bool Node::isSibling(Node * _left, Node * _right) {
    if( _left == NULL || _right == NULL) 
      return false;

// #ifdef DEBUG
//     cout << "_left->parent's 1st child key: " << _left->parent->pairs.front().first 
//          << "_right->parent's 1st child key: " << _right->parent->pairs.front().first << endl;
//     cout << "Node::isSibling - _left->parent == _right->parent " << ((_left->parent == _right->parent )?"True":"False") << endl;
// #endif 
    
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
#ifdef DEBUG
  cout << "Node::remove - isLeaf(): " << isLeaf() << endl;
  cout << "Node::remove - hasEnoughKeys(): " << hasEnoughKeys() << endl;
#endif

  if( isLeaf() && removeValueEntry(_key) == false ){
    return KEY_NOT_FOUND;
  }
  
  if( !hasEnoughKeys() )
    return TOO_FEW_KEYS;

  return SUCCESS;
}

void Node::redistribute( Node * _left, Node * _right, bool right_to_left) {
  auto parent = _right->parent;

  if( _left->isLeaf() && _right->isLeaf() ) {
    // For leaf node, redistribution may be easier

    if( right_to_left ){
      auto entry = _right->pairs.front();
      _right->pairs.erase(_right->pairs.begin());
      _left->pairs.push_back(entry);

    }
    else {
      // Left to Right
      auto entry = _left->pairs.back();
      _left->pairs.pop_back();
      _right->pairs.insert( _right->pairs.begin(), entry);
    }

    // Redistribute higher-level keys
    for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++) {
      if( it->second == _right ){
        it->first = _right->pairs.front().first;
      }
    }

    // Handle the case of extra entry
    if( parent->getNextLeaf() == _right ){
      parent->pairs.back().first = _right->pairs.front().first;
    }
  }
  else {
    int key = -1; 
    for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++) {
      if( it->second == _left ){
        key = it->first;
      }
    }
    // cout << "Node::redistribute - Key value: " << key << endl;
    if( right_to_left ){
      auto entry = _right->pairs.front(); 

      auto new_entry = make_pair( key, _left->getNextLeaf());
      _left->pairs.push_back(new_entry);

      _right->pairs.erase(_right->pairs.begin());

      // Set the parent of left entry
      ((Node *)entry.second)->parent = _left;
      _left->setNextLeaf( (Node *) entry.second );

      // Redistribute higher-level keys
      for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++) {
        if( it->second == _left ){
          // it->first = _right->pairs.front().first;
          it->first = entry.first;
        }
      }
    }
    else {
      // Left to Right
      auto entry = _left->pairs.back(); 
      auto new_entry = make_pair(key, _left->getNextLeaf());

      _left->setNextLeaf( (Node *) entry.second);
      _left->pairs.pop_back();

      // Set the parent of right entry
      ((Node *)new_entry.second)->parent = _right;
      _right->pairs.insert( _right->pairs.begin(), new_entry);

      // Redistribute higher-level keys
      for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++) {
        if( it->second == _left ){
          // it->first = _left->pairs.front().first;
          it->first = entry.first;
        }
      }
    }

  }

}
void Node::forceRemove() {
  this->pairs.clear();
  this->tree->node_number--;
}

void Node::coalesce( Node * _left, Node * _right, bool merge_to_right) {
  // Function phylosophy
  // ==========================================================
  // 1. Merge Nodes
  // 2. Delete Parent Key
  // 3. Rebalance Parent Key

  auto parent = _left->parent;
 

  if( _left->isLeaf() && _right->isLeaf() ){
    
    if( merge_to_right ){

      for (auto it = _left->pairs.end(); it != _left->pairs.begin(); --it)
      {
        // Change parent node
        _right->pairs.insert(_right->pairs.begin(), *it);
      }
      if( _left->left_ptr != NULL ) {
        _right->becomeRightSibingOf(_left->left_ptr); 
        _left->left_ptr->setNextLeaf(_right);
      }

      _left->forceRemove();

      for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++)
      {
        if( it->second == _left ){
          parent->pairs.erase(it);
        }
      }

    }else{
      for (auto it = _right->pairs.begin(); it != _right->pairs.end(); ++it)
      {
        _left->pairs.push_back(*it);
      }

      if( _right->right_ptr != NULL ){
        _right->right_ptr->becomeRightSibingOf(_left);
        _left->setNextLeaf(_right->right_ptr);
      } 

      _right->forceRemove();

      int key = 0;
      for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++)
      {
        if( it->second == _right ){
          key = it->first;
          parent->pairs.erase(it);
          break;
        }
      }

      if( parent->getNextLeaf() != _right && key != 0 ){
        for(auto it = parent->pairs.begin(); it != parent->pairs.end(); it++) {
          if( it->second == _left )
            it->first = key;
        }
      } else {
        parent->pairs.pop_back();
        parent->setNextLeaf(_left);
      }
    }

  }else {

    // if( merge_to_right ){
    //   for (auto it = _left->pairs.end(); it != _left->pairs.begin(); --it)
    //   {
    //     _right->pairs.insert(_right->pairs.begin(), *it);
    //   }
    //   _left->pairs.clear();


    // }
    // else{
    //   for (auto it = _right->pairs.begin(); it != _right->pairs.end(); ++it)
    //   {
    //     _left->pairs.push_back(*it);
    //   }
    //   _right->pairs.clear();


    // }
#ifdef DEBUG
    cout << "Coalesce Interior Node...Still not implemented." << endl;
#endif
  }

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

  int delete_status;

  while( (delete_status = current_node->remove(_key)) == TOO_FEW_KEYS )
  {


#ifdef DEBUG
      cout << "BpTree::remove - Current Node has too few keys..." << endl;
#endif

    if( current_node->left_ptr != NULL                      && 
      Node::isSibling(current_node->left_ptr, current_node) && 
      current_node->left_ptr->hasExtraKeys()                ){

#ifdef DEBUG
      cout << "BpTree::remove - Redistribute: from left sibling to right node..." << endl;
#endif


        // 1. Redistribute to left sibling
      Node::redistribute( current_node->left_ptr, current_node );

    }else if( current_node->right_ptr != NULL                &&
      Node::isSibling(current_node, current_node->right_ptr) && 
      current_node->right_ptr->hasExtraKeys()                ){
        // 2. Redistribute to right sibling


#ifdef DEBUG
      cout << "BpTree::remove - Redistribute: from right sibling to left node..." << endl;
#endif


      Node::redistribute( current_node, current_node->right_ptr, true );

    }else if( current_node->left_ptr != NULL                && 
              !current_node->left_ptr->hasExtraKeys()       ){
        // 3. Coalesce left sibling



#ifdef DEBUG
      cout << "BpTree::remove - Coalesce: left sibling and current node" << endl;
#endif


      Node::coalesce(current_node->left_ptr, current_node);

    }else if( current_node->right_ptr != NULL                 && 
              !current_node->right_ptr->hasExtraKeys()        ){
        // 4. Coalesce right sibling


#ifdef DEBUG
      cout << "BpTree::remove - Coalesce: current node and right sibling" << endl;
#endif

      Node::coalesce(current_node, current_node->right_ptr);

    }
    else {
#ifdef DEBUG
      cout << "BpTree::remove - Fatal Problem" << endl;
#endif      
    }

    if (current_node->parent != NULL) {
      current_node = current_node->parent;

#ifdef DEBUG
      cout << "BpTree::remove - Iterate parent node" << endl;
      // cout << "BpTree::remove - Parent node size: "  << current_node->numOfEntries()           << endl;
      // cout << "BpTree::remove - Node criteria: "     << CEIL( current_node->tree->key_num , 2) << endl;
      // cout << "BpTree::remove - HasEnoughKeys: "     << current_node->hasEnoughKeys() << endl;
#endif  
    }
    else
    {
#ifdef DEBUG
      cout << "BpTree::remove - Reach the root of tree" << endl;
#endif       
    }

  }

  if( delete_status == KEY_NOT_FOUND) 
    // The case that there is no such key in the bpTree
    return false;

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

