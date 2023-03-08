#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "BinarySearchTree.h"
#include "AVLTree.h"
using namespace std;

#define choice_displaySectionAVL ("1")
#define choice_displaySectionBST ("2")
#define choice_selectSection ("3")
#define choice_addNewSection ("4")
#define choice_deleteSection ("5")
#define choice_exit ("6")
#define innerChoice_displayItemsAVL ("1")
#define innerChoice_displayItemsBST ("2")
#define innerChoice_displayInformationOfItem ("3")
#define innerChoice_addnewItem ("4")
#define innerChoice_updateInformationOfItem ("5")
#define innerChoice_deleteItem ("6")
#define innerChoice_returnToMainMenu ("7")
#define continueSectionTasks(var) (var == choice_displaySectionAVL || var == choice_displaySectionBST || var == choice_selectSection || var == choice_addNewSection || var == choice_deleteSection)
#define acceptedTasksForMainMenu(var) (continueSectionTasks(var) || var == choice_exit)
#define maxUserKeyboardValueLength (500)

class ItemS
{
public:
    ItemS(string section="notFound", string item="notFound", string info="notFound") //constructor for items
        :section(section),item(item),info(info)
    {}

    bool Less(const ItemS & rhs)const{   // function for < operator  
        if(item<rhs.item){
            return true;
        }
        return false;
    }
    string getItem()const;
    string getInfo()const{
        return info;
    }
    string getSection()const{
        return section;
    }


private:
    string item,info,section;
};

ostream & operator << (ostream & os, const ItemS & s){
    ostringstream ostr;
    ostr << s.getItem();
    os << ostr.str();
    return os;
};

string ItemS::getItem()const{
    return item;
}

bool operator < (const ItemS & lhs,const ItemS  & rhs){
    return lhs.Less(rhs);
}

bool operator > (const ItemS & rhs,const ItemS & lhs){
    return lhs<rhs;
}

class Sections{
public:
    Sections(string title="notFound",AvlTree<ItemS> *pAvl=NULL)
        :title(title),pItemAvlTree(pAvl)
    {}

    Sections(string title="notFound",BinarySearchTree<ItemS> *pBST=NULL)
        :title(title),pItemBSTree(pBST)
    {}

    bool Less(const Sections & rhs)const{
    if(title<rhs.title){
        return true;
    }
    return false;
    }

    BinarySearchTree<ItemS>  *getItemBinarySearchTree()const{
        return pItemBSTree;
    }

    AvlTree<ItemS>  *getItemAvlTree()const{
        return pItemAvlTree;
    }

    string getTitle()const{
        return title;
    }
private:
    string title;
    BinarySearchTree<ItemS> *pItemBSTree;
    AvlTree<ItemS> *pItemAvlTree;
};

ostream & operator << (ostream & os, const Sections & s){
    ostringstream ostr;
    ostr << s.getTitle();
    os << ostr.str();
    return os;
};
bool operator < (const Sections & lhs,const Sections  & rhs){
    return lhs.Less(rhs);
}

bool operator > (const Sections & rhs,const Sections & lhs){
    return lhs<rhs;
}

void createBT(BinarySearchTree<Sections> & BTForAll,AvlTree<Sections> & BTForAvl){

    ItemS tempbegin("notFound","notFound","notFound");
    BinarySearchTree<ItemS> *BinaryTree = new BinarySearchTree<ItemS>(tempbegin,NULL);
    long long usTimeElapsedValueBST = 0;
    AvlTree<ItemS> *AVLTree = new AvlTree<ItemS>(tempbegin,NULL);
    long long usTimeElapsedValueAVL = 0;


    string fname="data.txt",line,section="",word="",item,info="";
    bool check=false;
    ifstream in;
    in.open(fname.c_str());
    while(getline(in,line)){
        info="";
        if(line.find("-")==string::npos){ //for get section title 
            if(check){ //if it create a  tree for item part
                Sections newSectionAVL = Sections(section,AVLTree); // create a section with tree for items
                auto start = std::chrono::high_resolution_clock::now(); // start time

                BTForAvl.insert(newSectionAVL); // insert inner to outer tree for sections in AVL tree

                auto end = std::chrono::high_resolution_clock::now(); // end time
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                usTimeElapsedValueAVL+=duration.count();
                cout << "Section "<< section <<" has been inserted into the AVL notebook." << endl;
                cout <<"[AVL] Elapsed time: "<< usTimeElapsedValueAVL <<" microseconds " << endl;

                ItemS tempAVL("notFound","notFound","notFound");
                AVLTree = new AvlTree<ItemS>(tempAVL,NULL);
                usTimeElapsedValueAVL = 0;

                Sections newSectionBST = Sections(section,BinaryTree); // create a section with tree for items
                start = std::chrono::high_resolution_clock::now(); // start time

                BTForAll.insert(newSectionBST); // insert inner to outer tree for sections in binary tree

                end = std::chrono::high_resolution_clock::now(); // end time
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                usTimeElapsedValueBST+=duration.count();
                cout << "Section "<< section <<" has been inserted into the BST notebook." << endl;
                cout <<"[BST] Elapsed time: "<< usTimeElapsedValueBST <<" microseconds " << endl;
                cout <<"" << endl;
                cout <<"" << endl;

                ItemS tempBST("notFound","notFound","notFound");
                BinaryTree = new BinarySearchTree<ItemS>(tempBST,NULL);                
                usTimeElapsedValueBST = 0;
            }
            section=line;
            check=true;
            //cout << "section is: " << section << endl;
        }
        else{
            int idx= line.find("-");
            int idxR =line.rfind("-");
            item = line.substr(idx+1,idxR-idx-1); //getting item
            //cout << "item is :" <<item << "a"<< endl;
            info=line.substr(idxR+1);
        }
        //cout << "info is :" << info << endl;
        if(info!=""){ 
            //cout << "item: " << item << " Section: " << section << " info: " << info <<endl;
            ItemS myItem(section, item, info); // creating struct for items tree
            auto start = std::chrono::high_resolution_clock::now(); // start time

            AVLTree->insert(myItem); // inserting item and info together in avl tree

            auto end = std::chrono::high_resolution_clock::now(); // end time
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            usTimeElapsedValueAVL+=duration.count();

            start = std::chrono::high_resolution_clock::now(); // start time

            BinaryTree->insert(myItem); // inserting item and info together in binary tree

            end = std::chrono::high_resolution_clock::now(); // end time
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            usTimeElapsedValueBST+=duration.count();
        }
    }
    Sections newSectionAVL = Sections(section,AVLTree);
    auto start = std::chrono::high_resolution_clock::now(); // start time

    BTForAvl.insert(newSectionAVL); // inserting last section to avl

    auto end = std::chrono::high_resolution_clock::now(); // end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    usTimeElapsedValueAVL+=duration.count();
    cout << "Section "<< section <<" has been inserted into the AVL notebook." << endl;
    cout <<"[AVL] Elapsed time: "<< usTimeElapsedValueAVL <<" microseconds " << endl;

    Sections newSection = Sections(section,BinaryTree);
    start = std::chrono::high_resolution_clock::now(); // start time

    BTForAll.insert(newSection); // inserting last section to binary

    end = std::chrono::high_resolution_clock::now(); // end time
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    usTimeElapsedValueBST+=duration.count();
    cout << "Section "<< section <<" has been inserted into the BST notebook." << endl;
    cout <<"[BST] Elapsed time: "<< usTimeElapsedValueBST <<" microseconds " << endl;
    cout <<"" << endl;
    cout <<"" << endl;
    in.close();
}

void Display_the_sections_AvlTree(AvlTree<Sections> & BTForAvl){ //calling print tree function to printing avl tree (sections)
    cout << " " << endl;
    cout << "*****" << endl;
    BTForAvl.printTree();
    cout << "*****" << endl;
    cout << " " << endl;
}

void Display_the_sections_BST(BinarySearchTree<Sections> & BTForAll){ //calling print tree function to printing binary tree (sections)
    cout << " " << endl;
    cout << "*****" << endl;
    BTForAll.printTree();
    cout << "*****" << endl;
    cout << " " << endl;
}

void Display_the_items_AVL(AvlTree<ItemS> *pItemAvlTree){ //calling print tree function for item names of avl tree
    cout << " " << endl;
    cout << "*****" << endl;
    pItemAvlTree->printTree();
    cout << "*****" << endl;
    cout << " " << endl;
}

void Display_the_items_BST(BinarySearchTree<ItemS> *pItemBSTree){ //calling print tree function for item names of binary tree
    cout << " " << endl;
    cout << "*****" << endl;
    pItemBSTree->printTree();
    cout << "*****" << endl;
    cout << " " << endl;
}

bool Select_a_section(AvlTree<Sections> & BTForAvl, BinarySearchTree<Sections> & BTForAll,string sectionTitle,BinarySearchTree<ItemS> **pItemBSTree,AvlTree<ItemS> **pItemAvlTree){
    BinarySearchTree<ItemS> *pBST=NULL;
   Sections s1(sectionTitle,pBST); //creating section for using find function
    string val = BTForAll.find(s1).getTitle(); // checking if given title exists in the binary tree
    if(val == "notFound"){ // if title is invalid
        pItemBSTree = NULL;
        pItemAvlTree = NULL;
        return false;
    }
    *pItemBSTree = BTForAll.find(s1).getItemBinarySearchTree(); //if title is valid we are getting Items tree pointer
    *pItemAvlTree = BTForAvl.find(s1).getItemAvlTree(); //if title is valid we are getting Items tree pointer
    return true;
}


bool Select_a_section(BinarySearchTree<Sections> & BTForAll,string sectionTitle){
    BinarySearchTree<ItemS> *pBST=NULL;
    Sections s1(sectionTitle,pBST);
    string val=BTForAll.find(s1).getTitle();
    if(val=="notFound"){
        return false;
    }
    return true;
}

bool Display_information_of_item(string itemTitle,BinarySearchTree<ItemS> *pItemBSTree,AvlTree<ItemS> *pItemAvlTree){
    ItemS t("notFound",itemTitle,"notFound");
    auto start = std::chrono::high_resolution_clock::now(); // start time

    string val = pItemAvlTree->find(t).getItem();

    auto end = std::chrono::high_resolution_clock::now(); // end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    long long usTimeElapsedValue = duration.count();
    cout <<"[AVL] Elapsed time: "<< usTimeElapsedValue <<" microseconds " << endl;

    start = std::chrono::high_resolution_clock::now(); // start time

    string val2 = pItemBSTree->find(t).getItem();

    end = std::chrono::high_resolution_clock::now(); // end time
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    usTimeElapsedValue = duration.count();
    cout <<"[BST] Elapsed time: "<< usTimeElapsedValue <<" microseconds " << endl;

    if ((val=="notFound") || (val2=="notFound")){
        cout << "Invalid title." << endl;
        cout <<"" << endl;
        return false;
    }
    else{
        cout << pItemBSTree->find(t).getInfo()<<endl;
        cout <<"" << endl;
        return true;
    }
}

string getUserKeyboardValue() {
    char userValue[maxUserKeyboardValueLength];
    cin.getline(userValue,maxUserKeyboardValueLength);
    return userValue;
}

void waitChoice(string &choice) {
    cout << "Input: ";
    choice = getUserKeyboardValue();
}

void outOfHomeworkButNeedForWrongUserEntry(string &choice) {
    cout << "This message is not defined in Homework -> user selection is out of range..." << endl;
    cout << " " << endl;
    waitChoice(choice);
}

int main(){

   string choice;
    string innerChoice;
    string sectionTitle,itemTitle,itemProperties,itemUpdateInformation;
    AvlTree<ItemS> *pAVL=NULL;
    Sections NotebookSectionAVL("notFound",pAVL);
    AvlTree<Sections> BTForAvl = AvlTree<Sections>(NotebookSectionAVL,NULL);
    BinarySearchTree<ItemS> *pBST=NULL;
    Sections NotebookSection("notFound",pBST);
    BinarySearchTree<Sections> BTForAll = BinarySearchTree<Sections>(NotebookSection,NULL);
    BinarySearchTree<ItemS> *pSelectedSectionItemBSTree = NULL;
    AvlTree<ItemS> *pSelectedSectionItemAvlTree = NULL;
    bool exitActivated = false;

    cout << "Welcome to the Notebook!" << endl;
    cout <<"" << endl;
    cout <<"" << endl;
    createBT(BTForAll,BTForAvl);

    cout << "MENU \nPlease enter an input between [1 - 6]: \n1- Display the sections [AVL] \n2- Display the sections [BST]\n3- Select a section \n4- Add new section\n5- Delete a section\n6- Exit" << endl;
    waitChoice(choice);

     while (!exitActivated) {

        if(choice == choice_displaySectionAVL){
            Display_the_sections_AvlTree(BTForAvl);
            waitChoice(choice);
        }
        else if(choice == choice_displaySectionBST){
            Display_the_sections_BST(BTForAll);
            waitChoice(choice);
        }
        else if(choice == choice_selectSection){
            cout << "Enter the title of the section: ";
            sectionTitle = getUserKeyboardValue();

            if(!Select_a_section(BTForAvl,BTForAll,sectionTitle,&pSelectedSectionItemBSTree,&pSelectedSectionItemAvlTree)){
                cout << "Invalid title!" << endl;
                cout <<"" << endl;
                waitChoice(choice);
            }
            else{
                cout << " " << endl;
                cout << "Selected section -> " << sectionTitle << endl;
                cout << "Please enter an input between [1 - 7]:\n1- Display the items [AVL]\n2- Display the items [BST]\n3- Display the information of a item\n4- Add new item\n5- Update the information of a item\n6- Delete an item\n7- Return to main menu"<<endl;
                waitChoice(innerChoice);
                while (innerChoice != innerChoice_returnToMainMenu){

                    if (innerChoice == innerChoice_displayItemsAVL) { //display item in AVL
                        Display_the_items_AVL(pSelectedSectionItemAvlTree);
                        waitChoice(innerChoice);
                    }
                    else if (innerChoice == innerChoice_displayItemsBST) {  //display item in BST
                        Display_the_items_BST(pSelectedSectionItemBSTree);
                        waitChoice(innerChoice);
                    }
                    else if (innerChoice == innerChoice_displayInformationOfItem) {   //display the information of item
                        cout << "Enter the title of the item: ";
                        itemTitle = getUserKeyboardValue();
                        Display_information_of_item(itemTitle,pSelectedSectionItemBSTree,pSelectedSectionItemAvlTree);
                        waitChoice(innerChoice);
                    }
                    else if (innerChoice == innerChoice_addnewItem) {  // Add new item
                        cout << "Enter a title for the item: ";
                        itemTitle = getUserKeyboardValue();
                        ItemS myItem("notFound", itemTitle, "notFound");
                        if (pSelectedSectionItemBSTree->find(myItem).getItem() != "notFound") {
                            cout << "Item "<< itemTitle <<" already exists in the "<<sectionTitle<<"." << endl;
                            cout << " "<< endl;
                            waitChoice(innerChoice);
                        }
                        else {
                            cout << "Enter a description for the item: ";
                            itemProperties = getUserKeyboardValue();
                            ItemS myItem2(sectionTitle, itemTitle, itemProperties);
                            auto start = std::chrono::high_resolution_clock::now(); // start time
                            pSelectedSectionItemAvlTree->insert(myItem2);

                            auto end = std::chrono::high_resolution_clock::now(); // end time
                            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                            long long usTimeElapsedValue = duration.count();
                            cout <<"[AVL] Elapsed time: "<< usTimeElapsedValue <<" microseconds " << endl;
                            start = std::chrono::high_resolution_clock::now(); // start time


                            pSelectedSectionItemBSTree->insert(myItem2);

                            end = std::chrono::high_resolution_clock::now(); // end time
                            duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                            usTimeElapsedValue = duration.count();
                            cout <<"[BST] Elapsed time: "<< usTimeElapsedValue <<" microseconds " << endl;
                            cout <<"The new item "<< itemTitle <<" has been inserted." << endl;
                            cout << " "<< endl;
                            waitChoice(innerChoice);
                        }
                    }
                    else if (innerChoice == innerChoice_updateInformationOfItem) { // Update information of item
                        cout << "Enter the title of the item: ";
                        itemTitle = getUserKeyboardValue();
                        ItemS myItem("notFound", itemTitle, "notFound");
                        bool founded = false;
                        auto start = std::chrono::high_resolution_clock::now(); // start time

                        founded = (pSelectedSectionItemBSTree->find(myItem).getItem() != "notFound");

                        auto end = std::chrono::high_resolution_clock::now(); // end time
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                        long long usTimeElapsedValueBST = duration.count();

                        start = std::chrono::high_resolution_clock::now(); // start time

                        pSelectedSectionItemAvlTree->find(myItem).getItem();

                        end = std::chrono::high_resolution_clock::now(); // end time
                        duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                        long long usTimeElapsedValueAVL = duration.count();
                        cout <<"[AVL] Elapsed time: "<< usTimeElapsedValueAVL <<" microseconds " << endl;
                        cout <<"[BST] Elapsed time: "<< usTimeElapsedValueBST <<" microseconds " << endl;

                        if (!founded) {
                            cout << "Item " << itemTitle << " does not exist in the "<<sectionTitle<<"." << endl;
                            cout << " "<< endl;
                            waitChoice(innerChoice);
                        }
                        else {
                            cout << "Enter the new information: ";
                            itemUpdateInformation = getUserKeyboardValue();
                            ItemS myItem(sectionTitle, itemTitle, itemUpdateInformation);
                            pSelectedSectionItemBSTree->update(myItem);
                            pSelectedSectionItemAvlTree->update(myItem);
                            cout << "The content " << itemTitle << " has been updated." << endl;
                            cout << " "<< endl;
                            waitChoice(innerChoice);
                        }
                    }
                    else if (innerChoice == innerChoice_deleteItem) { // Delete an item
                        cout << "Enter the title of the item: ";
                        itemTitle = getUserKeyboardValue();
                        ItemS myItem("notFound", itemTitle, "notFound");
                        if (pSelectedSectionItemBSTree->find(myItem).getItem() == "notFound") {
                            cout << "Item "<< itemTitle <<" does not exist in the "<<sectionTitle<<"." << endl;
                            cout << " "<< endl;
                            waitChoice(innerChoice);
                        }
                        else {
                            ItemS myItem(sectionTitle, itemTitle, itemProperties);
                            auto start = std::chrono::high_resolution_clock::now(); // start time

                            pSelectedSectionItemAvlTree->remove(pSelectedSectionItemAvlTree->find(myItem));

                            auto end = std::chrono::high_resolution_clock::now(); // end time
                            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                            long long usTimeElapsedValue = duration.count();
                            cout <<"[AVL] Elapsed time: "<< usTimeElapsedValue <<" microseconds " << endl;
                            start = std::chrono::high_resolution_clock::now(); // start time

                            pSelectedSectionItemBSTree->remove(pSelectedSectionItemBSTree->find(myItem));

                            end = std::chrono::high_resolution_clock::now(); // end time
                            duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
                            usTimeElapsedValue = duration.count();
                            cout <<"[BST] Elapsed time: "<< usTimeElapsedValue <<" microseconds " << endl;
                            cout << "The item "<<itemTitle<<" has been deleted." << endl;
                            cout << " " << endl;
                            waitChoice(innerChoice);
                        }
                    }
                    else { // if user will enter wrong value that is out of range
                        outOfHomeworkButNeedForWrongUserEntry(innerChoice);
                    }
                }
                // Return the main menu
                cout << "MENU \nPlease enter an input between [1 - 6]: \n1- Display the sections [AVL] \n2- Display the sections [BST]\n3- Select a section \n4- Add new section\n5- Delete a section\n6- Exit" << endl;
                waitChoice(choice);
                while (!acceptedTasksForMainMenu(choice)) {
                    outOfHomeworkButNeedForWrongUserEntry(choice);
                }
            }
        }
        else if(choice == choice_addNewSection){ // add new section
            string newSectionTitle;
            cout << "Enter a title for the section: ";
            newSectionTitle = getUserKeyboardValue();
            if(Select_a_section(BTForAll,newSectionTitle)){
                cout << "Section: " << newSectionTitle << " already exists" << endl;
                cout << " " << endl;
                waitChoice(choice);
            }
            else {
                ItemS tempbegin("notFound","notFound","notFound");
                BinarySearchTree<ItemS> *BinaryTree = new BinarySearchTree<ItemS>(tempbegin,NULL);
                Sections newSection = Sections(newSectionTitle,BinaryTree);
                BTForAll.insert(newSection); // insert in BST

                AvlTree<ItemS> *AVLTree = new AvlTree<ItemS>(tempbegin,NULL);
                Sections newSectionAVL = Sections(newSectionTitle,AVLTree);
                BTForAvl.insert(newSectionAVL); // insert in AVL
                cout << "The new section " << newSectionTitle << " has been inserted." << endl;
                cout << " " << endl;
                waitChoice(choice);
            }
        }
        else if(choice == choice_deleteSection){ // Delete section
            cout << "Enter the title of the section: " ;
            sectionTitle = getUserKeyboardValue();
            if(!Select_a_section(BTForAll,sectionTitle)){
                cout << "Section "<< sectionTitle << " does not exist." << endl;
                cout << " " << endl;
                waitChoice(choice);
            }
            else {
                BinarySearchTree<ItemS> *pBST=NULL;
                Sections s1(sectionTitle,pBST);
                BTForAll.remove(BTForAll.find(s1));

                AvlTree<ItemS> *pAVL=NULL;
                Sections s2(sectionTitle,pAVL);
                BTForAvl.remove(BTForAvl.find(s2));                

                cout << "The section has been deleted." << endl;
                cout << " " << endl;
                waitChoice(choice);
            }
        }
        else if(choice == choice_exit){
            exitActivated = true;
        }
        else {
            outOfHomeworkButNeedForWrongUserEntry(choice);
        }
    }
    return 0;
}
