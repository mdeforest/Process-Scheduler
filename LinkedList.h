//LinkedList.h

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

#include "List.h"
#include "LinkedListNode.h"

using namespace std;

template <class item_t>
class LinkedList : public List<item_t>
{
 protected:
  LinkedListNode<item_t>* head;
  LinkedListNode<item_t>* tail;
  int size;

 public:
  LinkedList();
  virtual ~LinkedList();
  virtual void pushBack(const item_t& item);
  virtual void popBack();
  virtual const item_t& getBack() const;
  virtual void pushFront(const item_t& item);
  virtual void popFront();
  virtual const item_t& getFront() const;
  virtual const item_t& getItem(int index) const;
  virtual void setItem(int index, const item_t& item);
  virtual void insert(int index, const item_t& item);
  virtual void remove(int index);
  virtual int getSize() const;
  virtual bool isEmpty() const;
  virtual void print() const;
  virtual LinkedListNode<item_t>* loopThrough(int index) const;
};

template <class item_t>
LinkedList<item_t>::LinkedList()
{
  head = NULL;
  tail = NULL;
  size = 0;
}

template <class item_t>
LinkedList<item_t>::~LinkedList()
{
  LinkedListNode<item_t>* curNode;
  
  while (head != NULL) {
    curNode = head -> getNext();
    delete head;
    head = curNode;
  }
}

template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(NULL, item);

  if (size == 0) {
    head = newNode;
    tail = newNode;
  }

  else {
    tail -> setNext(newNode);
    tail = newNode;
  }

  size++;
}

template <class item_t>
void LinkedList<item_t>::popBack()
{
  remove(size-1);
}

template <class item_t>
const item_t& LinkedList<item_t>::getBack() const
{
  return tail -> getItem();
}

template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(head, item);

  if (size == 0) {
    tail = newNode;
  }
  
  head = newNode;
  size++;
}

template <class item_t>
void LinkedList<item_t>::popFront()
{
  LinkedListNode<item_t>* oldHead = head;
  head = head -> getNext();
  delete oldHead;

  size--;
  
  if (size == 0) {
    tail = NULL;
  }  
}

template <class item_t>
const item_t& LinkedList<item_t>::getFront() const
{
  return head -> getItem();
}

template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const
{
  LinkedListNode<item_t>* curNode = head;

  curNode = loopThrough(index);
  
  return curNode -> getItem();
}

template <class item_t>  
void LinkedList<item_t>::setItem(int index, const item_t& item)
{
  LinkedListNode<item_t>* curNode = head;

  curNode = loopThrough(index);

  curNode -> setItem(item);
}

template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item)
{
  if (index == 0) {
    pushFront(item);
  }

  else if (index == size) {
    pushBack(item);
  }

  else {
    LinkedListNode<item_t>* curNode = head;
  
    curNode = loopThrough(index-1);
  
    LinkedListNode<item_t>* newItem = curNode -> getNext();
    LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(newItem, item);
    curNode -> setNext(newNode);
    size++;
  }
}

template <class item_t>
void LinkedList<item_t>::remove(int index)
{
  if (index == 0) {
    popFront();
  }

  else {
    LinkedListNode<item_t>* curNode = head;
  
    curNode = loopThrough(index-1);

    LinkedListNode<item_t>* oldNext = curNode -> getNext();
    LinkedListNode<item_t>* newNext = oldNext -> getNext();
    curNode -> setNext(newNext);
    size--;
    delete oldNext;
  }
}

template <class item_t>
int LinkedList<item_t>::getSize() const
{
  return size;
}

template <class item_t>
bool LinkedList<item_t>::isEmpty() const
{
  return size == 0;
}

template <class item_t>
void LinkedList<item_t>::print() const
{
  LinkedListNode<item_t>* curNode = head;
  if (curNode == NULL) {
    cout << "Empty" << endl;
  }
 
  else if (curNode -> getNext() == NULL) {
    cout << curNode -> getItem() << "-->" << "NULL" << endl;
  }

  else {
    cout << curNode -> getItem() << "-->"; 
    curNode = curNode -> getNext();

    while (curNode != NULL) {
      cout << curNode -> getItem() << "-->";
      curNode = curNode -> getNext();
    }

    cout << "NULL" << endl;
  }
}

template <class item_t>
LinkedListNode<item_t>* LinkedList<item_t>::loopThrough(int index) const
{
  LinkedListNode<item_t>* curNode = head;

  int i = 0;

  while (i < index) {
    curNode = curNode -> getNext();
    i++;
  }

  return curNode;
}

#endif
