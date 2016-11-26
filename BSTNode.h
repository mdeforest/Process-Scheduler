//BSTNode.h

#ifndef BSTNODE_H
#define BSTNODE_H

template <class key_t, class val_t>
class BSTNode
{
 protected:
  key_t key;
  val_t value;
  BSTNode<key_t, val_t>* leftChild;
  BSTNode<key_t, val_t>* rightChild;
  BSTNode<key_t, val_t>* parent;

 public:
  BSTNode(const key_t& key, const val_t& value);

  virtual ~BSTNode() { }

  virtual const val_t& getValue() const;
  virtual void setValue(const val_t& value);

  virtual const key_t& getKey() const;
  virtual void setKey(const key_t& key);

  virtual BSTNode* getLeftChild();
  virtual void setLeftChild(BSTNode* leftChild);
  
  virtual BSTNode* getRightChild();
  virtual void setRightChild(BSTNode* rightChild);

  virtual BSTNode* getParent();
  virtual void setParent(BSTNode* parent);  
};

template <class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& key, const val_t& value)
{
  this -> key = key;
  this -> value = value;

  leftChild = 0;
  rightChild = 0;
  parent = 0;
}

template <class key_t, class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() const
{
  return value;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& value)
{
  this -> value = value;
}

template <class key_t, class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() const
{
  return key;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setKey(const key_t& key)
{
  this -> key = key;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild()
{
  return leftChild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setLeftChild(BSTNode<key_t, val_t>* leftChild)
{
  this -> leftChild = leftChild;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getRightChild()
{
  return rightChild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setRightChild(BSTNode<key_t, val_t>* rightChild)
{
  this -> rightChild = rightChild;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent()
{
  return parent;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setParent(BSTNode<key_t, val_t>* parent)
{
  this -> parent = parent;
}

#endif
