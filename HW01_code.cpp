// Program creates a linked list of user-defined size, then
// applies the selection sort algorithm on it.


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
	Node* next;
};

Node::Node() {
	val = 0;
	next = NULL;
}


//function declarations
inline void keepWindowOpen();
void printName();
int userInput();
Node* createList(int s);
void traverseList(Node* h);
Node* selSort(Node* h);



inline void keepWindowOpen() {
	char ch;
	cout << "\n\nEnter any key to continue.\n";
	cin >> ch;
}


void printName() {
	cout << "Vineet Rai\nAssignment #1\nFebruary 8, 2020\n\n";
}


//get size of linked list from user
int userInput() {

	cout << "Please enter the number of nodes for the linked list." << endl;

	int uc;
	cin >> uc;
	cout << endl;

	while (cin.fail() || uc < 1) {
		cout << "Error. Please enter a positive integer value." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> uc;
	}

	return uc;
}


//generate linked list
Node* createList(int s) {
	Node* head = new Node;
	Node* tmp = head;

	srand(0);//set random seed

	for (int i = 0; i < s - 1; i++) {
		tmp->val = rand() % s;
		//cout << tmp->val << ", ";
		tmp->next = new Node;
		tmp = tmp->next;
	}

	return head;
}


//traverse linked list
void traverseList(Node* h) {
	while (h != NULL) {
		cout << h->val << " ";
		h = h->next;
	}
	cout << endl << endl;
}


//selection sort of linked list
Node* selSort(Node* h) {
	
	Node* prevcurrent = h;
	Node* current = h;
	Node* current2 = h;
	Node* tmp = NULL;
	Node* tmp2 = NULL;

	while (current->next != NULL) {

		current2 = current->next;
		tmp2 = current->next;

		while (current2 != NULL) {

			if (current->val > current2->val) {

				if ((current == h) && (current->next == current2)) {
					current->next = current2->next;
					current2->next = current;
					tmp = current;
					current = current2;
					current2 = tmp;
					tmp2 = current2;
					h = current;
					current2 = current2->next;
				}
				else if ((current == h) && (current->next != current2)) {
					tmp = current->next;
					current->next = current2->next;
					current2->next = tmp;
					tmp2->next = current;
					tmp = current;
					current = current2;
					current2 = tmp;
					tmp2 = current2;
					current2 = current2->next;
					h = current;
				}
				else if ((current != h) && (current->next == current2)) {
					current->next = current2->next;
					current2->next = current;
					prevcurrent->next = current2;
					tmp = current;
					current = current2;
					current2 = tmp;
					tmp2 = current2;
					current2 = current2->next;
				}
				else if ((current != h) && (current->next != current2)) {
					tmp = current->next;
					current->next = current2->next;
					current2->next = tmp;
					tmp2->next = current;
					prevcurrent->next = current2;
					tmp = current;
					current = current2;
					current2 = tmp;
					tmp2 = current2;
					current2 = current2->next;
				}

			}
			else {
				tmp2 = current2;
				current2 = current2->next;
			}
		}

		prevcurrent = current;
		current = current->next;

	}

	return h;
}


int main() {
	printName();

	int n = userInput();
	Node* head = createList(n);
	cout << "An unsorted linked list of size " << n << ":" << endl;
	traverseList(head);

	head = selSort(head);
	cout << "The same linked list, sorted:" << endl;
	traverseList(head);
	
	keepWindowOpen();
	return 0;
}