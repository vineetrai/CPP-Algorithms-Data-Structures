// Program creates a binary search tree of size 15, then
// traverses the tree.

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;



//Node class
class Node {
public:
	Node();
	int val;
	Node* left;
	Node* right;
};

Node::Node() {
	val = 0;
	left = NULL;
	right = NULL;
}



//function declarations
inline void keepWindowOpen();
void printName();
void insertBST(Node* tmp, int v);
void ioTraverse(Node* tmp);
Node* deleteNode(Node* tmp, int v);
Node* findPred(Node* tmp1, Node* pred, Node* tmp2);
Node* getMax(Node* tmp1);


Node* getMax(Node* tmp1) {
	while (tmp1->right != NULL) {
		if (tmp1->right->left || tmp1->right->right) {
			tmp1 = tmp1->right;
		}
	}
	return tmp1;
}


Node* findPred(Node* tmp1, Node* pred, Node* tmp2) {

	if (tmp1 == NULL) {
		return pred;
	}

	else if (tmp1->val == tmp2->val && tmp1->left != NULL) {
		pred = getMax(tmp2->left);
	}

	else if (tmp1->left || tmp2->right) {
		if (tmp1->val < tmp2->val) {
			pred = findPred(tmp1->right, tmp1, tmp2);
		}
		//else tmp1->val > tmp2->val
		else {
			pred = findPred(tmp1->left, pred, tmp2);
		}
	}

	else {
		return pred;
	}

	return pred;
}


Node* deleteNode(Node* tmp, int v) {

	Node* oldroot = tmp;
	Node* newroot = tmp;

	if (tmp == NULL) {
		cout << "Error, could not find value " << v << " in tree";
		newroot = tmp;
	}
	else if (v < tmp->val) {
		newroot = deleteNode(tmp->left, v);
	}
	else if (v > tmp->val) {
		newroot = deleteNode(tmp->right, v);
	}
	//else tmp->val == v
	else {
		Node* p = NULL;
		p = findPred(oldroot, p, tmp);
		
		if (p != NULL) {
			tmp->val = p->val;
			newroot = deleteNode(p, p->val);
		}
		else {
			tmp = tmp->right;
		}
	}

	return newroot;

}


void ioTraverse(Node* tmp) {

	if (tmp == NULL) {
		return;
	}
	ioTraverse(tmp->left);
	cout << tmp->val << " ";
	ioTraverse(tmp->right);
}



void insertBST(Node* tmp, int v) {

	Node* ins = new Node;
	ins->val = v;

	if (tmp->val < v) {
		if (tmp->right == NULL) {
			//insert(v); 
			tmp->right = ins;
		}
		else {
			insertBST(tmp->right, v);
		}
	}
	else if (tmp->left == NULL) {
		//insert(v);
		tmp->left = ins;
	}
	else {
		insertBST(tmp->left, v);
	}
}



inline void keepWindowOpen() {
	char ch;
	cout << "\n\nEnter any key to continue.\n";
	cin >> ch;
}



void printName() {
	cout << "Vineet Rai\nAssignment #2\nFebruary 23, 2020\n\n";
}



int main() {
	printName();

	vector<int> numlist = {
		50, 40, 80, 20, 45, 60, 100,
		70, 65, 42, 44, 30, 25, 35, 33
	};

	Node* root = new Node;
	root->val = numlist[0];
	cout << "Root set as " << root->val << endl;

	for (int i = 1; i < numlist.size(); i++) {
		insertBST(root, numlist[i]);
		cout << "inserted " << numlist[i] << endl;
	}

	cout << endl << "In Order Traversal: " << endl;
	ioTraverse(root);
	cout << endl << endl;

	ioTraverse(deleteNode(root, 50));

	keepWindowOpen();
	return 0;
}