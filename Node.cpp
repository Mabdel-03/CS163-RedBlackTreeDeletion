#include <iostream>
#include <cstring>
#include "Node.h"
using namespace std;

Node::Node(int newVal) {
  val = newVal;
  right = NULL;
  left = NULL;
  parent = NULL;
  color = 1; //colors are 1 and 2, 1 is black 2 is red
}

//these functions are all pretty self explanatory by name
int Node::getVal() {
  return val;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getParent() {
  return parent;
}

void Node::setVal(int newVal) {
  val = newVal;
}

void Node::setRight(Node* newRight) {
  right = newRight;
}

void Node::setLeft(Node* newLeft) {
  left = newLeft;
}

void Node::setParent(Node* newParent) {
  parent = newParent;
}

Node* Node::getGrandParent() {
  return parent->getParent();
}

Node* Node::getSibling() {
  if(parent == NULL) {
    return NULL;
  }
  if(this == parent->getLeft()) {
    return parent->getRight();
  }
  else {
    return parent->getLeft();
  }
}

void Node::setColor(int newColor) {
  color = newColor;
}

int Node::getColor() {
  if(this == NULL) {
    return 2;
  }
  return color;
}

Node* Node::getUncle() {
  if(parent == NULL) {
    return NULL;
  }
  return parent->getSibling();
}

void Node::rotateLeft() {

  Node* r = right;
  Node* p = parent;

  if(r == NULL) {
    return;
  }
  right = r->getLeft();
  r->setLeft(this);
  parent = r;
  if(right != NULL) {
    right->setParent(this);
  }
  if(p != NULL) {
    if(this == p->getLeft()) {
      p->setLeft(r);
    }
    else if(this == p->getRight()) {
      p->setRight(r);
    }
  }
  r->setParent(p); 
}

void Node::rotateRight() {

  Node* l = left;
  Node* p = parent;

  if(l == NULL) {
    return;
  }
  left = l->getRight();
  l->setRight(this);
  parent = l;
  if(left != NULL) {
    left->setParent(this);
  }
  if(p != NULL) {
    if(this == p->getLeft()) {
      p->setLeft(l);
    }
    else if(this == p->getRight()) {
      p->setRight(l);
    }
  }
  l->setParent(p); 
}

Node::~Node() {

}
