#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>

// char 형 배열 사이즈 조정
#define NAME_INPUT_MAX 30
#define PW_INPUT_MAX 40
#define MAX_CHAR_INPUT 255

using namespace std;

// 쪽지 클래스 - 기초 클래스
class memo {
protected:
	// 파일로 부터 읽어 들이는 변수
	char name[NAME_INPUT_MAX];
	char pw[PW_INPUT_MAX];
	unsigned int index;
	// 사용자 입력 변수
	char input_name[NAME_INPUT_MAX];
	char input_pw[PW_INPUT_MAX];

	// 다음에 삽일될 위치를 지정할 인덱스 변수
	unsigned int next_index;

	// 계정 노드
	struct node_account{
		char name[NAME_INPUT_MAX];
		char pw[PW_INPUT_MAX];
		int index;	// 계정별 인덱스 변수
		// 노드 이동 포인터 변수
		node_account *next;
		node_account *prev;
	};

	char *account_file; // 파일 이름 저장 변수
	int checkend; // 파일 끝 검사
public:
	// 쪽지 클래스 초기화
	memo(void) {
	next_index = 0;
	
	account_file = "account.txt";
	}
};

// 계정 클래스 - 쪽지 클래스로 부터 상속 받음
class account : public memo {
protected:
	node_account *head_account;	// 계정 연결 리스트 선언
	int count;	// 등록된 계정 수
public:
	// 계정 생성자 - 계정 연결 리스트 초기화
	account(void) {
		count = 0;

		head_account = new node_account;
		head_account->next = NULL;
		head_account->prev = NULL;
	}
	// 계정 소멸자 - 계정 연결 리스트 연결된 노드 순으로 메모리 반환
	~account(void) {
		// 반환될 노드를 가리킬 포인터 p
		node_account *p_account;
		while (head_account != NULL) {
			p_account = head_account;
			head_account = head_account->next;
			delete p_account;
		}
	}

	// 계정 노드 제어 함수
	void insert(int __index, char *__name, char *__pw);
	void remove(char *__name);

	// account.txt 파읽 읽기 쓰기 제어 함수
	int load_acfile(void);	// 파일 불러오기
	int save_acfile(void);	// 파일에 쓰기

	// 기능 제어 함수
	int add_account(void);   // 계정 추가
	int find_account(void);  // 계정 찾기
	int del_account(void);   // 계정 삭제
};

void account ::insert(int __index, char *__name, char *__pw) {
	// 새로운 데이터를 받아올 노드 new_node
	node_account *new_node_account = new node_account;
	// head 에 삽입할 위치를 가리킬 포인터 p
	node_account *p_account = NULL;

	// 받아온 데이터를 new_node 에 넣음
	new_node_account->index = __index;
	strcpy(new_node_account->name, __name);
	strcpy(new_node_account->pw, __pw);

	// head 가 비어있을 경우
	// new_node 를 head 에 연결시킴
	if(head_account->next == NULL) {
		head_account->next = new_node_account;
		new_node_account->next = NULL;
		new_node_account->prev = head_account;
			return;
	}

	// 포인터 p에게 head에 삽입할 위치를 알려줌
	p_account = head_account->next;

	// 포인터 p가 head의 끝을 만날때 까지 노드를 따라 한칸씩 전진
	while(p_account->next != NULL)
		p_account = p_account->next;

	// head의 끝을 만나면 new_node 에 연결시킴
	p_account->next = new_node_account;
	new_node_account->prev = p_account;
	new_node_account->next = NULL;
}

void account ::remove(char *__name) {
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
			return;
		} else { // 노드를 따라 한칸씩 전진
			p_account = p_account->next;
			tolink_account = tolink_account->next;
		}
	}

	cout << "계정 목록에 입력하신 인덱스 또는 계정명이 존재하지 않습니다!" \
		<< endl;
}


// account.txt 파일 불러오기
int account ::load_acfile(void) {
	// rt 모드로 파일 열기 : r-읽기모드, t-텍스트 모드
	FILE *acfile = NULL;
	FILE *is_ac_empty = NULL;
	acfile = fopen(account_file, "rt");
	is_ac_empty = fopen(account_file, "rt");

	// 파일 열기 정상 여부
	if(!acfile) {
		cout << \
			"[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
		exit(1);
	}
	
	// 계정 로드
	cout << endl << "계정 목록 로드중..." << endl;
	
	// 한줄 먼저 읽어 보고 바로 파일의 끝을 만날 경우
	// 등록된 계정이 없는 것으로 인식, 해당 메세지 출력 후 함수 종료
	checkend = fscanf(is_ac_empty, "INDEX : %3d ID : %s PW : %s\n", \
			&next_index, name, pw);
	if(checkend == EOF) {
		cout << "현재 등록되어 있는 계정이 없습니다." << endl;
		return 0;
	}

	do {
	         // 파일로 부터 한줄씩 읽어옴
	         checkend = fscanf(acfile, "INDEX : %3d ID : %s PW : %s\n", \
				 &next_index, name, pw);
	
		 // 파일 끝을 만나면 루프 종료
		 if(checkend == EOF)
			 break;

		 count++; // 등록된 계정 수 세기

		 // 연결 리스트에 하나씩 삽입
		 insert(next_index, name, pw);
	} while(1);

	cout << "현재 " << count << "명의 계정이 " \
		<< "등록 되어 있습니다." << endl;

	return 0;
}

// account.txt 파일에 쓰기
int account ::save_acfile(void) {
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
		acfile << "INDEX : ";
		if(next_index == 0)
			p_account->index = 1;
		// index 가 1일 경우 001, 23일 경우 023 이런식으로 기록됨
		acfile << setfill('0') << setw(3) << p_account->index;
		acfile << " ID : " << p_account->name;
		acfile << " PW : " << p_account->pw << endl;

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

	while(1) {
		next_index++; // 다음에 삽일될 인덱스 위치 증가 시킴

		cout << "계정명 입력 : ";
		cin >> input_name;
		cout << "암호 입력 : ";
		cin >> input_pw;
		insert(next_index, input_name, input_pw);

		// 추가로 계속 등록할 것인지 물어봄
		while(1) {
			cout << "다른 계정을 계속 등록 하시겠습니까? (y/n) : ";
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
	
		// 계속 등록한다고 했으면 루프 계속 돌고 아니면 빠져나옴
		if(iscontinue)
			continue;
		else
			break;
	}

	// account.txt 파일에 변경사항 기록
	save_acfile();
	
	return 0;
}

// 계정 찾기
int account ::find_account(void) {
	unsigned int iscontinue;
	char input[MAX_CHAR_INPUT];

///////////////////////////////////////////////////////
search: // 다시 검색한다고 했을 경우 이곳으로 되돌아옴
///////////////////////////////////////////////////////

	cout << "찾고자 하는 계정명을 입력하세요 : ";
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
	        checkend = fscanf(acfile, "INDEX : %3d ID : %s PW : %s\n", \
				&index, name, pw);
	
	        // 사용자가 입력한 계정명이 계정 파일 안에 있는지 검사
	        if(strcmp(input_name, name) == 0) {
	        	cout << endl;
	        	cout << endl << "찾은 계정명 : " << name << endl;
	
				// 찾은 계정에게 메세지를 보낼것인지 물어봄
				while(1) {
					cout << name << "님께 메세지를 보내시겠습니까? (y/n) : ";
					cin >> input;
					if(*input == 'y' || *input == 'Y') {
						cout << endl;
						cout << ">>>>메세지 함수 만들면 이곳에서 불러올꺼임...<<<<";
						cout << endl << endl;
						// message.send();
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
		cout << "다시 검색 하시겠습니까? (y/n) : ";
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
int account ::del_account(void) {
	cout << "삭제하고자 하는 인덱스 또는 계정명을 입력하세요 : ";
	cin >> input_name;
	
	remove(input_name);
	
	// account.txt 파일에 변경사항 기록
	save_acfile();
	
	cout << endl << "삭제된 계정명 : " << input_name << endl;
	
	return 0;
}

// 메인 함수
int main(void) {
	account ac;
	
	ac.load_acfile();
	ac.add_account();
	ac.find_account();
	ac.del_account();
	
	return 0;
}
