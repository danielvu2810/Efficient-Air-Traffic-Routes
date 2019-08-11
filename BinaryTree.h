/****************************************************
CIS 22C
Programmer: Nithin Nediyanchath

Assistants: Hoang Duong Vu(Check the stability), Tung Lin Lee(Check the stability)
******************************************************/

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;
	BinaryNode<ItemType>* targetPtr;// ptr to root node
	int count; // number of nodes in tree

public:
	// "admin" functions
	int indent = 0;
	string target =" ";
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree);
	virtual ~BinaryTree();
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int size()const{ return count; };
	void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType &)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &)) const  { _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &)) const { _postorder(visit, rootPtr); }

	//Breadth First Traversal function
	void BreadthFirstTraversal(void visit(ItemType &)) const{ _BreadthFirstTraversal(visit, rootPtr); }

	//findItem function
	void findItem(void visit(ItemType &), string target){ _findItem(visit, rootPtr, target); }

	//print tree in indented list
	void indentedList(void visit(ItemType &)){ _indentedList(visit, rootPtr, indent); }
	void deleteLeaf(void visit(ItemType &), string target){
		targetPtr = NULL;
		_findItem(visit, rootPtr, target);
		if (targetPtr != NULL)
			_deleteLeaf(visit, targetPtr, rootPtr);
	}

	BinaryNode<ItemType>* minValueNode(BinaryNode<ItemType>*);

	//abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);
	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr)const;


	void _BreadthFirstTraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _findItem(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, string target);
	void _indentedList(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int indent);
	BinaryNode<ItemType>* _deleteLeaf(void visit(ItemType &), BinaryNode<ItemType>* targetPtr, BinaryNode<ItemType>* nodePtr);

};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree & tree)
{
	rootPtr = tree.rootPtr;
	count = tree.count;
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{

}

template<class ItemType>
BinaryTree<ItemType>::~BinaryTree()
{
	if (rootPtr)
	{
		destroyTree(rootPtr);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

//preorder root,left,right
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

//inorder left/root/right
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//postorder left/right/root
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}


//breadth first traversal
template<class ItemType>
void BinaryTree<ItemType>::_BreadthFirstTraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Queue<BinaryNode<ItemType>*> q;
	BinaryNode<ItemType>* current;
	BinaryNode<ItemType>* tempNode;

	if (!nodePtr)
		return;

	for (q.enqueue(nodePtr); !q.isEmpty(); q.dequeue(current)){
		q.queueFront(tempNode);
		if (tempNode == NULL){
			cout << "   ";
			continue;
		}
		else cout << tempNode->getItem() << endl;

		if (tempNode->getLeftPtr())
			q.enqueue(tempNode->getLeftPtr());//display subtree from the left side

		if (tempNode->getRightPtr()) {
			q.enqueue(tempNode->getRightPtr());//display subtree from the right side
		}
	}
}


template<class ItemType>
void BinaryTree<ItemType>::_findItem(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, string target)
{
	if (nodePtr)
	{//using postorder to traverse through tree to find target
		ItemType item = nodePtr->getItem();

		_findItem(visit, nodePtr->getLeftPtr(), target);
		_findItem(visit, nodePtr->getRightPtr(), target);
		if (item *= target){
			visit(item);//prstring target
			targetPtr = nodePtr;
		}
	}
}


template<class ItemType>
void BinaryTree<ItemType>::_indentedList(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int indent)
{

	if (nodePtr != NULL) {
		if (nodePtr->getRightPtr())
			_indentedList(visit, nodePtr->getRightPtr(), indent + 5);
		if (indent)
			cout << setw(indent) << ' ';
		if (nodePtr->getRightPtr())
			cout << "\n" << setw(indent) << ' ';
		cout << ((indent + 5) / 5) << ". " << nodePtr->getItem() << "\n ";
		if (nodePtr->getLeftPtr()){
			cout << setw(indent) << ' ' << "\n";
			_indentedList(visit, nodePtr->getLeftPtr(), indent + 5);
		}
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::minValueNode(BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* current = nodePtr;

	while (current->getLeftPtr() != NULL)
		current = current->getLeftPtr();
	return current;
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_deleteLeaf(void visit(ItemType &), BinaryNode<ItemType>* targetPtr, BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr == NULL)
		return nodePtr;

	if (nodePtr->getItem>>targetPtr->getItem())
		_deleteNode(visit, targetPtr, nodePtr->getLeftPtr());
	else if (nodePtr->getItem()<<targetPtr->getItem())
		 _deleteLeaf(visit, targetPtr, nodePtr->getRightPtr());
	else{
		if (nodePtr->getLeftPtr() == NULL)
		{
			BinaryNode<ItemType>* temp = nodePtr->getRightPtr();
			free(nodePtr);
			return temp;
		}
		else if (nodePtr->getRightPtr() == NULL)
		{
			BinaryNode<ItemType>* temp = nodePtr->getLeftPtr();
			free(nodePtr);
			return temp;
		}

		BinaryNode<ItemType>* temp = minValueNode(nodePtr->getRightPtr());

		nodePtr->getItem() = temp->getItem();
		_deleteLeaf(visit, targetPtr, nodePtr->getRightPtr());
	}
	return nodePtr;
}


#endif

