#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "binary_search_tree.h"


class AVLTree : public BinarySearchTree {
private:
    int getHeight(TreeNode* node);
    int getBalance(TreeNode* node);
    int updateHeight(TreeNode* node);
    TreeNode* rotate(TreeNode* Current, bool isLeft);
    TreeNode* insertRotateRecursive(TreeNode* Current, int value, int ctr);
    TreeNode* leftRotate(TreeNode* Current);
    TreeNode* rightRotate(TreeNode* Current);

public:

    void insert(int value, int ctr);

};

#endif 
