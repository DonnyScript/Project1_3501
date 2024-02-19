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
	AVLTree Test;
	actOnFile.setTitle(testTitle);
	bst.setTitle(testTitle);

	actionValues = bst.readandCheckAction(actionFile);
	nodeValues = bst.readAndCheckInput(initialTree);

	for (int val : nodeValues) {
		bst.actionCT[0]++;
		bst.insert(val,0);
	}
	Test.setAVLHeight(bst.root);

	return 0;
}