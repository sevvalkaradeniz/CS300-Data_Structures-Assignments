#include <iostream>
#include <string>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "strutils.h"
#include <fstream>
#include <sstream>
#include<chrono>

using namespace std;


WordItem tempH("notFoundH");
WordItem tempB("notFoundB");
HashTable<WordItem> hTable(tempH,53);
BinarySearchTree<WordItem> bTree(tempB);

string organizeSearchWord(string wordsForSearch) {
	string finalForm = "";
	ToLower(wordsForSearch);
	string searchW = "";
	for (unsigned int i = 0; i < wordsForSearch.length(); i++) {
		if ('a' <= wordsForSearch[i] && 'z' >= wordsForSearch[i]) {
			searchW += wordsForSearch[i];
		}
		else {
			if (searchW != "" && 'a' <= searchW[0] && 'z' >= searchW[0]) {

				finalForm += searchW + " ";
			}
			searchW = "";
		}
	}
	if (searchW != "" && 'a' <= searchW[0] && 'z' >= searchW[0]) {
		finalForm += searchW;
		
	}

	return finalForm;

}

void insertForHash(string currW, string fname){
	if (currW != "" && 'a' <= currW[0] && 'z' >= currW[0] && hTable.find(currW).word == "notFoundH") {
		DocumentItem d(fname, 1);
		WordItem w(currW);
		w.docVec.push_back(d);
		hTable.insert(w);
	}
	else if(currW!="" && 'a' <= currW[0] && 'z' >= currW[0]) {
		bool check = false;
		int idx = hTable.findPos(currW);
		int sizeOfInnerVec = hTable.array[idx].element.docVec.size();
		for (int k = 0; k < sizeOfInnerVec; k++) {
			if (hTable.array[idx].element.docVec[k].documentName == fname) {
				hTable.array[idx].element.docVec[k].count++;
				check = true;
				k = sizeOfInnerVec;
			}
		}
		if (!check) {
			DocumentItem d(fname, 1);
			hTable.array[idx].element.docVec.push_back(d);
		}

	}
}
void insertForBST(string currW, string fname) {
	if (currW != "" && 'a' <= currW[0] && 'z' >= currW[0] && bTree.find(currW).word == "notFoundB") {
		DocumentItem d(fname, 1);
		WordItem w(currW);
		w.docVec.push_back(d);
		bTree.insert(w);
	}
	else if (currW != "" && 'a' <= currW[0] && 'z' >= currW[0]) {
		bool check = false;
		BinaryNode<WordItem> * t = bTree.findNode(currW);
		int sizeOfInnerVec = t->element.docVec.size();
		for (int k = 0; k < sizeOfInnerVec; k++) {
			if (t->element.docVec[k].documentName == fname) {
				t->element.docVec[k].count++;
				check = true;
				k = sizeOfInnerVec;
			}
		}
		if (!check) {
			DocumentItem d(fname, 1);
			t->element.docVec.push_back(d);
		}
	

	}
}

void readFileForBoth(string fname){
	ifstream input;
	string line,word="",currW="";
	input.open(fname.c_str());
	while (getline(input, line)) {
		ToLower(line);
		istringstream ss(line);
		while (ss >> word) {
			for (unsigned int i = 0; i < word.length(); i++) {
				if ('a' <= word[i] && 'z' >= word[i]) {
					currW += word[i];
				}
				else {
					insertForHash(currW, fname);
					insertForBST(currW, fname);
					currW = "";
				}
			}
			
			insertForHash(currW, fname);
			insertForBST(currW, fname);
			currW = "";
		}
	}
	input.close();
}

void fileNames(string fnames) {
	string fileN="";
	istringstream ssf(fnames);
	while (ssf >> fileN) {

		readFileForBoth(fileN);
	}
}

bool checkIfWordExists(string finalWord, string fname) {

	if(hTable.find(finalWord).word == "notFoundH"){
		return false;
	}
	int idx = hTable.findPos(finalWord);
	int sizeOfInnerVec = hTable.array[idx].element.docVec.size();

	for (int k = 0; k < sizeOfInnerVec; k++) {
		if (hTable.array[idx].element.docVec[k].documentName == fname) {
			return true;
		}
	}
	return false;
}
bool checkIfWordExistsBST(string finalWord, string fname) {

	if (bTree.find(finalWord).word == "notFoundB") {
		return false;
	}
	BinaryNode<WordItem>* t = bTree.findNode(finalWord);
	int sizeOfInnerVec = t->element.docVec.size();

	for (int k = 0; k < sizeOfInnerVec; k++) {
		if ((t->element.docVec[k].documentName == fname)) {
			return true;
		}
	}
	return false;
}

int findCount(string finalWord, string fname) {

	int idx = hTable.findPos(finalWord);
	int sizeOfInnerVec = hTable.array[idx].element.docVec.size();

	for (int k = 0; k < sizeOfInnerVec; k++) {
		if (hTable.array[idx].element.docVec[k].documentName == fname) {
			return hTable.array[idx].element.docVec[k].count;
		}
	}

}
int findCountBST(string finalWord, string fname) {

	BinaryNode<WordItem>* t = bTree.findNode(finalWord);
	int sizeOfInnerVec = t->element.docVec.size();

	for (int k = 0; k < sizeOfInnerVec; k++) {
		if (t->element.docVec[k].documentName == fname) {
			return t->element.docVec[k].count;
		}
	}

}

bool checkIfAllWordsExistsInFile(string seperatedWords, string fileN) {
	bool checkW = true;
	istringstream ssw(seperatedWords);
	string searchW = "";
	while (ssw >> searchW) {

		if (!checkIfWordExists(searchW, fileN)) {
			checkW = false;
			return checkW;
		}
	}
	return checkW;
	
}
bool checkIfAllWordsExistsInFileBST(string wordsForSearch, string fileN) {
	bool checkW = true;
	string seperatedWords = organizeSearchWord(wordsForSearch);
	istringstream ssw(seperatedWords);
	string searchW = "";
	while (ssw >> searchW) {

		if (!checkIfWordExistsBST(searchW, fileN)) {
			checkW = false;
			return checkW;
		}
	}
	return checkW;

}

void printInfoForWordsBST(string wordsForSearch, string allFNames) {
	string seperatedWords= organizeSearchWord(wordsForSearch);
	string fileN = "",word="";
	bool check = false;
	istringstream ssf(allFNames);
	//istringstream ssw(seperatedWords);
	while (ssf >> fileN) {
		if (checkIfAllWordsExistsInFileBST(wordsForSearch, fileN)) {
			cout << "in Document " << fileN;
			check = true;
			istringstream ssw(seperatedWords);
			while (ssw >> word) {
				int countW = findCountBST(word, fileN);
				cout<< ", " << word << " found " << countW << " times ";
			}
		}
		cout << endl;
	}
	if (!check) {
		cout << "No document contains the given query" << endl;
	}
}

void printInfoForWords(string wordsForSearch, string allFNames) {
	string seperatedWords = organizeSearchWord(wordsForSearch);
	string fileN = "", word = "";
	bool check = false;
	istringstream ssf(allFNames);
	//istringstream ssw(seperatedWords);
	while (ssf >> fileN) {
		if (checkIfAllWordsExistsInFile(seperatedWords, fileN)) {
			cout << "in Document " << fileN;
			check = true;
			istringstream ssw(seperatedWords);
			while (ssw >> word) {
				int countW = findCount(word, fileN);
				cout << ", " << word << " found " << countW << " times ";
			}
		}
		cout << endl;
	}
	if (!check) {
		cout << "No document contains the given query" << endl;
	}
}

string getUserKeyboardValue() {	
	char userValue[500];
	cin.ignore();
	cin.clear();
	cin.getline(userValue, 500);
	return userValue;
}

void waitChoice(string& wordsForSearch) {
	wordsForSearch = getUserKeyboardValue();
}

int main()
{
	int numOfFile;
	long long BSTTime = 0, HTTime=0;
	string fileName, allFNames, wordsForSearch="";
	cout << "Enter number of input files: ";
	cin >> numOfFile;

	for (int i = 1; i <= numOfFile; i++) {
		cout << "Enter " << i << " . file name: ";
		cin >> fileName;
		allFNames += fileName + " ";
	}
	fileNames(allFNames);
	double loadFactor = (double(hTable.currentSize) / hTable.array.size());
	cout << endl << "After preprocessing, the unique word count is " << hTable.currentSize  << " Current load ratio is " << loadFactor << endl;
	cout << "Enter queried words in one line: ";
	waitChoice(wordsForSearch);
	//cin >> wordsForSearch;

	int k = 20;
	auto start = std::chrono::high_resolution_clock::now();
	printInfoForWordsBST(wordsForSearch, allFNames);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	BSTTime = duration.count();


	start = std::chrono::high_resolution_clock::now();
	printInfoForWords(wordsForSearch, allFNames);
	end = std::chrono::high_resolution_clock::now();
	 duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	HTTime = duration.count();

	cout << "\nTime: " << BSTTime / k << "\n";
	cout << "\nTime: " << HTTime / k << "\n";
	cout << "Speed Up: " << double(BSTTime) / HTTime << endl;

	return 0;
}
