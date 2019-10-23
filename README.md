# AVL-Tree
AVL tree is a self-balancing BST. The height of left subtree and right subtree of a node in AVL can differ at most by 1.

The following public meber functions are supported in the AVL class implementation: 
(these public member functions make use of other private recursive member functions)

-> AVL() :  default constructor

-> AVL(AVL<k, v> const& that) :  copy constructor

-> int getHeight() const :   returns the height of the AVL tree

-> void insert(k const  key, v const value) :   inserts a value with the specific key by creating a new node. if the key already exists, it    simply overwrites the value

-> v* search(k const key) const :   returns a pointer to the value of the node containining the key.

-> void inorderPrintKeys() const :   print keys in inorder fashion.

-> void deleteAll()     :   deletes all nodes of the AVL Tree.

-> void deleteKey(k key) :   deletes the node containing the given key.

-> int length() const  :  returns total number of nodes of the AVL tree (total number of nodes is equal to the total number of keys.)

-> ~AVL()  :  Destructor


The insert and deleteKey methods follow the same logic for balancing as stated on geeksforgeeks:

Balancing logic for insert: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
Balancing logic for delete: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
