#include <iostream>
using namespace std;
#include "AVL.h"

int main()
{
	AVL<int, int> tree; //the key and value both are of type int. (both can be of any type. They 
						//can also be of different type from each other)

	for (int i = 1; i <= 500; i++)
		tree.insert(i, i);
	
	for (int i = -1; i > -500; i--)
		tree.insert(i, i);

	for (int i = 1000; i > 500; i--)
		tree.insert(i, i);

	for (int i = -1000; i <=-500; i++)
	tree.insert(i, i);


	for (int i = -1; i >= -1000; i--)
		tree.deleteKey(i);


	AVL<int, int> tree1(tree);

	tree1.inorderPrintKeys();
	cout << endl << endl;
	cout << "Tree1 Height: " << tree1.getHeight() << endl;
	cout << "Tree1 Total Nodes: " << tree1.length() << endl;
	int *val = tree1.search(100);

	if (val != nullptr)
	{
		cout << "Key= 100 found" << endl;
	}

	val = tree1.search(-151);
	if (val == nullptr)
	{
		cout << "Key= -151 not found" << endl;
	}

	system("pause");
}

