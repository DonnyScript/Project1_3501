#include "AVL_Tree.h"
using namespace std; 

int AVLTree::getHeight(TreeNode* node) {
	operationCtr++;
	if (node == nullptr) {
		return 0;
	}
	return node->height;
}

int AVLTree::getBalance(TreeNode* node) {
	operationCtr++;
	if (node == nullptr) {
		return 0;
	}
	return getHeight(node->left) - getHeight(node->right);
}

TreeNode* AVLTree::leftRotate(TreeNode* Current) {
	operationCtr++;
	TreeNode* B = Current->right;
	TreeNode* Y = B->left;

	B->left = Current;
	Current->right = Y;

	Current->height = 1 + max(Current->left->height, Current->right->height);
	B->height = 1 + max(B->left->height, B->right->height);

	return B;
}

TreeNode* AVLTree::rightRotate(TreeNode* Current) {
	operationCtr++;
	TreeNode* B = Current->left;
	TreeNode* Y = B->right;

	B->right = Current;
	Current->left = Y;

	Current->height = 1 + max(Current->left->height, Current->right->height);
	B->height = 1 + max(B->left->height, B->right->height);

	return B;
}

TreeNode* AVLTree::insertRotateRecursive(TreeNode* Current, int value, int ctr) {
	operationCtr++;
	actionCT[ctr]++;
	if (Current == nullptr) {
		return new TreeNode(value);
	}
	else if (value < Current->data) {
		Current->left = insertRotateRecursive(Current->left, value, ctr);
	}
	else if (value > Current->data) {
		Current->right = insertRotateRecursive(Current->right, value, ctr);
	}
	else if (root->data == value) {
		root->twin++;
	}

	Current->height = 1 + max(getHeight(Current->left), getHeight(Current->right));
	Current->balance = getBalance(Current);

	if (Current->balance > 1 && value < Current->left->data) {
		return rightRotate(Current);
	}
	if (Current->balance < -1 && value > Current->right->data) {
		return leftRotate(Current);
	}
	if (Current->balance > 1 && value > Current->left->data) {
		Current->left = leftRotate(Current->left);
		return rightRotate(Current);
	}
	if (Current->balance < -1 && value < Current->right->data) {
		Current->right = rightRotate(Current->right);
		return leftRotate(Current);
	}

	return Current;
}

void AVLTree::insert(int value, int ctr){
	root = insertRotateRecursive(root, value, ctr);
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
