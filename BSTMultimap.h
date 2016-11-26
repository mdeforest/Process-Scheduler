#ifndef BSTMULTIMAP_H
#define BSTMULTIMAP_H

#include <queue>
#include <iostream>

#include "BSTNode.h"
#include "BSTForwardIterator.h"

using namespace std;

template <class key_t, class val_t>
class BSTMultimap
{
 protected:
  BSTNode<key_t, val_t>* root;
  BSTNode<key_t, val_t>* sentinel;
  int numItems;

  void transplant(BSTNode<key_t, val_t>* node1, BSTNode<key_t, val_t>* node2);
  virtual void insertNode(BSTNode<key_t, val_t>* newNode);

 public:
  BSTMultimap();
  virtual ~BSTMultimap();

  virtual void insert(const key_t& key, const val_t& val);
  virtual int getSize();
  virtual bool isEmpty();
  virtual void printTree();
  virtual bool contains(const key_t& key) const;
  virtual void clear();

  virtual BSTForwardIterator<key_t, val_t> getMin() const;
  virtual BSTForwardIterator<key_t, val_t> getMax() const;
  virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> findLast(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator
						  <key_t, val_t>& pos);

};

template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap()
{
  sentinel = 0;
  root = sentinel;
  numItems = 0;
}

template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::~BSTMultimap()
{
  clear();
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::clear()
{
  queue<BSTNode<key_t, val_t>*> newQueue;
  newQueue.push(root);

  while (!newQueue.empty()) {
    BSTNode<key_t, val_t>* curNode = newQueue.front();
    newQueue.pop();

    if (curNode != sentinel) {
      if (curNode -> getLeftChild() != sentinel) {
	newQueue.push(curNode -> getLeftChild());
      }

      else {
	newQueue.push(sentinel);
      }

      if (curNode -> getRightChild() != sentinel) {
	newQueue.push(curNode -> getRightChild());
      }

      else {
	newQueue.push(sentinel);
      }

      delete curNode;
    }
  }

  root = sentinel;
  numItems = 0;
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& val)
{
  BSTNode<key_t, val_t>* newNode = new BSTNode<key_t, val_t>(key, val);

  insertNode(newNode);
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* newNode)
{
  BSTNode<key_t, val_t>* curNode = root;
  BSTNode<key_t, val_t>* y = sentinel;

  while (curNode != sentinel) {
    y = curNode;

    if (newNode -> getKey() < curNode -> getKey()) {
      curNode = curNode -> getLeftChild();
    }

    else {
      curNode = curNode -> getRightChild();
    }
  }

  newNode -> setParent(y);

  if (y == sentinel) {
    root = newNode;
  }

  else if (newNode -> getKey() < y -> getKey()) {
    y -> setLeftChild(newNode);
  }

  else {
    y -> setRightChild(newNode);
  }

  numItems++;
}

template <class key_t, class val_t>
int BSTMultimap<key_t, val_t>::getSize()
{
  return numItems;
}

template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::isEmpty()
{
  return numItems == 0;
}

template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const
{
  BSTNode<key_t, val_t>* curNode = root;

  while (curNode != sentinel && key != curNode -> getKey()) {

    if (key < curNode -> getKey()) {
      curNode = curNode -> getLeftChild();
    }

    else {
      curNode = curNode -> getRightChild();
    }
  }

  if (curNode != sentinel) {
    return true;
  }

  return false;
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const
{
  BSTNode<key_t, val_t>* curNode = root;
  
  if (numItems == 0) {
    return BSTForwardIterator<key_t, val_t>(sentinel, sentinel);
  }
  
  while (curNode -> getLeftChild() != sentinel) {
    curNode = curNode -> getLeftChild();
  }

  return BSTForwardIterator<key_t, val_t>(curNode, sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const
{
  BSTNode<key_t, val_t>* curNode = root;
  
  if (numItems == 0) {
    return BSTForwardIterator<key_t, val_t>(sentinel, sentinel);
  }
  
  while (curNode -> getRightChild() != sentinel) {
    curNode = curNode -> getRightChild();
  }

  return BSTForwardIterator<key_t, val_t>(curNode, sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::
findFirst(const key_t& key) const
{
  BSTNode<key_t, val_t>* curNode = root;
  BSTNode<key_t, val_t>* curNew = sentinel;

  while (curNode != sentinel) {
    if (key > curNode -> getKey()) {
      curNode = curNode -> getRightChild();

      if (key == curNode -> getKey()) {
	curNew = curNode;
      }

    }

    else {
      curNode = curNode -> getLeftChild();
      
      if (curNode != sentinel) {
	if (curNode -> getKey() == key) {
	  curNew = curNode;
	}
      }

    }

  }

  return BSTForwardIterator<key_t, val_t>(curNew, sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::
findLast(const key_t& key) const
{
  BSTNode<key_t, val_t>* curNode = root;
  BSTNode<key_t, val_t>* curNew = sentinel;

  while (curNode != sentinel) {
    if (key < curNode -> getKey()) {
      curNode = curNode -> getLeftChild();

      if (key == curNode -> getKey()) {
	curNew = curNode;
      }

    }

    else {
      curNode = curNode -> getRightChild();
      
      if (curNode != sentinel) {
	if (curNode -> getKey() == key) {
	  curNew = curNode;
	}
      }

    }

  }

  return BSTForwardIterator<key_t, val_t>(curNew, sentinel);
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::
transplant(BSTNode<key_t, val_t>* node1, BSTNode<key_t, val_t>* node2)
{
  if (node1 -> getParent() == sentinel) {
    root = node2;
  }

  else if (node1 == node1 -> getParent() -> getLeftChild()) {
    node1 -> getParent() -> setLeftChild(node2);
  }

  else {
    node1 -> getParent() -> setRightChild(node2);
  }

  if (node2 != sentinel) {
    node2 -> setParent(node1 -> getParent());
  }
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::
remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTNode<key_t, val_t>* current = pos.current;
  BSTNode<key_t, val_t>* successor = current -> getRightChild();

  if (current -> getLeftChild() == sentinel) {
    transplant(current, current -> getRightChild());
  }

  else if (current -> getRightChild() == sentinel) {
    transplant(current, current -> getLeftChild());
  }

  else {
    while (successor -> getLeftChild() != sentinel) {
      successor = successor -> getLeftChild();
    }

    if (successor -> getParent() != current) {
      transplant(successor, successor -> getRightChild());
      successor -> setRightChild(current -> getRightChild());
      successor -> getRightChild() -> setParent(successor);
    }

    transplant(current, successor);
    successor -> setLeftChild(current -> getLeftChild());
    successor -> getLeftChild() -> setParent(successor);
  }

  delete current;
  numItems--;

  return BSTForwardIterator<key_t, val_t>(successor, sentinel);
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::printTree()
{
  queue<BSTNode<key_t, val_t>*> newQueue;
  newQueue.push(root);

  while (!newQueue.empty()) {
    BSTNode<key_t, val_t>* curNode = newQueue.front();
    newQueue.pop();

    if (curNode != sentinel) {
      cout << "Node: (" << curNode -> getKey() << ", " 
	   << curNode -> getValue() << ")" << endl;

      if (curNode -> getLeftChild() != sentinel) {
	newQueue.push(curNode -> getLeftChild());
      }

      else {
	newQueue.push(sentinel);
      }

      if (curNode -> getRightChild() != sentinel) {
	newQueue.push(curNode -> getRightChild());
      }

      else {
	newQueue.push(sentinel);
      }
    }

    else {
      cout << "NULL" << endl;
    }
  }
}

#endif
