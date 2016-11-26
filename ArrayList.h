//ArrayList.h
//creates an array list class

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "List.h"

template <class item_t>
class ArrayList : public List<item_t>
{
  protected:
   item_t* items;
   int size;
   int capacity;

   //Checks the capacity and doubles capacity if necessary
   void checkCapacity();

  public:
   //Creates an empty list with capacity 10
   ArrayList();
   //Creates a list with the given capacity
   ArrayList(int capacity);
   virtual ~ArrayList();

   //Pushes item to the back of the list
   virtual void pushBack(const item_t& item);   
   //Removes, but does not return, the last item
   virtual void popBack();
   //Returns a reference to the last item (does not remove it).
   virtual const item_t& getBack() const;
   
   //Pushes item to the front of the list
   virtual void pushFront(const item_t& item);
   //Removes, but does not return, the first item
   virtual void popFront();
   //Returns a reference to the first item (does not remove it).
   virtual const item_t& getFront() const;

   //Returns a reference to the item at the given index
   virtual const item_t& getItem(int index) const;
   //Sets the item at the given index
   virtual void setItem(int index, const item_t& item);

   //Inserts the given item at the given index
   //(items at index or beyond shift up one position)
   //Inserting just past the last element (i.e. position
   //size) shoud be equivalent to pushBack.
   virtual void insert(int index, const item_t& item);
   //Removes the item at the given index
   //(items beyond index shift down one position)
   virtual void remove(int index);

   //Returns the number of items in the list
   virtual int getSize() const;
   //Returns true if the list is empty (false otherwise)
   virtual bool isEmpty() const;
   //Returns the size of the array that contains the list
   virtual int getCapacity() const;
};

template <class item_t>
ArrayList<item_t>::ArrayList()
{
  //Constructor creates empty array list with a capacity of 10

  items = new item_t[10];
  size = 0;
  capacity = 10;
}

template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)
{
  /* Constructor takes a capacity and creates an empty array list with the
  given capacity */

  items = new item_t[capacity];
  size = 0;
  this -> capacity = capacity;
}

template <class item_t>
ArrayList<item_t>::~ArrayList()
{
  //Destructor removes the items in the array list and resets capacity and size

  capacity = 0;
  size = 0;
  delete[] items;
}

template <class item_t>
void ArrayList<item_t>::checkCapacity()
{
  //Checks the capacity and doubles capacity if necessary

  if(size+1 > capacity) { //at least 1 greater than capacity
    item_t* newArray = new item_t[capacity*2];

    for (int i = 0; i < size; i++) {
      newArray[i] = items[i];
    }

    delete[] items;
    items = newArray; //sets array to double capacity array
    capacity *= 2;
  }
}

template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item)
{
  //Pushes item to the back of the list

  checkCapacity();

  items[size] = item;
  size++;
}

template <class item_t>
void ArrayList<item_t>::popBack()
{
  //Removes, but does not return, the last item
  //Can be done by decreasing pointer to last index by 1

  size--;
}

template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{
  //Returns a reference to the last item (does not remove it)

  return items[size-1];
}

template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{
  //Pushes item to the front of the list

  insert(0, item); //same as insert at index 0
}

template <class item_t>
void ArrayList<item_t>::popFront()
{
  //Removes, but does not return, the first item

  remove(0); //same as remove at index 0
}

template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{
  //Returns a reference to the first item (does not remove it)

  return items[0];
}

template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const
{
  //Returns a reference to the item at the given index

  return items[index];
}

template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{
  //Sets the item at the given index

  items[index] = item;
}

template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{
  //Inserts the given item at the given index

  checkCapacity();

  if(index == size) { //index is at one past last index; just pushBack
    pushBack(item);
  }

  else {
    //Shift every element down to, and including, the goal index 1 to the right

    for(int i = size; i >= index; i--) {
      items[i] = items[i-1];
    }
    
    items[index] = item;
    size++;
  }
}

template <class item_t>
void ArrayList<item_t>::remove(int index)
{
  //Removes the item at the given index

  for (int i = index; i < size-1; i++) {
    //Shifts every item 1 to the left from the remove index to the end

    items[i] = items[i+1];
  }

  size--;
}

template <class item_t>
int ArrayList<item_t>::getSize() const
{
  //Returns the number of items in the list

  return size;
}

template <class item_t>
bool ArrayList<item_t>::isEmpty() const
{
  //Returns true if the list is empty (false otherwise)

  return size == 0;
}

template <class item_t>
int ArrayList<item_t>::getCapacity() const
{
  //Returns the size of the array that contains the list

  return capacity;
}

#endif
