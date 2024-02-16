#include "binary_search_tree.h"
using namespace std;

void removeWhitespaceAtEnd(string &filename) {
	filename.erase(find_if(filename.rbegin(), filename.rend(), [](int ch) {
		return !isspace(ch);
		}).base(), filename.end());
}

vector<int> BinarySearchTree:: readAndCheckInput(string filename) {
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);
	vector<int> values;
	int num;
	string tempData;

	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cout << "Unable to open file: " + filename << endl;
		outputFile << "Unable to open file: " + filename << endl;
		return values;
	}

	if (inputFile.peek() == ifstream::traits_type::eof()) {
		cout << "Input file is empty" << endl;
		outputFile << "Input file is empty" << endl;
		return values;
	}

	while (inputFile >> tempData) {
		try {
			num = stoi(tempData);
		}
		catch (const invalid_argument& ia) {
			cout << tempData << " - is not a valid input " << endl;
			outputFile << tempData << " - is not a valid input " << endl;
			cout << "_____________________________________________________________" << endl;
			outputFile << "_____________________________________________________________" << endl;
			continue;
		}
		values.push_back(num);
	}

		outputFile.close();
		inputFile.close();

	return values;
}

vector<string> BinarySearchTree::readandCheckAction(string filename) {
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);
	vector<string> values;
	string data;
	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		outputFile << "Unable to open file " + filename << endl;
		cout << "Unable to open file " + filename << endl;
		return values;
	}

	if (inputFile.peek() == ifstream::traits_type::eof()) {
		outputFile << "Action file is empty" << endl;
		cout << "Action file is empty" << endl;
		return values;
	}

		while (inputFile >> data) {
		values.push_back(data);
		}

		outputFile.close();
		inputFile.close();

	return values;
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* root, int value, int ctr) {
	operationCtr++;
	actionCT[ctr]++;
	if (root == nullptr) {
		return new TreeNode(value);
	}
	else if (root->data == value) {
		root->twin++;
	}

	if (value < root->data) {
		root->left = insertRecursive(root->left, value, ctr);
	}
	else if (value > root->data) {
		root->right = insertRecursive(root->right, value, ctr);
	}

	return root;
}

TreeNode* BinarySearchTree::deleteNode(TreeNode* root, int value) {
	operationCtr++;
	actionCT[3]++;
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);
	if (root == nullptr) {
		return nullptr;
	}
	else if (root->twin > 1 && root->data == value) {
		root->twin--;
		return root;
	}

	if (value < root->data) {
		root->left = deleteNode(root->left, value);
	}
	else if (value > root->data) {
		root->right = deleteNode(root->right, value);
	}
	else {
		if (root->twin > 1 && root->data == value) {
			return root;
		}
		else if (root->left == nullptr) {
			TreeNode* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == nullptr) {
			TreeNode* temp = root->left;
			delete root;
			return temp;
		}

		TreeNode* current = root->right;
		while (current && current->left != nullptr) {
			operationCtr++;
			actionCT[3]++;
			current = current->left;
		}
		root->data = current->data;
		root->twin = current->twin;
		if (root->right->twin) {
			root->right->twin = 1;
		}
		root->right = deleteNode(root->right, current->data);
	}
	return root;
}

void BinarySearchTree::displayTree(TreeNode* root, int depth) {
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);

	if (root != nullptr) {
		displayTree(root->right, depth + 1);
		for (int i = 0; i < depth; ++i) {
			cout << "   ";
			outputFile << "   ";
		}
		if (root->twin > 1) {
			cout << root->data << "(" << root->twin << ")" << endl;
			outputFile << root->data << "(" << root->twin << ")" << endl;
		}
		else
		{
			cout << root->data << endl;
			outputFile << root->data << endl;
		}

		displayTree(root->left, depth + 1);
	}
	outputFile.close();

}

void BinarySearchTree::insert(int value,int ctr) {
	root = insertRecursive(root, value,ctr);
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);

	if (outputFile.is_open()) {
		cout << "Inserting: " << value << endl;
		outputFile << "Inserting: " << value << endl;

		displayTree(root, 0);

		cout << "Tree Depth: " << treeHeight(root) << endl;
		cout << "Operations: " << getOpCount() << endl;
		outputFile << "Operations: " << getOpCount() << endl;
		outputFile << "Tree Depth: " << treeHeight(root) << endl;
		resetOpCount();
		cout << "_____________________________________________________________" << endl;
		outputFile << "_____________________________________________________________" << endl;
		cout << endl;
		outputFile << endl;


	}
	outputFile.close();
}

void BinarySearchTree::deleteValue(int value) {
	root = deleteNode(root, value);
}

void BinarySearchTree::searchValue(int value)
{
	ofstream outputFile(BinarySearchTree::testTitle, ios::app);
	cout << "Searching: " << value << endl;
	outputFile << "Searching: " << value << endl;

	displayTree(root, 0);
	cout << endl;

	if (searchRec(root, value)) {
		outputFile << value << " found " << endl;
		cout << value << " found " << endl;
	}
	else {
		outputFile << value << " not found" << endl;
		cout << value << " not found" << endl;
	}

	cout << "Tree Depth: " << treeHeight(root) << endl;
	cout << "Operations: " << getOpCount() << endl;
	outputFile << "Operations: " << getOpCount() << endl;
	outputFile << "Tree Depth: " << treeHeight(root) << endl;
	cout << "_____________________________________________________________" << endl;
	outputFile << "_____________________________________________________________" << endl;
	cout << endl;
	outputFile << endl;
	resetOpCount();
}

void BinarySearchTree::displayTree() {
	displayTree(root, 0);
}

void BinarySearchTree::setTitle(string name)
{
	BinarySearchTree::testTitle = name + ".txt";
}

int BinarySearchTree::treeHeight(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}

	int leftheight = treeHeight(root->left);
	int rightHeight = treeHeight(root->right);
	return 1 + max(leftheight, rightHeight);
}

bool BinarySearchTree::searchRec(TreeNode* root, int value){
	operationCtr++;
	actionCT[1]++;
	if (root == nullptr) {
		return false;
	}
	if (root->data == value) {
		return true;
	}

	if (value < root->data) {
		return searchRec(root->left, value);
	}
	else {
		return searchRec(root->right, value);
	}
}


int BinarySearchTree::getOpTotal()
{
	return opTotal;
}

int BinarySearchTree::getOpCount()
{
	return operationCtr;
}

void BinarySearchTree::incOpCnt()
{
	operationCtr++;
}

void BinarySearchTree::resetOpCount()
{
	operationCtr = 0;
}
BinarySearchTree::BinarySearchTree() : root(nullptr), operationCtr(0), opTotal(0), actionCT{0,0,0,0} {}

void PreformAction::setTitle(string name)
{
	PreformAction::testTitle = name + ".txt";
}

void PreformAction::displayReportSummary(BinarySearchTree& treePass, vector<string> data) {
	ofstream outputFile(PreformAction::testTitle, ios::app);
	int totalAct = treePass.actionCT[0] + treePass.actionCT[1] + treePass.actionCT[2] + treePass.actionCT[3];
	PreformAction::testTitle = PreformAction::testTitle.substr(0, PreformAction::testTitle.size() - 4);

	cout << "        " << PreformAction::testTitle << endl;
	cout << "        Operation Counts" << endl;
	cout << "                  BST" << endl;
	cout << "Creation           " << treePass.actionCT[0] << endl;
	cout << "Search             " << treePass.actionCT[1] << endl;
	cout << "Insert             " << treePass.actionCT[2] << endl;
	cout << "Delete             " << treePass.actionCT[3] << endl;
	cout << "                 _________" << endl;
	cout << "Total              " << totalAct << endl;

	outputFile << "        " << PreformAction::testTitle << endl;
	outputFile << "                  BST" << endl;
	outputFile << "Creation           " << treePass.actionCT[0] << endl;
	outputFile << "Search             " << treePass.actionCT[1] << endl;
	outputFile << "Insert             " << treePass.actionCT[2] << endl;
	outputFile << "Delete             " << treePass.actionCT[3] << endl;
	outputFile << "                 _________" << endl;
	outputFile << "Total              " << totalAct << endl;

}

void PreformAction::actOnTree(BinarySearchTree& treePass, vector<string> data) {
	ofstream outputFile(PreformAction::testTitle, ios::app);
	int integer{};
	string actCommand;

	for (int i = 0; i < data.size(); i += 2) {
		actCommand = data[i];

		if (actCommand != keys[0] && actCommand != keys[1] && actCommand != keys[2]) {
			outputFile << actCommand << " - Not a valid command" << endl;
			cout << actCommand << " - Not a valid command" << endl;
			cout << "_____________________________________________________________" << endl;
			outputFile << "_____________________________________________________________" << endl;
			continue;
		}

		try {
			int integer = stoi(data[i + 1]);
		}
		catch (const invalid_argument& ia) {
			cout << data[i + 1] << " - Not an integer" << endl;
			outputFile << data[i + 1] << " - Not an integer" << endl;
			cout << "_____________________________________________________________" << endl;
			outputFile << "_____________________________________________________________" << endl;
			continue;
		}
		
		int integer = stoi(data[i + 1]);


		if (actCommand == keys[0]) {
			treePass.actionCT[2]++;
			treePass.incOpCnt();
			treePass.insert(integer,2);
		}
		else if (actCommand == keys[1]) {
			treePass.deleteValue(integer);
			treePass.incOpCnt();
			treePass.actionCT[3]++;

			cout << "Deleting: " << integer << endl;
			outputFile << "Deleting: " << integer << endl;

			treePass.displayTree();

			cout << "Tree Depth: " << treePass.treeHeight(treePass.root) << endl;
			cout << "Operations: " << treePass.getOpCount() << endl;
			outputFile << "Operations: " << treePass.getOpCount() << endl;
			outputFile << "Tree Depth: " << treeHeight(treePass.root) << endl;
			cout << "_____________________________________________________________" << endl;
			outputFile << "_____________________________________________________________" << endl;
			cout << endl;
			outputFile << endl;
			treePass.resetOpCount();
		}
		else if (actCommand == keys[2]) {
			treePass.searchValue(integer);
		}
	}
	displayReportSummary(treePass, data);
}



