//Code Written By Mahmoud Abdelmoneum on 6/6/2021
//Code Written To be a Red Black Tree implementation that takes number input
// either in the form of file input or console input and put into a RB Tree
// This implementation also includes a search feature, to search the tree for values
// As well as a deletion function, to delete values from the tree
// A LOT of this project's pseudocode comes from: en.wikipedia.org/wiki/Red-black_tree
// All of this project's recursive cases for both deletion and insertion are taken from wikipedia!


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Node.h"
using namespace std;

void rotateLeft(Node*&, Node*&);
void rotateRight(Node*&, Node*&);
void repairTree(Node* &, Node* &);
void insert(Node*&, int);
void addNode(Node*&, Node*);
void case1(Node*&);
void case2();
void case3(Node*&, Node* &);
void case4(Node*&, Node* &);
void case4pt2(Node*&, Node* &);
void printTree(Node*, int);
Node* Search(Node*, int);
void removeNode(Node*&, Node*&);
Node* traverseDown(Node*);
void replaceNode(Node*&, Node*&);
void DeleteOneChild(Node*&);
void DeleteCase1(Node*&);
void DeleteCase2(Node*&);
void DeleteCase3(Node*&);
void DeleteCase4(Node*&);
void DeleteCase5(Node*&);
void DeleteCase6(Node*&);


int main() {

  //set head
  Node* head = NULL;
  char type;
  char input[999];

  //prompt user for type
  cout << "Enter 1 for file input, enter 2 for manual input" << endl;

  cin >> type;
  cin.ignore();
  //file input
  if(type == '1') {
    //got tutorial for this portion from cplusplus.com/doc/tutorial/files/
    cout << "Please enter the file name" << endl;
    char fileInput[999];
    cin.getline(fileInput, sizeof(fileInput));
    ifstream fileStream;
    fileStream.open(fileInput);
    if(fileStream) {
      fileStream.getline(input, sizeof(input));
    }
    else { //file doesn't exist
      cout << "This file cannot be found" << endl;
    }

  }

  else if(type == '2') {
    cout << "Please enter the number set, dividing each number by a space" << endl;
    cin.getline(input, 999);
  }
  char* list = strtok(input, " "); //strtok splits up input by spaces
  while(list) {
    insert(head, atoi(list));
    list = strtok(NULL, " ");
  }
  while(true) {
    cout << "Enter ADD to add to the RB tree, PRINT to print it, SEARCH to search for a value, DELETE to delete a value, and QUIT to exit the program" << endl;
    cin.getline(input, sizeof(input));
    for(int i = 0; i<sizeof(input); i++) {
      input[i] = toupper(input[i]);
    }
    if(strcmp(input, "ADD") == 0) { //add a new node
      int val;
      cout << "Enter the value that you would like to add" << endl;
      cin >> val;
      cin.ignore();
      insert(head, val);
    }
    
    else if(strcmp(input, "PRINT") == 0) { //print out/display the RB Tree
      printTree(head, 0);
    }
    
    else if(strcmp(input, "SEARCH") == 0) {
      int val;
      cout << "Please enter the number that you would like to search for" << endl;
      cin >> val;
      cin.ignore();
      if(Search(head, val) == NULL) {
	cout << "This value cannot be found!" << endl;
      }
      else {
	cout << "The value is a part of the tree!" << endl; 
      }
    }
    
    else if(strcmp(input, "DELETE") == 0) {
      int val;
      cout << "Please input the value that you wish to delete" << endl;
      cin >> val;
      cin.ignore();
      Node* n = Search(head, val);
      if(n == NULL) {
	cout << "The desired value was not found" << endl;
      }
      else {
	removeNode(head, n);
      }
    }
    
    else if(strcmp(input, "QUIT") == 0) {
      return 0;
    }
    
  }
}

void addNode(Node* &head, Node* n) { //function uses recursion to insert new node
   if(head == NULL) { //add head if current head is NULL
     head = n;
     return;
   }

   if(head->getVal() < n->getVal()) { //if the input is LARGER than the head
     if(head->getRight() == NULL) { //if at base of tree, add new node right
       head->setRight(n);
       head->getRight()->setParent(head);
       return;
     }
     else { //otherwise, traverse right
	 Node* right = head->getRight();
       addNode(right, n);
     }
   }
   else { //if the input is SMALLER than the head
     if(head->getLeft() == NULL) { //if left of head is empty
       head->setLeft(n);
       head->getLeft()->setParent(head);
       return;
     }
     else { //if not, we will traverse further down the left side
       Node* left = head->getLeft();
       addNode(left, n);
     }
   }
}

void insert(Node* &head, int val) {
  Node* n = new Node(val);
  addNode(head, n); //calls recursion function
  repairTree(n, head); //use repair Tree to set colors appropriately, balance
}

void repairTree(Node* &n, Node* &head) {

  if(n->getParent() == NULL) { //base case
    case1(n);
  }

  //if parent is red
  else if(n->getParent()->getColor() == 2) {
    case2();
  }
  
  //if uncle is red
  else if(n->getUncle() != NULL && n->getUncle()->getColor() == 1) {
    case3(n, head);
  }

  else {
    case4(n, head);
  }
  
}

//Next make the cases used to recursive function to repair the tree

void case1(Node* &n) {
  n->setColor(2);
}

void case2() {
  return;
}

void case3(Node* &n, Node* &head) {
  //set parent/uncle to black
  n->getParent()->setColor(2);
  n->getUncle()->setColor(2);
  //set grandparent to red
  n->getGrandParent()->setColor(1);
  //use the grandparent to rerun the repairTree function
  Node* grandparent = n->getGrandParent();
  repairTree(grandparent, head);
}

void case4(Node* &n, Node* &head) {
  Node* parent = n->getParent();
  Node* grandparent = n->getGrandParent();
  if(n == parent->getRight() && parent == grandparent->getLeft()) {
    parent->rotateLeft();
    n = n->getLeft();
  }
  else if(n == parent->getLeft() && parent == grandparent->getRight()) {
    parent->rotateRight();
    n = n->getRight();
  }
  case4pt2(n, head);
}

void case4pt2(Node* &n, Node* &head) {
  Node* parent = n->getParent();
  Node* g = n->getGrandParent();
  //if node to the left
  if(n == parent->getLeft()) {
    g->rotateRight();
  }
  else {
    g->rotateLeft();
  }
  if(g == head) {
    head = parent;
  }
  parent->setColor(2);
  g->setColor(1);
}


//function to print tree visualization		 
void printTree(Node* head, int depth) {
  //Go to right branch
  if(head == NULL) {
    return;
  }
  if(head->getRight() != NULL) {
    printTree(head->getRight(), depth+1);
  }
  for(int i = 0; i < depth; i++) {
    cout << "      ";
  }
  //print colors
  if(head->getColor() == 1) { //red
    cout << "\033[1;31m"<<head->getVal()<<"\033[0m"<<endl;
  }
  else { //"black", which is actually displayed as white
    cout << "\033[1;37m"<<head->getVal()<<"\033[0m"<<endl;
  }
  //go to left branch
  if(head->getLeft() != NULL) {
    printTree(head->getLeft(), depth+1);
  }
}

Node* Search(Node* h, int searchcode) {
  
  if(h == NULL || h->getVal() == searchcode) { //if key found, return node
    return h;
  }

  if(searchcode < h->getVal()) { //if key < val, search left (left will be bigger)
    Node* left = h->getLeft();
    return Search(left, searchcode);
  }

  else if(searchcode > h->getVal()) { //if key > val, search right (right will be smaller)
    Node* right = h->getRight();
    return Search(right, searchcode);
  }

}

//Deletion function, with the recursive cases in separate functions below:

void removeNode(Node*& h, Node* &n) {
  if(h== n && n->getLeft() == NULL && n->getRight() == NULL) { //base case
    delete n;
    n = NULL;
    return;
  }

  else if(n->getLeft() != NULL && n->getRight() != NULL) { //case 2: node has 2 children
    Node* left = n->getLeft();
    left = traverseDown(left);
    n->setVal(left->getVal());
    DeleteOneChild(left);
    return;
  }

  DeleteOneChild(n);

}


Node* traverseDown(Node* head) {
  if(head->getRight() == NULL) {
    return head;
  }
  traverseDown(head->getRight());
}

void replaceNode(Node* &n, Node* &child) {
  child->setParent(n->getParent());
  if(n->getParent() == NULL) {
    n = child;
  }
  else if(n == n->getParent()->getLeft()) {
    n->getParent()->setLeft(child);
  }
  else {
    n->getParent()->setRight(child);
  }
}

//recursive case to delete one of two children
void DeleteOneChild(Node* &n) {
  Node* child;
  if(n->getRight() == NULL) {
    child = n->getLeft();
  }
  else {
    child = n->getRight();
  }
  if(child == NULL) {
    child = new Node(-1);
    child->setColor(2);
  }
  replaceNode(n, child);
  if(n->getColor() == 2) {
    if(child->getColor() == 1) {
      child->setColor(2);
    }
    else {
      DeleteCase1(child);
    }
  }
  if(child->getVal() == -1) {
    if(child->getParent() != NULL) {
      if(child == child->getParent()->getLeft()) {
	child->getParent()->setLeft(NULL);
      }
      else {
	child->getParent()->setRight(NULL);
      }
     }
   }
}

//wikipedia RBT page case 1
void DeleteCase1(Node* &n) {
  if(n->getParent() != NULL) {
    DeleteCase2(n);
  }
}

//wikipedia RBT page case 2
void DeleteCase2 (Node* &n) {
  Node* s = n->getSibling();
  if(s->getColor() == 1) {
    n->getParent()->setColor(1);
    s->setColor(2);
    Node* p = n->getParent();
    if(n == n->getParent()->getLeft()) {
      n->getParent()->rotateLeft();
    }
    else {
      n->getParent()->rotateRight();
    }
  }
  DeleteCase3(n);
}

//wikipedia RBT page case 3
void DeleteCase3(Node* &n) {
  Node* s = n->getSibling();
  if((n->getParent()->getColor() == 2) && (s->getColor() == 2) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)) {
    s->setColor(1);
    Node* p = n->getParent();
    DeleteCase1(p);
  }
  else {
    DeleteCase4(n);
  }
}

//wikipedia RBT page case 4 
void DeleteCase4(Node* &n) {
  Node* s = n->getSibling();
  if(n->getParent()->getColor() == 1 && s->getColor() == 2 && s->getLeft()->getColor() == 2 && s->getRight()->getColor() == 2) {
    s->setColor(1);
    n->getParent()->setColor(2);
  }
  else {
    DeleteCase5(n);
  }
}

//wikipedia RBT page case 5
void DeleteCase5(Node* &n) {
  Node* s = n->getSibling();
  if(s->getColor() == 2) {
    if((n == n->getParent()->getLeft()) && (s->getRight()->getColor() == 2) && (s->getLeft()->getColor() == 1)) {
      s->setColor(1);
      s->getLeft()->setColor(2);
      s->rotateRight();
    }
    if((n == n->getParent()->getRight()) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)) {
      s->setColor(1);
      s->getRight()->setColor(2);
      s->rotateLeft();
    }
  }
  DeleteCase6(n);
}

//wikipedia RBT page case 6 
void DeleteCase6(Node* &n) {
  Node* s = n->getSibling();
  s->setColor(n->getParent()->getColor());
  n->getParent()->setColor(2);
  if(n == n->getParent()->getLeft()) {
    s->getRight()->setColor(2);
    n->getParent()->rotateLeft();
  }
  else {
    s->getLeft()->setColor(2);
    n->getParent()->rotateRight();
  }

}
		       

    
