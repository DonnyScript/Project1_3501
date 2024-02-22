#include "AVL_Tree.h"

using namespace std;

int main() {
	string initialTree, actionFile, testTitle;
	cout << "Type name of initial tree file: ";
	getline(cin, initialTree);
	/* 
	cout << "Type name of Action File : ";
	getline(cin, actionFile);
	*/
	cout << "What is the title of this test: ";
	getline(cin, testTitle);
	removeWhitespaceAtEnd(initialTree);
	//removeWhitespaceAtEnd(actionFile);
	initialTree += ".txt";
	//actionFile += ".txt";
	vector<int> nodeValues;
	vector<string> actionValues;
	AVLTree AVL_DATA;
	AVL_DATA.setTitle(testTitle);

	nodeValues = AVL_DATA.readAndCheckInput(initialTree);
	//actionValues = AVL_DATA.readandCheckAction(actionFile);

	for (int val : nodeValues) {
		AVL_DATA.actionCT[0]++;
		AVL_DATA.insert(val,0);
	}

	return 0;
}