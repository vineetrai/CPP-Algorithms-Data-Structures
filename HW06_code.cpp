// Student Name: Vineet Rai
// University of Texas at Dallas
// Course: CS 5343.502
// Instructor: Dr. Neeraj K. Gupta
// Assignment #6
// April 29, 2020


#include <iostream>
#include <cmath>
using namespace std;


void printName() {
	cout << "Vineet Rai" << endl;
	cout << "Assignment #6" << endl;
	cout << "April 29, 2020" << endl;
	cout << endl;
}


class HashTable {
    public:
        HashTable(const string arr[], const int &s, const int &n);
        ~HashTable();

        int numCollide;
        int listSize;
        int tableSize;
        int fillCount;

        string getWord(int &i);
        void insertHash(const string &word);
        void quadProbe(const int &x, const string &word);
        int calcHash(const string &word);
        double getLoadFactor();
        void fullHash();
        void widenTable();

    private:
        const string* wordList; // ptr to wordlist array
        const string** htArr; // ptr to "hashtable array" of ptrs to words
};


// constructor inputs: ptr to word array, array size, hashtable size
// calls fullHash() which is the high-level hashing function
HashTable::HashTable(const string arr[], const int &s, const int &n){
    numCollide = 0; // number of collisions while filling htArr
    listSize = s; // number of words in array to be hashed
    tableSize = n; // size of "htArr" the hashtable array
    wordList = arr; // set ptr to array of words
    fillCount = 0; // number of filled slots in htArr

    // ptr to "hashtable array" of ptrs to words
    htArr = new const string*[tableSize];
    for (int i = 0; i < tableSize; i++){
        htArr[i] = nullptr;
    }

    cout << "created HashTable object" << endl;
    cout << "the current tableSize is " << tableSize << endl << endl;
    
    fullHash();
}


// destructor: delete "htArr" the hashtable array
HashTable::~HashTable(){
    delete [] htArr;
}


// high-level hash function
void HashTable::fullHash(){
    int i = 0;
    while (getLoadFactor() < 0.5 && fillCount < listSize){
        cout << "\"" << getWord(i) << "\"" << endl;
        insertHash(wordList[i]);
        cout << endl;
        i += 1;
    }
    if (getLoadFactor() >= 0.5){
        cout << fillCount << " items have been hashed" << endl;
        cout << "the tableSize is currently " << tableSize << endl;
        cout << "the load factor is now " << getLoadFactor() << " >= 0.5" << endl;
        
        widenTable();
        fullHash();
        return;
    }

    cout << "fillCount is " << fillCount << endl;
    cout << "loadFactor is " << getLoadFactor() << endl;
    cout << "total collisions is " << numCollide << endl;
}


// extract word from wordList array
string HashTable::getWord(int &i){
    return wordList[i];
}


// inserts ptr to word in htArr
void HashTable::insertHash(const string &word){
    int h = calcHash(word);
    if (!htArr[h]){
        htArr[h] = &word;
        fillCount++;
        cout << "insertHash at index " << h << endl;
    }
    else{
        numCollide++;
        cout << "collision (" << numCollide << ") found at index " << h << endl;
        cout << "trying quadratic probing..." << endl;
        quadProbe(h, word);
    }
}


// open addressing, quadratic collision resolution scheme
void HashTable::quadProbe(const int &x, const string &word){
    bool done = false;
    double a = static_cast<double>(x);
    double i = 1;
    double d = 0;
    int s = 0;

    while (!done){
        d = (x + pow(i, 2));
        s = static_cast<int>(d);
        if (!htArr[s]){
            done = true;
        }
        else{
            numCollide++;
            cout << "collision (" << numCollide << ") found at index " << s << endl;
            i++;
        }
    }
    
    htArr[s] = &word;
    fillCount++;
    cout << "insertHash at index " << s << endl;
}


// calculate hash value for a word
int HashTable::calcHash(const string &word){
    int hashVal = 0;
    
    for (int i = 0; word[i] > 0; i++){
        hashVal = 37 * hashVal + word[i];
    }

    hashVal %= tableSize;
    if (hashVal < 0){ // in case of int overflow
        hashVal += tableSize;
    }
    
    // cout << "calculated hashVal is " << hashVal << endl;
    return hashVal;
}


// fillCount divided by tableSize
double HashTable::getLoadFactor(){
    double a = static_cast<double>(fillCount);
    double b = static_cast<double>(tableSize);
    return a / b;
}


// double tableSize and clear hashtable
void HashTable::widenTable(){
    cout << "clearing the hash table and expanding tableSize..." << endl;
    
    bool done = false;
    tableSize = 2 * tableSize - 1; // odd number, one less than twice original
    
    while (!done){
        tableSize += 2;
        bool isPrime = true;
        for (int j = 3; j <= sqrt(tableSize) + 1; j++){
            int m = tableSize % j;
            cout << tableSize << " % " << j << " == " << m << endl;
            if (m == 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime){
            done = true;
        }
    }


    delete [] htArr;
    htArr = new const string*[tableSize];
    for (int i = 0; i < tableSize; i++){
        htArr[i] = nullptr;
    }
    
    fillCount = 0;
    cout << "found the smallest prime more than double the previous size" << endl;
    cout << "the new hash table has size " << tableSize << endl;
    cout << "starting hashing process again" << endl << endl;
}


int main(){
    printName();

    const string book[20] = {
        "pyramids", "station", "African", "The", 
        "John Doe", "Ohio", "military", "internet", 
        "leopard", "USA", "island", "album", 
        "north", "singer", "Luggage", "series", 
        "urban", "marine", "radio", "rugby"
        };

    HashTable obj(book, 20, 31);
    return 0;
}