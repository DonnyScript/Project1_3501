#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"


class AVLTree : public BinarySearchTree {
private:
    TreeNode* insertRecursive(TreeNode* root, int value, int ctr);
    TreeNode* insertRotateRecursive(TreeNode* Current, int value, int ctr);
public:
    int setAVLHeight(TreeNode* Current);
    void setNodeBalance(TreeNode* Current);
    void insert(int value, int ctr);
    TreeNode* leftRotate(TreeNode* Current);
    TreeNode* rightRotate(TreeNode* Current);

};















#endif 
