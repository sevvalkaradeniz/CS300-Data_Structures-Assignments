#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "strutils.h"

using namespace std;

struct PhoneBook {
    string name,surname,nameAndSurname;
    string city, phoneNumber;
    PhoneBook(string n="",string sn="", string c="", string p="",string nameAndSurname="")
        :name(n),surname(sn), city(c), phoneNumber(p), nameAndSurname(nameAndSurname)
    {}

    bool Less(const PhoneBook& rhs)const { // function for < operator  
        if (rhs.nameAndSurname.find(" ") != string::npos) {
            if (nameAndSurname < rhs.nameAndSurname) {
                return true;
            }
        }
        else {
            if (name < rhs.name) {
                return true;
            }
        }
        return false;
    }
  
    bool operator<=(const PhoneBook& rhs) {
        if (nameAndSurname <= rhs.nameAndSurname) {
            return true;
        }
        return false;
    }

    bool operator == (const PhoneBook rhs) {
        if (rhs.nameAndSurname.find(" ")!=string::npos) {
            if (nameAndSurname == rhs.nameAndSurname) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            string subS = name.substr(0, rhs.name.length());
            if (subS == rhs.name) {
                return true;
            }
            else {
                return false;
            }
        }
    }

    bool operator > (const PhoneBook& rhs) {
        if (rhs.nameAndSurname.find(" ") != string::npos) {
            if (nameAndSurname > rhs.nameAndSurname) {
                return true;
            }
        }
        else {
            if (name > rhs.name) {
                return true;
            }
        }
        return false;
    }
};

bool operator < (const PhoneBook& lhs, const PhoneBook& rhs) {
    return lhs.Less(rhs);
}



ostream& operator << (ostream& os, const PhoneBook& pb) {
    ostringstream ostr;
    ostr << pb.nameAndSurname << " " << pb.phoneNumber << " " << pb.city;
    os << ostr.str();
    return os;
}

vector<PhoneBook> insertSortVec;
vector<PhoneBook> quickSortVec;
vector<PhoneBook> mergeSortVec;
vector<PhoneBook> heapSortVec;

#define merge Merge
#define swap Swap

template <class Comparable>
void insertionSort(vector<Comparable>& a)
{
   for (int p = 1; p < a.size(); p++)
    {
         Comparable tmp = a[p];

        int j;
        for (j = p; j > 0 && tmp < a[j - 1]; j--)
          a[j] = a[j - 1];
       a[j] = tmp;
    }
}

template <class Comparable>
void heapsort(vector<Comparable>& a)
{
      for (int i = a.size() / 2; i >= 0; i--)  
          percDown(a, i, a.size());
      for (int j = a.size() - 1; j > 0; j--)
    {
         swap(a[0], a[j]);                  
          percDown(a, 0, j);
    }
}

inline int leftChild(int i)
{
    return 2 * i + 1;
}

template <class Comparable>
void percDown(vector<Comparable>& a, int i, int n)
{
    int child;
    Comparable tmp;

      for (tmp = a[i]; leftChild(i) < n; i = child)
    {
          child = leftChild(i);
          if (child != n - 1 && a[child] < a[child + 1])
              child++;
          if (tmp < a[child])
              a[i] = a[child];
        else
              break;
    }
      a[i] = tmp;
}


/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <class Comparable>
void mergeSort(vector<Comparable>& a, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a,left, center);
        mergeSort(a, center + 1, right);
        merge(a,left, center + 1, right);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <class Comparable>
void merge(vector<Comparable>& a, int leftPos, int rightPos, int rightEnd){
    int leftEnd = rightPos - 1;
    int numElements = rightEnd - leftPos + 1;

    if (a[leftEnd] <= a[rightPos]) {
        return;
    }
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos]) {
            leftPos++;
        }
        else {
            PhoneBook val = a[rightPos];
            int tmpPos = rightPos;
            while (tmpPos != leftPos) {
                a[tmpPos] = a[tmpPos - 1];
                tmpPos--;
            }
            a[leftPos] = val;
            leftPos++;
            leftEnd++;
            rightPos++;
        }
    }
   
}


/**
 * Quicksort algorithm (driver).
 */
template <class Comparable>
void quicksort(vector<Comparable>& a)
{
    quicksort(a, 0, a.size() - 1);
}

/**
 * Standard swap
 */
template <class Comparable>
inline void swap(Comparable& obj1, Comparable& obj2)
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <class Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
    int center = (left + right) / 2;
    if (a[center] < a[left])
        swap(a[left], a[center]);
    if (a[right] < a[left])
        swap(a[left], a[right]);
    if (a[right] < a[center])
        swap(a[center], a[right]);

    // Place pivot at position right - 1
    swap(a[center], a[right - 1]);
    return a[right - 1];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <class Comparable>
void quicksort(vector<Comparable>& a, int left, int right)
{
      if (left + 10 <= right)
    {
          Comparable pivot = median3(a, left, right);

        // Begin partitioning
          int i = left, j = right - 1;
          for (; ; )
        {
              while (a[++i] < pivot) {}
              while (pivot < a[--j]) {}
              if (i < j)
                  swap(a[i], a[j]);
            else
                  break;
        }

          swap(a[i], a[right - 1]);  // Restore pivot

          quicksort(a, left, i - 1);     // Sort small elements
          quicksort(a, i + 1, right);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
          insertionSort(a, left, right);
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
    for (int p = left + 1; p <= right; p++)
    {
        Comparable tmp = a[p];
        int j;

        for (j = p; j > left && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <class Comparable>
void quickSelect(vector<Comparable>& a, int k)
{
    quickSelect(a, 0, a.size() - 1, k);
}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <class Comparable>
void quickSelect(vector<Comparable>& a, int left, int right, int k)
{
      if (left + 10 <= right)
    {
         Comparable pivot = median3(a, left, right);


          int i = left, j = right - 1;
          for (; ; )
        {
              while (a[++i] < pivot) {}
              while (pivot < a[--j]) {}
             if (i < j)
                  swap(a[i], a[j]);
            else
                  break;
        }

        /*10*/          swap(a[i], a[right - 1]);  // Restore pivot

                            // Recurse; only this part changes
        /*11*/          if (k <= i)
            /*12*/              quickSelect(a, left, i - 1, k);
        /*13*/          else if (k > i + 1)
            /*14*/              quickSelect(a, i + 1, right, k);
    }
    else  // Do an insertion sort on the subarray
        /*15*/          insertionSort(a, left, right);
}

void createVectors(string fname) {
    ifstream in;
    string line,word, nameAndSurnameOfUser="",city, phoneNum,name,surname;
    cout << "Fname: " << fname << endl;
    in.open(fname.c_str());
    while(getline(in,line)){
        istringstream ss(line);
        ss >> word;
        name = UpperString(word);
        nameAndSurnameOfUser += word+" ";
        ss >> word;
        surname = UpperString(word);
        nameAndSurnameOfUser += word;
        ToUpper(nameAndSurnameOfUser);
        ss >> word;
        phoneNum = word;
        ss >> word;
        city =word;
        PhoneBook newPerson(name, surname, city, phoneNum,nameAndSurnameOfUser);
        insertSortVec.push_back(newPerson);
        quickSortVec.push_back(newPerson);
        mergeSortVec.push_back(newPerson);
        heapSortVec.push_back(newPerson);
        nameAndSurnameOfUser = "";
        city = "";
        phoneNum = "";
        name = "";
        surname = "";
    }
    in.close();
}

string getUserKeyboardValue() {
    //cin.ignore();
    cin.clear();
    char userValue[1000];
    cin.getline(userValue, 1000);
    return userValue;
}

void waitChoice(string& wordsForSearch) {
    wordsForSearch = getUserKeyboardValue();
}

template <class Comparable>
bool sequentialSearch(Comparable sWord, vector<Comparable> & insertSortVec) {
    bool existC = false;
    for (int i = 0; i < insertSortVec.size(); i++) {
        if (insertSortVec[i] == sWord) {
            existC = true;
            cout << insertSortVec[i] << endl;
        }
    }

    return existC;
}

template <class Comparable>
bool binarySearch(Comparable sWord, vector<Comparable>& insertSortVec,int &mid)
{
      int low = 0, high = insertSortVec.size() - 1;

      while (low <= high){

          mid = (low + high) / 2;

          if (insertSortVec[mid] < sWord) {
              low = mid + 1;
          }
          else if (insertSortVec[mid] > sWord) {
              high = mid - 1;
          }
              
          else {
              int i = 1;

              while ((mid - i) >= 0 && insertSortVec[mid - i] == sWord) {
                  cout << insertSortVec[mid - i] << endl;
                  i++;
              }

              cout << insertSortVec[mid] << endl;

              i = 1;

              while ((mid + i) < insertSortVec.size() && insertSortVec[mid + i] == sWord) {
                  cout << insertSortVec[mid + i] << endl;
                  i++;
              }
              return true;
          }
              
    }
      return false;


}


void calculateTimes(long long& insertionSortTime, long long& heapSortTime, long long& mergeSortTime, long long& quickSortTime) {
    int k = 20;
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(insertSortVec);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    insertionSortTime = duration.count();

    k = 20;
    start = std::chrono::high_resolution_clock::now();
    heapsort(heapSortVec);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    heapSortTime = duration.count();


    k = 20;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSortVec, 0, mergeSortVec.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    mergeSortTime = duration.count();

     k = 20;
    start = std::chrono::high_resolution_clock::now();
    quicksort(quickSortVec);
     end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    quickSortTime = duration.count();
}

void printTimes(long long& insertionSortTime, long long& heapSortTime, long long& mergeSortTime, long long& quickSortTime) {
    cout << "Quick Sort Time: " << quickSortTime  <<" Nanoseconds "<< endl;
    cout << "Insertion Sort Time : " << insertionSortTime << " Nanoseconds" << endl;
    cout << "Merge Sort Time : " << mergeSortTime << " Nanoseconds" << endl;
    cout << "Heap Sort Time : " << heapSortTime <<" Nanoseconds" << endl;
}


void printSpeedUps(long long& insertionSortTime, long long& heapSortTime, long long& mergeSortTime, long long& quickSortTime,long long & binarySearchTime,long long &sequentialSearchTime) {
    cout << "SpeedUp between Search Algorithms " << endl;
    cout << " ======================================" << endl;
    cout << "(Sequential Search/ Binary Search) SpeedUp = " << double(sequentialSearchTime)/binarySearchTime << endl << endl;
    cout << "SpeedUps between Sorting Algorithms " << endl;
    cout << "======================================" << endl;
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << double(insertionSortTime) / quickSortTime << endl;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << double(mergeSortTime) / quickSortTime << endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << double(heapSortTime) / quickSortTime << endl;
}

int main() {
    string fname="", searchWord="";
    long long insertionSortTime = 0,heapSortTime=0,mergeSortTime=0,quickSortTime=0,binarySearchTime=0,sequentialSearchTime=0;
    cout << "Please enter the contact file name: " ;
    waitChoice(fname);
    cout << "Please enter the word to be queried :";
    waitChoice(searchWord);
 
    createVectors(fname);

    cout << "Sorting the vector copies" << endl << endl;

    calculateTimes(insertionSortTime, heapSortTime, mergeSortTime, quickSortTime);
    printTimes(insertionSortTime, heapSortTime, mergeSortTime, quickSortTime);

    cout << "======================================" << endl;
    cout << "Searching for " << searchWord << endl;
    cout << "======================================" << endl<< endl;

    ToUpper(searchWord);
    PhoneBook searchWordB(searchWord, "", "", "", searchWord);

    int mid = 0;

    int k = 20;
    auto start = std::chrono::high_resolution_clock::now();
    bool ifExists= binarySearch(searchWordB, insertSortVec, mid);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    binarySearchTime = duration.count();

    if (!ifExists) {
        cout << searchWord << " does NOT exist in the dataset" << endl;
    }

    cout << endl << "Binary Search Time: " << binarySearchTime << endl;
    
    cout << "********" << endl;


    k = 20;
    start = std::chrono::high_resolution_clock::now();
    ifExists = sequentialSearch(searchWordB, insertSortVec);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    sequentialSearchTime = duration.count();


    if (!ifExists) {
        cout << "Search results for Sequential Search: " << endl;
        cout << searchWord << " does NOT exist in the dataset" << endl;
    }

    cout << endl << "Sequential Search Time: " << sequentialSearchTime <<  endl << endl;

    printSpeedUps(insertionSortTime, heapSortTime, mergeSortTime, quickSortTime, binarySearchTime, sequentialSearchTime);
 

	return 0;
}