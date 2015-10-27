/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */


#include <queue>

template <typename T>
int BinaryTree<T>::height() const
{	
	// Call recursive helper function on root
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	mirror(root);
	// your code here
}
template <typename T>
void BinaryTree<T>:: mirror(Node * subRoot)
{	if(subRoot!=NULL){
		Node* temp=NULL;
		temp = subRoot->left;
		subRoot->left = subRoot->right;
		subRoot->right = temp;
		mirror(subRoot->left);
		mirror(subRoot->right);
	}
}

/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{	/*queue<T> q;
	q = isOrdered(root);
	while(!q.empty()){
		T a = q.front();
		q.pop();
		T b = q.front();
		if(a>=b) return false;
		if(q.size() ==1) return true;
	}
	return true;*/
	return isOrdered(root);
}

template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const 
{	
	if (subRoot == NULL) return true;

	if (subRoot->left !=NULL && (subRoot->left->elem > subRoot->elem)) return false;

	if (subRoot->right !=NULL && (subRoot->right->elem < subRoot->elem)) return false;

	if (!isOrdered(subRoot->right) && !isOrdered(subRoot->left)) return false;

	return true;
	/*queue<T> Q;
	if( subRoot != NULL){
	isOrdered(subRoot->left);
	T c = subRoot->elem;
	Q.push(c);
	isOrdered(subRoot->right);
	}
	return Q;*/
}

/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
	T* thePaths = new T[500];
    int theLength = 0;
    printPaths(theLength, root, thePaths);
    // your code here
}

/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
 template <typename T>
void BinaryTree<T>::printPaths(int length, Node* subRoot, T* &paths) const {

	if (subRoot == NULL) return;

	paths[length] = subRoot->elem;

	length = length+1;

	if (subRoot->left== NULL && subRoot->right == NULL) { 
		cout << "Path: ";


		for (int i = 0; i < length; i++) {
			cout<<paths[i]<< " ";

		}
		cout <<endl;
	}

	printPaths(length, subRoot->left, paths);
	printPaths(length, subRoot->right, paths);


}
 
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    int sum=0;
	queue<int> Q;
	sumDistances(root, 0, 0, Q);
	while(!Q.empty())
	{
		int a=Q.front();
		sum=sum+a;
		Q.pop();
	}
	return sum;
}

template <typename T>
void BinaryTree<T>::sumDistances(const Node * subRoot, int len,int distance, queue<int> &q)const
{
	if(subRoot==NULL) return;
	distance=len;
	len++;

	q.push(distance);
	sumDistances(subRoot->left, len, distance, q);
	sumDistances(subRoot->right, len, distance, q);

}
