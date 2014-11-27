#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

class SList;
class node {
friend class SList;
protected:
    char ID[64];
    int PASSWORD;
    int INDEX;
    node* next;
    node* prev;
};

class SList {
protected:
    node* head; 
public:
    SList();
	~SList();

    void insert (int in, char *id, int pa);
    void remove(int in);
    void print();
	void savelist ();
	int loadlist ();
};

SList::SList(){
    head = new node; 
    head->next = NULL;
	head->prev = NULL;
}

SList::~SList(){
    node* temp; 
    while (head != NULL) {
	temp = head;
        head = head->next;
	delete temp; 
        }
}

void SList::insert(int in, char *id, int pa){
    node* new_node = new node;
    node* temp;
    new_node->INDEX = in; 
    strcpy (new_node->ID, id);
    new_node->PASSWORD = pa;

    if (head->next == NULL) {
	head->next = new_node; 
	new_node->next = NULL;
	new_node->prev = head;
        return; 
    }
    temp = head->next;

    while (temp->next != NULL) 

    temp = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = NULL;
}

void SList::remove(int in){
    node *current = head->next;
    node *prev = head;

    while (current != NULL) {
	if (current->INDEX == in) {
	    prev->next = current->next;
	    delete current;

            return;
            }	else {prev = prev->next;
	    current = current->next;
            }
        }
        cout << "리스트내에 Index : " << in << " 이 없습니다" << endl;
}

void SList::print(){
    node *temp = head->next;
    while (temp != NULL) {
	cout << "Index : " << setfill('0') << setw(3) << temp->INDEX << " ID :  " << temp->ID << " Password : " << temp->PASSWORD << endl;
	temp = temp->next;
        }

        cout << endl;
}

void SList::savelist (){
	ofstream fout ("test.txt", ios::out);

	node *temp2 = head->next;
    while (temp2 != NULL) {

		fout << setfill('0') << setw(3) << temp2->INDEX << endl;
		fout << temp2->ID << endl;
		fout << temp2->PASSWORD << endl;
	
		temp2 = temp2->next;
    }
	fout.close ();
}

int SList::loadlist (){
	ifstream fin ("test.txt");

	char buff [128];
	char buff2 [128];
	char *tmpID;
	int tmpPASS;
	int tmpINDEX;

	int checkINDEX = 1;

	int nextTEXT = 0;

    while ( !fin.eof() ) {
		if (nextTEXT == 0) {
			fin.getline (buff, 128);
			tmpINDEX = atoi (buff);
			nextTEXT = 1;
		} else if (nextTEXT == 1) {
			fin.getline (buff2, 128);
			tmpID = buff2;
			nextTEXT = 2;
		} else {
			fin.getline (buff, 128);
			tmpPASS = atoi (buff);
			nextTEXT = 0;

			insert (tmpINDEX, tmpID, tmpPASS);
			checkINDEX++;
		}
    }
	fin.close ();

	return (checkINDEX);
}