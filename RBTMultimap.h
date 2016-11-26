#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  protected:
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);

   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

   //Fix up the tree after deleting a node
   //ReplacementNode is the node that replaced the deleted node
   //(possibly the sentinel)
   virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);

  public:
   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::RBTMultimap()
{
  key_t key;
  val_t val;

  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t, val_t>(key, val, false);

  this -> sentinel = newNode;
  this -> root = this -> sentinel;
}

template <class key_t, class val_t>
RBTMultimap<key_t, val_t>::~RBTMultimap()
{
  this -> clear();
  delete this -> sentinel;
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* y = node -> getRightChild();
  node -> setRightChild(y -> getLeftChild());

  if (y -> getLeftChild() != this -> sentinel) {
    y -> getLeftChild() -> setParent(node);
  }

  y -> setParent(node -> getParent());

  if (node -> getParent() == this -> sentinel) {
    this -> root = y;
  }

  else if (node == node -> getParent() -> getLeftChild()) {
    node -> getParent() -> setLeftChild(y);
  }

  else {
    node -> getParent() -> setRightChild(y);
  }

  y -> setLeftChild(node);
  node -> setParent(y);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* y = node -> getLeftChild();
  node -> setLeftChild(y -> getRightChild());

  if (y -> getRightChild() != this -> sentinel) {
    y -> getRightChild() -> setParent(node);
  }

  y -> setParent(node -> getParent());

  if (node -> getParent() == this -> sentinel) {
    this -> root = y;
  }

  else if (node == node -> getParent() -> getRightChild()) {
    node -> getParent() -> setRightChild(y);
  }

  else {
    node -> getParent() -> setLeftChild(y);
  }

  y -> setRightChild(node);
  node -> setParent(y);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{
  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t, val_t>(key, value, true);

  newNode -> setLeftChild(this -> sentinel);
  newNode -> setRightChild(this -> sentinel);

  this -> insertNode(newNode);
  insertFixup(newNode);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode)
{
  while (insertedNode -> getParent() -> getColor()) {
    if (insertedNode -> getParent() == insertedNode -> getParent() ->
	getParent() -> getLeftChild()) {
        RBTNode<key_t, val_t>* uncle = insertedNode -> getParent() ->
	getParent() -> getRightChild();

      if (uncle -> getColor()) {
	insertedNode -> getParent() -> setColor(false);
	uncle -> setColor(false);

	insertedNode -> getParent() -> getParent() -> setColor(true);
	insertedNode = insertedNode -> getParent() -> getParent();
      }

      else {
	if (insertedNode == insertedNode -> getParent() -> getRightChild()) {
	  insertedNode = insertedNode -> getParent();
	  rotateLeft(insertedNode);
	}

	insertedNode -> getParent() -> setColor(false);
	insertedNode -> getParent() -> getParent() -> setColor(true);

	rotateRight(insertedNode -> getParent() -> getParent());
      }
    }
    else {
      RBTNode<key_t, val_t>* uncle = insertedNode -> getParent() ->
	getParent() -> getLeftChild();

      if (uncle -> getColor() == true) {
	insertedNode -> getParent() -> setColor(false);
	uncle -> setColor(false);

	insertedNode -> getParent() -> getParent() -> setColor(true);
	insertedNode = insertedNode -> getParent() -> getParent();
      }

      else {
	if (insertedNode == insertedNode -> getParent() -> getLeftChild()) {
	  insertedNode = insertedNode -> getParent();
	  rotateRight(insertedNode);
	}

	insertedNode -> getParent() -> setColor(false);
	insertedNode -> getParent() -> getParent() -> setColor(true);
	rotateLeft(insertedNode -> getParent() -> getParent());
      }
    }
  }

  RBTNode<key_t, val_t>* newRoot = (RBTNode<key_t, val_t>*) this -> root;
  newRoot -> setColor(false);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace,
					   BSTNode<key_t, val_t>* 
					   replacementNode)
{
  if (nodeToReplace -> getParent() == this -> sentinel) {
    this -> root = replacementNode;
  }

  else if (nodeToReplace == nodeToReplace -> getParent() -> getLeftChild()) {
    nodeToReplace -> getParent() -> setLeftChild(replacementNode);
  }

  else {
    nodeToReplace -> getParent() -> setRightChild(replacementNode);
  }

  replacementNode -> setParent(nodeToReplace -> getParent());
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::
  remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTNode<key_t, val_t>* deleteNode = pos.current;
  RBTNode<key_t, val_t>* successor = (RBTNode<key_t, val_t>*) deleteNode;
  RBTNode<key_t, val_t>* replacementNode;

  bool successorOriginalColor = successor -> getColor();
  
  if (deleteNode -> getLeftChild() == this -> sentinel) {
    replacementNode = (RBTNode<key_t, val_t>*) deleteNode -> getRightChild();
    transplant(deleteNode, deleteNode -> getRightChild());
  }

  else if (deleteNode -> getRightChild() == this -> sentinel) {
    replacementNode  = (RBTNode<key_t, val_t>*) deleteNode -> getLeftChild();
    transplant(deleteNode, deleteNode -> getLeftChild());
  }

  else {
    RBTNode<key_t, val_t>* treeMin = (RBTNode<key_t, val_t>*) deleteNode -> getRightChild();
    while (treeMin -> getLeftChild() != this -> sentinel) {
      treeMin = treeMin -> getLeftChild();
    }

    successor = treeMin;
    successorOriginalColor = successor -> getColor();
    replacementNode = successor -> getRightChild();

    if (successor -> getParent() == deleteNode) {
      replacementNode -> setParent(successor);
    }

    else {
      transplant(successor, successor -> getRightChild());

      successor -> setRightChild(deleteNode -> getRightChild());
      successor -> getRightChild() -> setParent(successor);
    }

    transplant(deleteNode, successor);

    successor -> setLeftChild(deleteNode -> getLeftChild());
    successor -> getLeftChild() -> setParent(successor);

    RBTNode<key_t, val_t>* newDelete = (RBTNode<key_t, val_t>*) deleteNode;

    successor -> setColor(newDelete -> getColor());
  }

  if (successorOriginalColor == false) {
    deleteFixup(replacementNode);
  }

  return BSTForwardIterator<key_t, val_t>(successor, this -> sentinel);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* 
					    replacementNode)
{
  RBTNode<key_t, val_t>* newRoot = (RBTNode<key_t, val_t>*) this -> root;

  while (replacementNode != newRoot && replacementNode -> getColor() == false) {
    if (replacementNode == replacementNode -> getParent() -> getLeftChild()) {
      RBTNode<key_t, val_t>* sibling = replacementNode -> getParent() -> getRightChild();

      if (sibling -> getColor()) {
	sibling -> setColor(false);
	replacementNode -> getParent() -> setColor(true);

	rotateLeft(replacementNode -> getParent());

	sibling = replacementNode -> getParent() -> getRightChild();
      }

      if (sibling -> getLeftChild() -> getColor() == false && sibling -> getRightChild() -> getColor() == false) {
	sibling -> setColor(true);
	replacementNode = replacementNode -> getParent();
      }

      else {
	if (sibling -> getRightChild() -> getColor() == false) {
	  sibling -> getLeftChild() -> setColor(false);
	  sibling -> setColor(true);

	  rotateRight(sibling);

	  sibling = replacementNode -> getParent() -> getRightChild();
	}

	sibling -> setColor(replacementNode -> getParent() -> getColor());
	replacementNode -> getParent() -> setColor(false);
	sibling -> getRightChild() -> setColor(false);

	rotateLeft(replacementNode -> getParent());

	replacementNode = newRoot;
      }
    }

    else {
      RBTNode<key_t, val_t>* sibling = replacementNode -> getParent() -> getLeftChild();
      if (sibling -> getColor()) {
	sibling -> setColor(false);
	replacementNode -> getParent() -> setColor(true);

	rotateRight(replacementNode -> getParent());

	sibling = replacementNode -> getParent() -> getLeftChild();
      }

      if (sibling -> getRightChild() -> getColor() == false && sibling -> getLeftChild() -> getColor() == false) {
	sibling -> setColor(true);
	replacementNode = replacementNode -> getParent();
      }

      else {
	if (sibling -> getLeftChild() -> getColor() == false) {
	  sibling -> getRightChild() -> setColor(false);
	  sibling -> setColor(true);

	  rotateLeft(sibling);

	  sibling = replacementNode -> getParent() -> getLeftChild();
	}

	sibling -> setColor(replacementNode -> getParent() -> getColor());
	replacementNode -> getParent() -> setColor(false);
	sibling -> getLeftChild() -> setColor(false);

	rotateRight(replacementNode -> getParent());

	replacementNode = newRoot;
      }
    }
  }

  replacementNode -> setColor(false);
}

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

#endif
