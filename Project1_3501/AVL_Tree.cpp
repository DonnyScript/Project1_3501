#include "AVL_Tree.h"
using namespace std; 

TreeNode* AVLTree::insertRecursive(TreeNode* root, int value, int ctr){
	operationCtr++;
	actionCT[ctr]++;
	if (root == nullptr) {
		return new TreeNode(value);
	}
	else if (root->data == value) {
		root->twin++;
	}

	if (value < root->data) {
		root->left = insertRecursive(root->left, value, ctr);
	}
	else if (value > root->data) {
		root->right = insertRecursive(root->right, value, ctr);
	}

	setAVLHeight(root);
	setNodeBalance(root);
	
	return root;
}

TreeNode* AVLTree::insertRotateRecursive(TreeNode* Current, int value, int ctr){
	if (root == nullptr) {
		return new TreeNode(value);
	}
	else if (value < Current->data) {
		Current->left = insertRotateRecursive(Current->left, value, ctr);
	}
	else if (value > Current->data) {
		Current->right = insertRotateRecursive(Current->right, value, ctr);
	}

	Current->height = 1 + max(Current->left->height, Current->right->height);
	int balanceFactor = Current->balance; 


	return Current;
}

int AVLTree::setAVLHeight(TreeNode* Current){
	if (Current == nullptr) {
		return 0;
	}

	int leftheight = setAVLHeight(Current->left);
	int rightHeight = setAVLHeight(Current->right);
	Current->height = 1 + max(leftheight, rightHeight);
	return(1 + max(leftheight, rightHeight));
}

void AVLTree::setNodeBalance(TreeNode* Current){
	if (Current == nullptr) {
		return;
	}

	int leftNodeHeight = 0, rightNodeHeight = 0;

	if (Current->left != nullptr) {
		leftNodeHeight = Current->left->height;
	}
	if (Current->right != nullptr) {
		rightNodeHeight = Current->right->height;
	}
	Current->balance = leftNodeHeight - rightNodeHeight;

	setNodeBalance(Current->left);
	setNodeBalance(Current->right);

	return;
}

void AVLTree::insert(int value, int ctr){
	root = insertRecursive(root, value, ctr);
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);

	if (outputFile.is_open()) {
		cout << "Inserting: " << value << endl;
		outputFile << "Inserting: " << value << endl;

		displayTree(root, 0);

		cout << "Tree Depth: " << treeHeight(root) << endl;
		cout << "Operations: " << getOpCount() << endl;
		outputFile << "Operations: " << getOpCount() << endl;
		outputFile << "Tree Depth: " << treeHeight(root) << endl;
		resetOpCount();
		cout << "_____________________________________________________________" << endl;
		outputFile << "_____________________________________________________________" << endl;
		cout << endl;
		outputFile << endl;
	}
	outputFile.close();
}

TreeNode* AVLTree::leftRotate(TreeNode* Current){
	TreeNode* B = Current->right;
	TreeNode* Y = B->left;

	B->left = Current;
	Current->right = Y;
	
	Current->height = 1 + max(Current->left->height, Current->right->height);
	B->height = 1 + max(B->left->height, B->right->height);

	return B;
}

TreeNode* AVLTree::rightRotate(TreeNode* Current){
	TreeNode* A = Current->left;
	TreeNode* Y = A->right;

	A->right = Current;
	Current->left = Y;

	Current->height = 1 + max(Current->left->height, Current->right->height);
	A->height = 1 + max(A->left->height, A->right->height);

	return A;
}
