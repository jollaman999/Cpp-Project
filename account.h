#include <iomanip>
#include <fstream>
#include <string.h>

#include "memo.h"

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
	void insert(char *__name, char *__pw);
	int remove(char *__name);

	// account.txt 파읽 읽기 쓰기 제어 함수
	int load_acfile(void);	// 파일 불러오기
	int save_acfile(void);	// 파일에 쓰기

	// 기능 제어 함수
	int add_account(void);			// 계정 추가
	int find_account(char *sendID);  	// 계정 찾기
	int del_account(char *input_name);	// 계정 삭제
	
	char* login (char *__name, char *__pw);
	int read_msg (char *readID);
};

