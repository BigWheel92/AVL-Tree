#pragma once

#include <iostream>
using namespace std;
#include <algorithm>


template <typename k, typename v>
struct TNode
{
	k key;
	v value;
	TNode<k, v>* leftChild;
	TNode<k, v>* rightChild;
	int height;

	TNode()
	{
		leftChild = rightChild = nullptr;
		height = 0;
	}

	bool isLeafNode() const
	{
		return !(leftChild || rightChild);
	}

};

template <typename k, typename v>
class AVL
{
private:
	TNode<k, v>* root;

	int getHeight(TNode<k, v> const* root) const
	{
		if (root == nullptr)
			return -1;

		if	(root->isLeafNode())
			return 0;

		return root->height;

	}

	void updateHeight(TNode<k, v>* root) const
	{
		if (!root->isLeafNode())
			root->height = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
		else root->height = 0;
	}



	int length(TNode<k, v> const* node) const
	{
		if (node == nullptr)
			return 0;

		else return (1 + length(node->leftChild) + length(node->rightChild));
	}

	void copy(TNode<k, v>*& n1, TNode<k, v> const* const& n2)
	{
		if (n2 == nullptr)
		{
			n1 = nullptr;
			return;
		}

		n1 = new TNode<k, v>;
		n1->key = n2->key;
		n1->value = n2->value;
		n1->height = n2->height;

		//recursively deep copying the left subtree and the right subtree.
		copy(n1->leftChild, n2->leftChild);
		copy(n1->rightChild, n2->rightChild);

	}

	TNode<k, v>* doubleRightLeftRotation(TNode<k, v>* root)
	{
		TNode<k, v>* z = root;

		TNode<k, v>* y = z->rightChild;


		z->rightChild = this->singleRightRotation(y);

		updateHeight(z);

		z = this->singleLeftRotation(z);


		root = z;
		return root;
	}

	TNode<k, v>* doubleLeftRightRotation(TNode<k, v>* root)
	{
		TNode<k, v>* z = root;
		TNode<k, v>* y = z->leftChild;


		z->leftChild = this->singleLeftRotation(y);

		updateHeight(z);

		//z is now x
		z = this->singleRightRotation(z);

		root = z;
		return root;
	}

	TNode<k, v>* singleRightRotation(TNode<k, v>* root)
	{

		TNode<k, v>* z = root;
		TNode<k, v>* y = z->leftChild;


		TNode<k, v>* T3 = y->rightChild;

		y->rightChild = z;
		z->leftChild = T3;

		updateHeight(z);
		updateHeight(y);

		root = y;
		return root;
	}


	TNode<k, v>* singleLeftRotation(TNode<k, v>* root)
	{

		TNode<k, v>* z = root;
		TNode<k, v>* y = z->rightChild;


		TNode<k, v>* T2 = y->leftChild;



		y->leftChild = z;
		z->rightChild = T2;


		updateHeight(z);
		updateHeight(y);

		root = y;
		return root;
	}


	int getBalanceFactor(TNode<k, v> const* root) const
	{
		if (!root || root->isLeafNode())
			return 0;

		return getHeight(root->leftChild) - getHeight(root->rightChild);
	}


	TNode<k, v>* insert(TNode<k, v>* root, k key, v value)
	{
		if (root == nullptr)
		{
			root = new TNode<k, v>();
			root->key = key;
			root->value = value;
			root->height = 0;
			return root;

		}

		else if (key > root->key)
		{
			root->rightChild = insert(root->rightChild, key, value);

		} //end of key>root->key case

		else if (key < root->key)
		{
			root->leftChild = insert(root->leftChild, key, value);

		} //end of key<root->key case

		else  //duplicate key, so update the value
		{
			root->value = value;
		}

		updateHeight(root);

		//left left case
		if (getBalanceFactor(root) > 1 && key < root->leftChild->key)
		{

			root = this->singleRightRotation(root);
		}

		//right right case
		else if (getBalanceFactor(root) < -1 && key > root->rightChild->key)
		{
			root = this->singleLeftRotation(root);
		}

		//left right case
		else if (getBalanceFactor(root) > 1 && key > root->leftChild->key)
		{
			root = this->doubleLeftRightRotation(root);
		}

		//right left case
		else if (getBalanceFactor(root) < -1 && key < root->rightChild->key)
		{
			root = this->doubleRightLeftRotation(root);
		}

		return root;

	}


	void inorderPrintKeys(TNode<k, v> const* node) const
	{
		if (node == nullptr)
			return;

		inorderPrintKeys(node->leftChild);

		cout << node->key << ",";

		inorderPrintKeys(node->rightChild);
	}

	v* search(TNode<k, v>* n, k const key) const
	{
		if (n == nullptr)
			return nullptr;

		if (n->key == key)
			return &n->value;

		else if (key < n->key)
			return search(n->leftChild, key);

		else return search(n->rightChild, key);

	}

	void deleteAll(TNode<k, v>* n)
	{
		if (n == nullptr)
			return;

		deleteAll(n->leftChild);
		deleteAll(n->rightChild);
		delete n;
	}


	TNode<k, v>* deleteKey(TNode<k, v>* root, k const key)
	{
		//the key to delete does not exist in the tree.
		if (root == nullptr)
			return nullptr;

		else if (key > root->key)
		{	//move to the right subtree
			root->rightChild = deleteKey(root->rightChild, key);

		}

		else if (key < root->key)
		{	//move to the left subtree
			root->leftChild = deleteKey(root->leftChild, key);
		}

		else //root node (the passed parameter) has the key that we need to delete
		{

			//case 1: the node to delete is the leaf node.
			if (root->isLeafNode() == true)
			{
				delete root;
				return nullptr;
			}//end of case 1

			//case 2: one of the subtrees of current is nullptr;
			else if (root->leftChild == nullptr || root->rightChild == nullptr)
			{
				if (root->leftChild == nullptr)
				{
					TNode<k, v>* nodeToDelete = root;
					root = root->rightChild;
					delete nodeToDelete;

				}

				else //right child is nullptr, but left child is not
				{
					TNode<k, v>* nodeToDelete = root;
					root = root->leftChild;
					delete nodeToDelete;

				}

			}//end of case 2

			else  //case 3: none of the subtrees of node to delete is nullptr.
			{
				TNode<k, v>* newNodeToDelete = root->rightChild;

				while (newNodeToDelete->leftChild != nullptr)
				{
					newNodeToDelete = newNodeToDelete->leftChild;
				}

				root->key = newNodeToDelete->key;
				root->value = newNodeToDelete->value;

				//in this new recursive call, case 0 and 3 will never exist. Only case 1 or case 2 will exist.
				root->rightChild = deleteKey(root->rightChild, root->key);
			}//end of case 3.
		}

		//update root height
		updateHeight(root);

		//balance the root.

		//left left case
		if (getBalanceFactor(root) > 1 && getBalanceFactor(root->leftChild) >=0)
		{

			root = this->singleRightRotation(root);
		}

		//right right case
		else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->rightChild) <=0)
		{
			root = this->singleLeftRotation(root);
		}

		//left right case
		else if (getBalanceFactor(root) > 1 && getBalanceFactor(root->leftChild) < 0)
		{
			root = this->doubleLeftRightRotation(root);
		}

		//right left case
		else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->rightChild) > 0)
		{
			root = this->doubleRightLeftRotation(root);
		}

		return root;
	}



public:
	AVL()
	{
		this->root = nullptr;
	}

	AVL(AVL<k, v> const& that)
	{
		if (that.root == nullptr)
		{
			this->root = nullptr;
			return;
		}

		//passed the node of this tree and the node of that tree by reference and recursively deep copies.
		copy(this->root, that.root);
	}


	int getHeight() const
	{
		if (root)
			return root->height;
		else return 0;
	}

	void insert(k const  key, v const value)
	{

		root = insert(this->root, key, value);
	}


	v* search(k const key) const
	{
		return search(this->root, key);
	}

	void inorderPrintKeys() const
	{

		this->inorderPrintKeys(this->root);
	}

	void deleteAll()
	{
		deleteAll(this->root);
		this->root = nullptr;
	}

	void deleteKey(k const key)
	{
		this->root = deleteKey(this->root, key);
	}

	int length() const
	{
		return length(this->root);
	}

	~AVL()
	{
		deleteAll();
	}


};
