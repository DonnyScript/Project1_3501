#include "AVL_Tree.h"
using namespace std; 

int AVLTree::getHeight(TreeNode* node) {
	return (node == nullptr) ? 0 : node->height;
}

int AVLTree::getBalance(TreeNode* node) {
	return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

int AVLTree::updateHeight(TreeNode* node) {
	if (node == nullptr) {
		return 0;
	}
	int leftHeight = (node->left != nullptr) ? node->left->height : 0;
	int rightHeight = (node->right != nullptr) ? node->right->height : 0;
	return 1 + max(leftHeight, rightHeight);
}

TreeNode* AVLTree::rotate(TreeNode* Current, bool isLeft) {
	operationCtr++;
	TreeNode* B = isLeft ? Current->right : Current->left;
	if (B == nullptr) {
		return Current;
	}
	TreeNode* Y = isLeft ? B->left : B->right;

	if (isLeft) {
		B->left = Current;
		Current->right = Y;
	}
	else {
		B->right = Current;
		Current->left = Y;
	}

	
	Current->height = updateHeight(Current);
	B->height = updateHeight(B);

	return B;
}

TreeNode* AVLTree::leftRotate(TreeNode* Current) {
	return rotate(Current, true);
}

TreeNode* AVLTree::rightRotate(TreeNode* Current) {
	return rotate(Current, false);
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
		return Current;
	}

	Current->height = updateHeight(Current);
	Current->balance = getBalance(Current);

	if (Current->left != nullptr && Current->balance > 1 && value < Current->left->data) {
		return rightRotate(Current);
	}
	if (Current->right != nullptr && Current->balance < -1 && value > Current->right->data) {
		return leftRotate(Current);
	}
	if (Current->left != nullptr && Current->balance > 1 && value > Current->left->data) {
		Current->left = leftRotate(Current->left);
		return rightRotate(Current);
	}
	if (Current->right != nullptr && Current->balance < -1 && value < Current->right->data) {
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
