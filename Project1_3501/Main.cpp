#include "AVL_Tree.h"

using namespace std;

int main() {
	string initialTree, actionFile, testTitle;
	cout << "Type name of initial tree file: ";
	getline(cin, initialTree);
	cout << "Type name of Action File : ";
	getline(cin, actionFile);
	cout << "What is the title of this test: ";
	getline(cin, testTitle);
	removeWhitespaceAtEnd(initialTree);
	removeWhitespaceAtEnd(actionFile);
	initialTree += ".txt";
	actionFile += ".txt";
	vector<int> nodeValues;
	vector<string> actionValues;
	BinarySearchTree bst;
	PreformAction actOnFile;
	AVLTree AVLTree;
	actOnFile.setTitle(testTitle);
	bst.setTitle(testTitle);
	AVLTree.setTitle(testTitle);

	nodeValues = AVLTree.readAndCheckInput(initialTree);
	actionValues = AVLTree.readandCheckAction(actionFile);

	for (int val : nodeValues) {
		AVLTree.insert(val,0);
	}

	return 0;
}