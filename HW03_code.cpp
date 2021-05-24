// Program performs the following tasks:
// create an array of 15 elements
// convert array into min heap using Floyd's algorithm
// sort the min heap in descending order using Heapsort



#include <iostream>
#include <cstdlib>
using namespace std;



//Number of desired array elements
//default is 15 elements
const int N = 15;



//Function Prototyping
void printName();
void fillArray(int a[]);
void printArray(int arr[]);
void minHeapify(int a[], int x);
void buildMinHeap(int arr[]);
void swapValues(int a[], int u, int v);
void sortHeap(int a[]);



void printName() {
	cout << "Vineet Rai" << endl;
	cout << "Assignment #3" << endl;
	cout << "March 1, 2020" << endl;
	cout << endl;
}



//fill array with N random elements
void fillArray(int a[]) {
	int s = a[0];
	srand(s); //set random seed

	for (int i = 1; i < s + 1; i++) {
		a[i] = rand() % (5 * s);
	}
}



//traverse array and print each element
void printArray(int a[]) {
	int s = a[0];

	for (int i = 1; i < s + 1; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}



//maintain heap property for subtree at root x
void minHeapify(int a[], int x) {
	int s = a[0];
	int min = 0;
	int left = 2 * x;
	int right = 2 * x + 1;

	if ((left <= s) && (a[left] < a[x])) {
		min = left;
	}
	else {
		min = x;
	}

	if ((right <= s) && (a[right] < a[min])) {
		min = right;
	}

	if (min != x) {
		swapValues(a, x, min);
		minHeapify(a, min);
	}
}



//convert array into min heap
void buildMinHeap(int a[]) {
	int s = a[0];

	for (int i = s / 2; i > 0; i--) {
		minHeapify(a, i);
	}
}



//helper function to swap array values
void swapValues(int a[], int u, int v) {
	int tmp = a[u];
	a[u] = a[v];
	a[v] = tmp;
}



//given a min heap, sort in descending order
void sortHeap(int a[]) {
	int s = a[0];

	for (int i = a[0]; i > 0; i--) {
		swapValues(a, 1, i);
		a[0] = a[0] - 1;
		minHeapify(a, 1);
	}

	a[0] = s;
}



int main() {
	printName();

	cout << "Generating array with " << N << " random elements...\n";
	int array[N + 1];
	array[0] = N; //store number of elements as value at index 0
	fillArray(array);

	cout << "The array elements are: ";
	printArray(array);
	cout << endl;

	cout << "Now converting array into Min Heap, using Floyd's algorithm...\n";
	buildMinHeap(array);

	cout << "The reordered array elements are: ";
	printArray(array);
	cout << endl;

	cout << "Now sorting Min Heap in descending order, using Heapsort...\n";
	sortHeap(array);

	cout << "The sorted array elements are: ";
	printArray(array);
	cout << endl;

	return 0;
}