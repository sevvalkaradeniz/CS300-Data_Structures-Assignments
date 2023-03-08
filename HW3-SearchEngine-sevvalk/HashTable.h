#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct DocumentItem {
    string documentName;
    int count;
    DocumentItem(string d = "", int c = 0)
        :documentName(d), count(c)
    {}

    void increaseCount() {
        count++;
    }
};

struct WordItem {
    string word;
    // List of DocumentItem’s.
    vector<DocumentItem> docVec;
    WordItem(string w="")
        :word(w)
    {}
    bool Less(const WordItem& rhs)const {   // function for < operator  
        if (word < rhs.word) {
            return true;
        }
        return false;
    }

};


bool operator < (const WordItem& lhs, const WordItem& rhs) {
    return lhs.Less(rhs);
}

bool operator > (const WordItem& rhs, const WordItem& lhs) {
    return lhs < rhs;
}

bool operator != (const WordItem& rhs, const WordItem& lhs) {
    if (rhs.word != lhs.word) {
        return true;
    }
    return false;
}
/*
ostream& operator << (ostream& os,  const WordItem& w) {
    ostringstream ostr;
    ostr << w.word;
    os << ostr.str();
    return os;
}
*/
bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}



int Hash(const WordItem& key, int tableSize);

int nextPrime(int n);

template <class HashedObj>
class HashTable
{
public:
    explicit HashTable(const HashedObj& notFound, int size = 101);
    HashTable(const HashTable& rhs)
        : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),array(rhs.array), currentSize(rhs.currentSize)
    {}

    const HashedObj& find(const HashedObj& x) const;

    void makeEmpty();
    void insert(const HashedObj& x);
    void remove(const HashedObj& x);

    const HashTable& operator=(const HashTable& rhs);

    enum EntryType { ACTIVE, EMPTY, DELETED };
//private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(),EntryType i = EMPTY)
            : element(e), info(i) 
        {}
    };

    vector<HashEntry> array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;

    bool isActive(int currentPos) const;
    int findPos(const HashedObj& x) const;
    void rehash();
};


template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound,int size)
    : ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
    makeEmpty();
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const
{
    int collisionNum = 0;
    int currentPos = Hash(x, array.size());
    int offset = 0;

    while (array[currentPos].info != EMPTY && array[currentPos].element != x)
    {        
        currentPos += pow(++collisionNum, 2+offset);  //add the difference
        if(currentPos >= array.size()) {             // perform the mod
            currentPos = currentPos- array.size(); // if necessary
            collisionNum = 0;
            offset++;
        }
    }
    return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos)) {
        array[currentPos].info = DELETED;
    }
        
}

template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x)
const
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return array[currentPos].element;

    return   ITEM_NOT_FOUND;
}

template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{
    // Insert x as active
    int currentPos = findPos(x);
    //cout << "CurrPos: " << currentPos << " " << array.size() << endl;
    if (isActive(currentPos)) {
        return;
    }
    array[currentPos] = HashEntry(x, ACTIVE);
    //cout << "insert " << currentSize << " " << currentPos << " " << array[currentPos].element.word << endl;

    // enlarge the hash table if necessary 
    if (++currentSize >= (array.size() /2)) {
        //cout << "CurrentSize: " << currentSize << " " << array.size() << endl;
        double loadFactor = (double(currentSize) / array.size());
        //cout << "insiloadFactorde: " << loadFactor << endl;
        if (loadFactor > 0.65) {
           // cout << "inside: " << endl;
            rehash();
            //cout << "end: " << endl;
        }
        
    }
   // cout << "CurrentSize: " << currentSize << " " << array.size() << endl;
        
}

template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<HashEntry> oldArray = array;
    //cout << "Previous array size " << array.size() << endl;
    // Create new double-sized, empty table

    cout << "rehashed..." << endl;
    cout << "previous table size : " << array.size();

    array.resize(nextPrime(2 * oldArray.size()));
    for (int j = 0; j < array.size(); j++)
        array[j].info = EMPTY;
    // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++) {
        if (oldArray[i].info == ACTIVE) {
            //cout << "current array xx " << currentSize << " " << oldArray[i].element.word << endl;
            insert(oldArray[i].element);
        }
    }
    double loadFactor = (double(currentSize) / array.size());
    cout << ", new table size : " << array.size() << ", current unique word count " << currentSize << ",current load factor : " << loadFactor <<  endl;
}


template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for (int i = 0; i < array.size(); i++) {
        array[i].info = EMPTY;
        array[i].element = ITEM_NOT_FOUND;
    }
    // destroy the lists but not the vector!
}


int nextPrime(int n)
{
    
    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}



int Hash(const WordItem& key, int tableSize)
{
    int hashVal = 0;

    for (int i = 0; i < key.word.length(); i++) {        
        hashVal = 37 * hashVal + key.word[i];
    }        

    hashVal = hashVal % tableSize;

    if (hashVal < 0)
        hashVal = hashVal + tableSize;

    return(hashVal);
}
