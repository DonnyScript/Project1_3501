#include "AVL_Tree.h"
using namespace std; 

int AVLTree::getHeight(TreeNode* node) {
	operationCtr+=2;
	return (node == nullptr) ? 0 : node->height;
}

int AVLTree::getBalance(TreeNode* node) {
	operationCtr+=2;
	return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

int AVLTree::updateHeight(TreeNode* node) {
	operationCtr += 4;
	if (node == nullptr) {
		return 0;
	}
	int leftHeight = (node->left != nullptr) ? node->left->height : 0;
	int rightHeight = (node->right != nullptr) ? node->right->height : 0;
	return 1 + max(leftHeight, rightHeight);
}

TreeNode* AVLTree::getMinNode(TreeNode* Current){
	if (!Current || !Current->left) {
		return Current;
	}
	return getMinNode(Current->left);
}

TreeNode* AVLTree::rotate(TreeNode* Current, bool isLeft) {
	operationCtr+= 4;
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

TreeNode* AVLTree::deleteRotate(TreeNode* Current, int value) {
	operationCtr++;
	if (Current == nullptr) {
		return nullptr;
	}
	else if (Current->twin > 1 && Current->data == value) {
		Current->twin--;
		return Current;
	}
	if (value < Current->data) {
		Current->left = deleteRotate(Current->left, value);
	}
	else if (value > Current->data) {
		Current->right = deleteRotate(Current->right, value);
	}
	else {
		if (Current->twin > 1 && Current->data == value) {
			return Current;
		}
		else if (Current->left == nullptr) {
			TreeNode* temp = Current->right;
			delete Current;
			return temp;
		}
		else if (Current->right == nullptr) {
			TreeNode* temp = Current->left;
			delete Current;
			return temp;
		}

		TreeNode* temp = Current->right;
		getMinNode(Current);
		Current->data = temp->data;
		Current->twin = temp->twin;
		if (Current->right->twin) {
			Current->right->twin = 1;
		}
		Current->right = deleteRotate(Current->right, temp->data);
	}

	Current->height = updateHeight(Current);
	Current->balance = getBalance(Current);

	if (Current->balance > 1 && getBalance(Current->left) >= 0) {
		return rotate(Current, false);
	}
	if (Current->balance < -1 && getBalance(Current->right) <= 0) {
		return rotate(Current, true);
	}
	if (Current->balance > 1 && getBalance(Current->left) < 0) {
		Current->left = rotate(Current->left, true);
		return rotate(Current, false);
	}
	if (Current->balance < -1 && getBalance(Current->right) > 0) {
		Current->right = rotate(Current->right, false);
		return rotate(Current, true);
	}
	return Current;
}



TreeNode* AVLTree::insertRotateRecursive(TreeNode* Current, int value, int ctr) {
	operationCtr++;
	if (Current == nullptr) {
		return new TreeNode(value);
	}
	else if (value < Current->data) {
		Current->left = insertRotateRecursive(Current->left, value, ctr);
	}
	else if (value > Current->data) {
		Current->right = insertRotateRecursive(Current->right, value, ctr);
	}
	else if (Current->data == value) {
		Current->twin++;
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

void AVLTree::deleteRotate(int value) {
	root = deleteRotate(root, value);
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);
	if (outputFile.is_open()) {
		cout << "Deleting: " << value << endl;
		outputFile << "Deleting: " << value << endl;

		displayTree(root, 0);

		cout << "Tree Depth: " << treeHeight(root) << endl;
		cout << "Operations: " << getOpCount() << endl;
		outputFile << "Operations: " << getOpCount() << endl;
		outputFile << "Tree Depth: " << treeHeight(root) << endl;
		actionCT[3] += getOpCount();
		resetOpCount();
		cout << "_____________________________________________________________" << endl;
		outputFile << "_____________________________________________________________" << endl;
		cout << endl;
		outputFile << endl;
	}
	outputFile.close();
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
		actionCT[ctr] += getOpCount();
		resetOpCount();
		cout << "_____________________________________________________________" << endl;
		outputFile << "_____________________________________________________________" << endl;
		cout << endl;
		outputFile << endl;
	}
	outputFile.close();
}