// DFS and BFS topological sort


#include <iostream>
#include <vector>
#include <string>
using namespace std;


inline void printName() {
	cout << "Vineet Rai" << endl;
	cout << "Assignment #4" << endl;
	cout << "April 22, 2020" << endl;
	cout << endl;
}


class Graph {
    public:
        Graph(const string& names);
        ~Graph();
        string getLabels();
        int getSize();
        void addEdge(const string& dir);
        void printAdj();
        vector<bool> fullseen;
        vector<bool> localseen;
        vector<int> order;
        vector<int> predcount;
        int n;
        bool cycle;
        void fullTopoDFS();
        void topoDFS(int v);
        void fullTopoBFS();
        void topoBFS(int v);
    private:
        string labels;
        int size;
        vector<vector<int>> adj;
};


Graph::Graph(const string& names) {
    labels = names;
    size = labels.size();

    adj = {{}};
    adj.resize(size);
    for (int i = 0; i < size; i++){
        adj[i].resize(size);
        for(int j = 0; j < size; j++){
            adj[i][j] = 0;
        }
    }

    fullseen = {};
    localseen = {};
    order = {};
    predcount = {};

    fullseen.resize(size);
    localseen.resize(size);
    order.resize(size);
    predcount.resize(size);

    fill(fullseen.begin(), fullseen.end(), false);
    fill(localseen.begin(), localseen.end(), false);
    fill(order.begin(), order.end(), -1);
    fill(predcount.begin(), predcount.end(), 0);

    n = size - 1;
    cycle = false;

    cout << "Created Graph of size " << size << endl << endl;
}


Graph::~Graph() {
}


string Graph::getLabels(){
    return labels;
}


int Graph::getSize(){
    return size;
}


void Graph::addEdge(const string& dir){
    if (dir.size() != 2){
        cout << "Error in directed edge input." << endl;
    }
    else{
        char a = dir[0];
        char b = dir[1];
        int x = labels.find(a);
        int y = labels.find(b);

        adj[x][y] = 1;
        adj[y][x] = -1;
        cout << "Added directed edge from " << a << " to " << b << endl;
    }
}


void Graph::printAdj(){
    cout << "Adjacency Matrix of Graph:" << endl;

    cout << "     ";
    for (int j = 0; j < size; j++){
        cout << labels[j] << "  ";
    }
    cout << endl;
    
    cout << "   ";
    for (int j = 0; j < size; j++){
        cout << "---";
    
    }
    cout << endl;
    
    for (int i = 0; i < size; i++){
        cout << labels[i] << " | ";
        for (int j = 0; j < size; j++){
            if (adj[i][j] != -1){
                cout << " " << adj[i][j];
            }
            else{
                cout << adj[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void Graph::fullTopoDFS(){
    for (int i = 0; i < size; i++){
        if (!fullseen[i] && !cycle){
            cout << "Calling topoDFS for vertex " << labels[i] << endl;
            topoDFS(i);
        }
    }

    if (!cycle){
        cout << "\n\nDFS Topological Ordering:" << endl;
        for (int i = 0; i < order.size(); i++){
            int s = order[i];
            cout << labels[s] << " ";
        }
        cout << endl << endl << endl;
    }
    else {
        cout << endl << "There is no topological ordering because of the cycle."
            << endl << endl;
    }
    
    fill(localseen.begin(), localseen.end(), 0);
    fill(fullseen.begin(), fullseen.end(), 0);
    fill(order.begin(), order.end(), -1);
    n = size - 1;
    bool cycle = false;
}


void Graph::topoDFS(int v){
    if (fullseen[v]){
        cout << "fullseen " << v << endl;
        return;
    }
    if (localseen[v]){
        cycle = true;
        cout << endl << "**Cycle found.**" << endl << endl;
        return;
    }
    
    localseen[v] = true;
    cout << "localseen " << labels[v] << " is now true" << endl;

    for (int j = 0; j < size; j++){
        if (adj[v][j] == 1){
            cout << "Calling topoDFS for vertex " << labels[j] << endl;
            topoDFS(j);
        }
        
    }

    localseen[v] = false;
    cout << "localseen " << labels[v] << " is now false" << endl;
    fullseen[v] = true;
    cout << "fullseen " << labels[v] << " is now true" << endl;
    order[n] = v;
    cout << labels[v] << " has order number " << n << endl;
    n--;
    cout << "N is decremented to " << n << endl;
}


void Graph::fullTopoBFS(){
    for (int i = 0; i < size; i++){
        int sum = 0;
        cout << "running sum initialized to zero." << endl;
        for (int j = 0; j < size; j++){
            if (adj[i][j] == -1){
                sum += 1;
                cout << "vertex " << labels[j] << " is a predecessor of "
                    << labels[i] << endl;
            }
        }
        predcount[i] = sum;
        cout << "predcount of vertex " << labels[i] << " is " << sum << endl;
        if (sum == 0){
            order.push_back(i);
            cout << "pushing back " << i << " into order vector." << endl;
        }
    }

    n = 0;
    while (n <= order.size()){
        topoBFS(order[n]);
    }

    cout << "BFS Topological Ordering:" << endl;
    for (int i = 0; i < order.size(); i++){
        int s = order[i];
        cout << labels[s] << " ";
    }
    cout << endl << endl;
}


void Graph::topoBFS(int v){
    n++;
    for (int j = 0; j < size; j++){
        if (adj[v][j] == 1){
            predcount[j]--;
            if (predcount[j] == 0){
                order.push_back(j);
            }
        }
    }
    topoBFS(order[n]);
}




int main() {
    printName();

    Graph A("mnopqrstuvwxyz");
    vector<string> edgesA = {
        "mq", "mr", "ms",
        "no", "nq", "nu",
        "or", "ov", "os",
        "po", "ps", "pz",
        "qt",
        "ru", "ry",
        "sr",
        "ut",
        "vx", "vw",
        "wz",
        "yv"
    };
    for (int i = 0; i < edgesA.size(); i++){
        string tmp = edgesA[i];
        A.addEdge(tmp);
    }
    cout << endl;
    A.printAdj();
    A.fullTopoDFS();
    //A.fullTopoBFS();

    cout << "\n\n\n-------------------------------------------\n\n\n";

    Graph B("12345678");
    vector<string> edgesB = {
      "12", "15", "16",
      "23", "25", "27",
      "34",
      "45",
      "57", "58",
      "65", "68",
      "74", "78",  
    };
    for (int i = 0; i < edgesB.size(); i++){
        string tmp = edgesB[i];
        B.addEdge(tmp);
    }
    cout << endl;
    B.printAdj();
    B.fullTopoDFS();
    //B.fullTopoBFS();

    return 0;
}