/****************************************************
CIS 22C
Programmer: Nithin Nediyanchath

Assistants: Hoang Duong Vu(The idea of two binary search trees deleloper), Tung Lin Lee(Check the stability)
******************************************************/

#ifndef _BINARY_SEARCH_TREE_PLATE
#define _BINARY_SEARCH_TREE_PLATE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTreePlate : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;


public:
	// insert a node at the correct location
	bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;


};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTreePlate<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTreePlate<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTreePlate<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	bool isSuccessful = false;
	BinaryNode<ItemType>* nodePtr = findNode(this->rootPtr, anEntry);
	if (nodePtr != NULL)
	{
		returnedItem = nodePtr->getItem();
		isSuccessful = true;
	}
	return isSuccessful;
}
//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTreePlate<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	// allocate the new node
	if (nodePtr == NULL)
		return newNodePtr;
	BinaryNode<ItemType> *tempPtr;

	if (newNodePtr->getItem() <= nodePtr->getItem())
	{
		tempPtr = _insert(nodePtr->getLeftPtr(), newNodePtr);
		nodePtr->setLeftPtr(tempPtr);
	}
	else
	{
		tempPtr = _insert(nodePtr->getRightPtr(), newNodePtr);
		nodePtr->setRightPtr(tempPtr);
	}
	return nodePtr;

}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTreePlate<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target,
	bool & success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTreePlate<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTreePlate<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTreePlate<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	BinaryNode<ItemType>* retPtr = NULL;

	if (nodePtr != NULL)
	{
		if (nodePtr->getItem() == target)
		{
			retPtr = nodePtr;
		}
		else
		{
			if (target < nodePtr->getItem())
				retPtr = findNode(nodePtr->getLeftPtr(), target);
			else
				retPtr = findNode(nodePtr->getRightPtr(), target);
		}
	}
	return retPtr;
}

#endif


