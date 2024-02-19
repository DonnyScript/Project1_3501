#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"


class AVLTree : BinarySearchTree {
private:

public:
    int setAVLHeight(TreeNode* Current);
    int setNodeBalance(TreeNode* Current);


};















#endif 
