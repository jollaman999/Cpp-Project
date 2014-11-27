#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
using namespace std;

int main (){

	int menu;
	int end = 0;

	char tmpID [64];
	int tmpPASS;
	int tmpINDEX;
	int tmp;

	SList s;
	
	tmpINDEX = s.loadlist ();

	do {
		cout << "New (1), Delete (2), Show (3), End (4)\n";
		cin >> menu;

		switch (menu) {

		case 1:
			cout << "Input ID : ";
			cin >> tmpID;
			cout << "Input Password : ";
			cin >> tmpPASS;

			s.insert (tmpINDEX, tmpID, tmpPASS);
			tmpINDEX++;
		break;

		case 2:
			cout << "Input Index : ";
			cin >> tmp;

			s.remove (tmp);
		break;

		case 3:
			s.print();
		break;

		case 4:
			s.savelist();
			end = 1;
		break;
		}

	}  while (end==0);

    return 0;
}

