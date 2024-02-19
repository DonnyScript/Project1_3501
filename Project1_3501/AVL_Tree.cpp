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
