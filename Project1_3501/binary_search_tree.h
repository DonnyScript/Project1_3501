#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdexcept>
using namespace std;

void removeWhitespaceAtEnd(string& filename);

struct TreeNode {
    int data;
    int twin = 1;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    string testTitle;
    int operationCtr;
    int opTotal;
    TreeNode* insertRecursive(TreeNode* root, int value,int ctr);
    TreeNode* deleteNode(TreeNode* root, int key);
    void displayTree(TreeNode* root, int depth);
    bool searchRec(TreeNode* root, int value);

public:
    TreeNode* root;
    int getOpTotal();
    int actionCT[4];
    int getOpCount();
    void incOpCnt();
    void resetOpCount();
    BinarySearchTree();
    void deleteValue(int value);
    void searchValue(int value);
    int treeHeight(TreeNode* root);
    void insert(int value,int ctr);
    void displayTree();
    void setTitle(string name);
    vector<string> readandCheckAction(string filename);
    vector<int> readAndCheckInput(string filename);
};

class PreformAction : public BinarySearchTree {
private:
    string keys[3] = { "I","D","S" };
    string testTitle;
public:

    void setTitle(string name);
    void actOnTree(BinarySearchTree &TreeNode, vector<string> data);
    void displayReportSummary(BinarySearchTree& TreeNode, vector<string> data);
};

#endif