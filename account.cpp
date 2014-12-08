#include "account.h"
#include "send.h"

void account ::insert(char *__name, char *__pw) {
	// 새로운 데이터를 받아올 노드 new_node
	node_account *new_node_account = new node_account;
	// head 에 삽입할 위치를 가리킬 포인터 p
	node_account *p_account = NULL;

	// 받아온 데이터를 new_node 에 넣음
	strcpy(new_node_account->name, __name);
	strcpy(new_node_account->pw, __pw);

	// head 가 비어있을 경우
	// new_node 를 head 에 연결시킴
	if(head_account->next == NULL) {
		head_account->next = new_node_account;
		new_node_account->next = NULL;
			return;
	}

	// 포인터 p에게 head에 삽입할 위치를 알려줌
	p_account = head_account->next;

	// 포인터 p가 head의 끝을 만날때 까지 노드를 따라 한칸씩 전진
	while(p_account->next != NULL)
		p_account = p_account->next;

	// head의 끝을 만나면 new_node 에 연결시킴
	p_account->next = new_node_account;
	new_node_account->next = NULL;
}

int account ::remove(char *__name) {
	// 삭제할 노드를 찾을 포인터 p
	node_account *p_account = head_account->next;
	// 삭제 후 연결될 노드를 가리킬 포인터 tolink
	node_account *tolink_account = head_account;

	// 포인터 p가 head의 끝을 만날때 까지 노드를 따라 한칸씩 전진
	while(p_account != NULL) {
		// 사용자로 부터 입력받은 이름이 리스트 내에 존재하는지 검사
		if(strcmp(p_account->name,__name) == 0) {
			// 삭제된 노드 앞에 있던 노드를
			// 삭제된 노드가 가리키고 있던 노드에 연결시킴
			// 그런 후 삭제할 노드 반환
			// 다시말해 삭제할 노드를 빼오고 그 끊어진 부분을 다시 연결 시킴
			tolink_account->next = p_account->next;
			delete p_account;
			return 0;
		} else { // 노드를 따라 한칸씩 전진
			p_account = p_account->next;
			tolink_account = tolink_account->next;
		}
	}

	cout << "계정 목록에 입력하신 계정명이 존재하지 않습니다!" \
		<< endl;
	return 1;
}


// account.txt 파일 불러오기
int account ::load_acfile(void) {
	// 비밀번호 복호화 포인터
	char *pw_unsecret = NULL, *p = NULL;
	pw_unsecret = new char;

	// rt 모드로 파일 열기 : r-읽기모드, t-텍스트 모드
	FILE *acfile = NULL;
	FILE *is_ac_empty = NULL;
	acfile = fopen(account_file, "rt");
	is_ac_empty = fopen(account_file, "rt");

	// 파일 열기 정상 여부
	if(!acfile) {
		cout << \
			"[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
		return 1;
	}
	
	// 계정 로드
	cout << endl << "계정 목록 로드중..." << endl;
	
	// 한줄 먼저 읽어 보고 바로 파일의 끝을 만날 경우
	// 등록된 계정이 없는 것으로 인식, 해당 메세지 출력 후 함수 종료
	checkend = fscanf(is_ac_empty, "ID : %s PW : %s\n", \
			name, pw);
	if(checkend == EOF) {
		cout << "현재 등록되어 있는 계정이 없습니다." << endl;
		return 0;
	}

	do {
	         // 파일로 부터 한줄씩 읽어옴
	         checkend = fscanf(acfile, "ID : %s PW : %s\n", \
				name, pw);
	
		 // 파일 끝을 만나면 루프 종료
		 if(checkend == EOF)
			 break;

		 count++; // 등록된 계정 수 세기

		// 비밀번호 복호화
		strcpy(pw_unsecret, pw);
		p = pw_unsecret;
		while(*p != '\0') {
			*p = *p - '@';
			p++;
		}
		// cout << pw_unsecret << endl;

		 // 연결 리스트에 하나씩 삽입
		 insert(name, pw_unsecret);
	} while(1);

	cout << "현재 " << count << "명의 계정이 " \
		<< "등록 되어 있습니다." << endl;

	return 0;
}

// account.txt 파일에 쓰기
int account ::save_acfile(void) {
	// 비밀번호 암호화 포인터
	char *pw_secret = NULL, *p = NULL;
	pw_secret = new char;

	// 현재 노드 위치를 지정할 포인터 p
	node_account *p_account = head_account->next;
	
	// 파일 출력 모드로 파일 열기
	ofstream acfile;
	acfile.open(account_file, ios::out);

	// 파일 열기 정상 여부
	if(!acfile) {
		cout << \
			"[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
	}

	// 입출력 정상 여부
	if(!acfile.good() && !acfile.eof()) {
		cout << "[Error] I/O Error!! Exiting..." << endl;
		return 2;
	}

	// 포인터 p가 head의 끝을 만날때까지 한칸씩 전진하며
	// account.txt 파일에 연결된 노드 순서대로 기록
	while(p_account != NULL) {
		// 비밀번호 암호화
		strcpy(pw_secret, p_account->pw);
		p = pw_secret;
		while(*p != '\0') {
			*p = *p + '@';
			p++;
		}
		// cout << pw_secret << endl;

		acfile << "ID : " << p_account->name;
		acfile << " PW : " << pw_secret << endl;

		p_account = p_account->next;
	}
	acfile.close();

	cout << endl;

	return 0;
}

// 계정 추가
int account ::add_account(void) {
	unsigned int iscontinue;
	char input[MAX_CHAR_INPUT];

	FILE *acfile = NULL;
	acfile = fopen(account_file, "rt");

	while(1) {
		//////////////////////////////////////////
		reinput:	// 중복 계정명 또는 0 입력시 돌아옴.
		//////////////////////////////////////////
		cout << "계정명 입력 : ";
		cin >> input_name;

		if(!strcmp(input_name, "0")) {
			cout << "0 은 등록할 수 없는 계정명 입니다!!" \
				<< endl;
			goto reinput;
		}

		do {
	        // 파일로 부터 한줄씩 읽어옴
	        checkend = fscanf(acfile, "ID : %s PW : %s\n", \
				name, pw);

			// 등록되어 있는 계정 없거나 파일 끝가면 루프 빠져나옴
			if(checkend == EOF)
				break;
	
	        // 사용자가 입력한 계정명이 계정 파일 안에 있는지 검사
	        if(strcmp(input_name, name) == 0) {
				cout << "이미 존재하는 계정명 입니다" << endl;
				goto reinput;
			}
		}while (1);

		cout << "암호 입력 : ";
		cin >> input_pw;

		insert(input_name, input_pw);

		// account.txt 파일에 변경사항 기록
		save_acfile();

		// 추가로 계속 등록할 것인지 물어봄
		while(1) {
			cout << "다른 계정을 계속 등록 하시겠습니까? (y/n) : ";
			cin >> input;
			if(*input == 'y' || *input == 'Y') {
				fseek(acfile, 0, SEEK_SET);
				iscontinue = 1;
				break;
			} else if(*input == 'n' || *input == 'N') {
				iscontinue = 0;
				break;
			}
		}
		cout << endl;
	
		// 계속 등록한다고 했으면 루프 계속 돌고 아니면 빠져나옴
		if(iscontinue)
			continue;
		else
			break;
	}
	
	return 0;
}

// 계정 찾기
int account ::find_account(char *sendID) {
	unsigned int iscontinue;
	char input[MAX_CHAR_INPUT];

///////////////////////////////////////////////////////
search: // 다시 검색한다고 했을 경우 이곳으로 되돌아옴
///////////////////////////////////////////////////////

	cout << "쪽지를 보낼 대상을 입력하세요 : ";
	cin >> input_name;
	
	// rt 모드로 파일 열기 : r-읽기모드, t-텍스트 모드
	FILE *acfile = NULL;
	acfile = fopen(account_file, "rt");

	// 파일 열기 정상 여부
	if(!acfile) {
		cout << \
		"[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
		 return 1;
	}

	// 계정 조회
	cout << endl << "계정 조회중...";
	do {
	        // 파일로 부터 한줄씩 읽어옴
	        checkend = fscanf(acfile, "ID : %s PW : %s\n", \
				name, pw);
	
	        // 사용자가 입력한 계정명이 계정 파일 안에 있는지 검사
	        if(strcmp(input_name, name) == 0) {
	        	cout << endl;
	        	cout << endl << "찾은 계정명 : " << name << endl;
	
				// 찾은 계정에게 메세지를 보낼것인지 물어봄
				while(1) {
					cout << name << "님께 메세지를 보내시겠습니까? (y/n) : ";
					cin >> input;
					getchar();
					if(*input == 'y' || *input == 'Y') {
						sendmsg (name, sendID);
						/* cout << endl;
						cout << ">>>>메세지 함수 만들면 이곳에서 불러올꺼임...<<<<";
						cout << endl << endl; */
						//message.send();
						break;
					} else if(*input == 'n' || *input == 'N') {
						break;
					}
				}
	
				return 0;
	        // 파일 끝까지 검사해서 해당 계정명이 없으면 에러 출력후 함수 종료
		} else if(checkend == EOF) {
	        	cout << endl;
	        	cout << "\"" << input_name << "\"는 등록되지 않은 계정입니다." << endl;
			break;
	        }
	} while(1);

	// 추가로 계속 검색할 것인지 물어봄
	while(1) {
		cout << "추가로 쪽지를 보내겠습니까? (y/n) : ";
		cin >> input;
		if(*input == 'y' || *input == 'Y') {
			iscontinue = 1;
			break;
		} else if(*input == 'n' || *input == 'N') {
			iscontinue = 0;
			break;
		}
	}
	cout << endl;

	// 계속 검색한다고 했으면 다시 검색하는 곳으로 감
	if(iscontinue)
		goto search; // 윗부분 참고

	return 0;
}

// 계정 삭제
int account ::del_account(char *input_name) {
   // 삭제할 계정이 존재하는지 검사한 후 결과 출력
   if(remove(input_name) == 0) {
      // account.txt 파일에 변경사항 기록
      save_acfile();

      char ID[128];
      char *txt;
      txt = ".txt";
      strcpy(ID, input_name);
      strcat(ID, txt);

      ifstream inputfile (ID, ios::out | ios::trunc);

      if (!inputfile)
         cout << "파일 열기에 실패.\n";

      inputfile.close();


      return 0;
   } else
      return 1;
}

char* account :: login (char *__name, char *__pw) {
	node_account *temp = head_account->next;
	char *loginID;
	loginID = new char;
	strcpy (loginID, "0");

    while (temp != NULL) {
		if (!strcmp (temp->name, __name)){
			if (!strcmp (temp->pw, __pw)){
				strcpy (loginID,temp->name);
			}
		} 
		temp = temp->next;
    }
	return loginID;
}

int account ::read_msg (char *readID) {
	readmsg (readID);

	return 0;
}

