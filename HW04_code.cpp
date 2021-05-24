// Program performs the following tasks:
//	create a graph of 20 vertices (disconnected)
//	add 25 edges to the graph adjacency matrix
//	DFS (depth-first traversal) so that all connected components are visited
//	BFS (breadth-first search) so that all connected components are visited
 

#include <iostream>
#include <string>
using namespace std;


//number of vertices
const int V = 20;


//function Prototyping
void printName();
void zeroVals(bool arr[][V], int n);
void printVals(bool arr[][V], int n);
void addEdge(bool arr[][V], int a, int b);
void traverseDFS(bool arr[][V], bool seen[][V], int s);
void fullDFS(bool arr[][V], bool seen[][V]);
void traverseBFS(bool arr[][V], bool seen[][V], int fifo[], int front, int back, int s);
void fullBFS(bool arr[][V], bool seen[][V], int fifo[], int front, int back);


void printName() {
	cout << "Vineet Rai" << endl;
	cout << "Assignment #4" << endl;
	cout << "April 4, 2020" << endl;
	cout << endl;
}


void zeroVals(bool arr[][V], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < V; j++) {
            arr[i][j] = false;
        }
    }
}


void printVals(bool arr[][V], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < V; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}


void addEdge(bool arr[][V], int a, int b) {
    if (a < V && b < V) {
        arr[a][b] = true;
        arr[b][a] = true;
        cout << "Added edge between vertices " << a << " and " << b << endl; 
    }
    else {
        cout << "ERROR: no edge added between vertices " << a << " and " << b << endl;
        cout << "One or both vertices do not exist." << endl;
    }
}


void traverseDFS(bool arr[][V], bool seen[][V], int s) {
    if (!seen[0][s]) {
        seen[0][s] = true;
        cout << s << " ";
        //cout << "Visited " << s << endl;
        //printVals(seen, 1);
        for (int j = 0; j < V; j++) {
            if (arr[s][j] && !seen[0][j]) {
                //cout << s << " is adjacent to " << j << endl;
                traverseDFS(arr, seen, j);
            }
        }
    }
}


//do DFS for each vertex if needed
void fullDFS(bool arr[][V], bool seen[][V]) {
    for (int i = 0; i < V; i++) {
        bool begin = false;
        int j = 0;
        while (!begin && j < V) {
            begin = arr[i][j] && !seen[0][j];
            j += 1;
        }
        if (begin) {
            traverseDFS(arr, seen, i);
        }
    }
}


void traverseBFS(bool arr[][V], bool seen[][V], int fifo[], int front, int back, int s) {
    for (int j = 0; j < V; j++) {
        if (arr[s][j] && !seen[0][j]) {
            seen[0][j] = true;
            fifo[back] = j;
            back += 1;
        }
    }
    if (front < V - 1) {
        front += 1;
        traverseBFS(arr, seen, fifo, front, back, fifo[front]);
    }
}


//do full BFS for each vertex if needed
void fullBFS(bool arr[][V], bool seen[][V], int fifo[], int front, int back) {
    for (int i = 0; i < V; i++) {
        if (!seen[0][i]) {
            seen[0][i] = true;
            fifo[back] = i;
            back += 1;
            traverseBFS(arr, seen, fifo, front, back, i);
        }
    }
    for (int i = 0; i < V; i++) {
        cout << fifo[i] << " ";
    }
}


int main() {
	printName();

    cout << "Creating graph of 20 vertices and 20 edges:" << endl;
	bool graph[V][V];
    zeroVals(graph, V);
    cout << endl;

    //add 20 edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 11);
    addEdge(graph, 0, 14);
    addEdge(graph, 1, 5);
    addEdge(graph, 1, 9);
    addEdge(graph, 1, 10);
    addEdge(graph, 2, 10);
    addEdge(graph, 2, 11);
    addEdge(graph, 2, 17);
    addEdge(graph, 3, 12);
    addEdge(graph, 3, 13);
    addEdge(graph, 4, 6);
    addEdge(graph, 4, 7);
    addEdge(graph, 4, 8);
    addEdge(graph, 4, 14);
    addEdge(graph, 5, 15);
    addEdge(graph, 5, 19);
    addEdge(graph, 6, 7);
    addEdge(graph, 6, 14);
    addEdge(graph, 7, 14);
    addEdge(graph, 8, 14);
    addEdge(graph, 10, 11);
    addEdge(graph, 11, 18);
    addEdge(graph, 12, 13);
    addEdge(graph, 15, 16);
    cout << endl;

    cout << "Adjacency Matrix of Graph:" << endl;
    printVals(graph, V);
    cout << endl;
    
    //array of visited vertices
    bool visited[1][V];
    zeroVals(visited, 1);

    cout << "DFS Traversal of the Graph:" << endl;
    fullDFS(graph, visited);
    cout << endl << endl;
    
    zeroVals(visited, 1);
    int queue[V];
    int front = 0;
    int back = 0;
    for (int i = 0; i < V; i ++) {
        queue[i] = -1;
    }
    cout << "BFS Traversal of the Graph:" << endl;
    fullBFS(graph, visited, queue, front, back);

	return 0;
}