#include <iostream>
#include <cstring>
using namespace std;

class Node{

 public:
  //these function declarations are all pretty self explanatory :)
  Node(int);
  int getVal();
  void setVal(int);
  Node* getRight();
  Node* getLeft();
  Node* getParent();
  void setRight(Node*);
  void setLeft(Node*);
  void setParent(Node*);
  int getColor();
  void setColor(int);
  Node* getGrandParent();
  Node* getUncle();
  Node* getSibling();
  void rotateRight();
  void rotateLeft();
  ~Node();
  
 private: 
  Node* left;
  Node* right;
  Node* parent;
  int color;
  int val;
  
};
