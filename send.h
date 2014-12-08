#include <stdlib.h>
#include <string.h>
#include <time.h>

void sendmsg (char *id, char *sendID){
	char temptext [255]; // 메시지 임시 저장

	char ID [128];
	char *txt;
	txt = ".txt";
	strcpy (ID, id);
	strcat (ID, txt);

	time_t cur_time;

	time(&cur_time);
	
	cout << "쪽지 내용을 입력 하시오 : ";
	gets(temptext);

	fstream myfiles;
	myfiles.open (ID, ios::out | ios::app);


	if (!myfiles )
		cout << "파일 열기에 실패.\n";
	else {	myfiles << \
		ctime(&cur_time) << \
		"보낸 사람 : " << sendID << \
		"  |  쪽지 내용 : " << temptext << \
		endl;
		myfiles.close();
	}
}

void readmsg (char *id){
	char ID [128];
	char *txt;
	txt = ".txt";
	strcpy (ID, id);
	strcat (ID, txt);

	int searchmsg;
	int i=0;

	int count = 0;
	int searchcount = 1;

	char buff1 [255];
	char buff2 [255];
	ifstream inputfile;

	inputfile.open (ID);
	if (!inputfile )
		cout << "파일 열기에 실패.\n";
	else {
		inputfile.getline( buff1 , 255 );
		inputfile.getline( buff2 , 255 );
		i++;
		while( !inputfile.eof() ) {
			count ++; 
			inputfile.getline( buff1 , 255 );
			inputfile.getline( buff2 , 255 );
			i++;
		}
	}
	inputfile.close();

	retry:

	cout << "총 " << count << "개의 메시지가 있습니다" << endl;
	cout << "몇번째 메시지를 보시겠습니까?" << endl;
	cout << "( 256 입력시 모두 출력 )" << endl;

	cin >> searchmsg;
	getchar();

	if (searchmsg == 256){
		inputfile.open (ID);
		if (!inputfile )
			cout << "파일 열기에 실패.\n";
		else {
			inputfile.getline( buff1 , 255 );
			inputfile.getline( buff2 , 255 );
				cout << buff1 << endl << \
					buff2 << endl << endl;
			while( !inputfile.eof() ) {
				searchcount ++; 
				inputfile.getline( buff1 , 255 );
				inputfile.getline( buff2 , 255 );
				cout << buff1 << endl << \
					buff2 << endl << endl;
			}
		}
		inputfile.close();
	}
	else if (searchmsg > count){
#ifdef LINUX
		system("clear");
#else
		system ("cls");
#endif
		cout << "잘못 입력 하셨습니다" << endl << endl;
		goto retry;
	} else if (searchmsg <= 0){
#ifdef LINUX
		system("clear");
#else
		system ("cls");
#endif
		cout << "잘못 입력 하셨습니다" << endl << endl;
		goto retry;
	} else {
		inputfile.open (ID);
		if (!inputfile )
			cout << "파일 열기에 실패.\n";
		else {
			inputfile.getline( buff1 , 255 );
			inputfile.getline( buff2 , 255 );
			if (searchcount == searchmsg){
				cout << buff1 << endl << \
					buff2 << endl << endl;
			}
			while( !inputfile.eof() ) {
				searchcount ++; 
				inputfile.getline( buff1 , 255 );
				inputfile.getline( buff2 , 255 );
				if (searchcount == searchmsg){
					cout << buff1 << endl << \
						buff2 << endl << endl;
				}
			}
		}
		inputfile.close();
	};
}

