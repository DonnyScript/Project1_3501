#include "AVL_Tree.h"
using namespace std; 

int AVLTree::setAVLHeight(TreeNode* Current){
	if (Current == nullptr) {
		return 0;
	}

	int leftheight = setAVLHeight(Current->left);
	int rightHeight = setAVLHeight(Current->right);
	Current->height = 1 + max(leftheight, rightHeight);
	return(1 + max(leftheight, rightHeight));
}

int AVLTree::setNodeBalance(TreeNode* Current){
	if (Current == nullptr) {
		return 0;
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

	return 0;
}
