#include <iostream>

// 리눅스 지원
#define LINUX

using namespace std;

// char 형 배열 사이즈 조정
#define NAME_INPUT_MAX 60
#define PW_INPUT_MAX 255
#define MAX_CHAR_INPUT 255

// 쪽지 클래스 - 기초 클래스
class memo {
protected:
	// 파일로 부터 읽어 들이는 변수
	char name[NAME_INPUT_MAX];
	char pw[PW_INPUT_MAX];
	// 사용자 입력 변수
	char input_name[NAME_INPUT_MAX];
	char input_pw[PW_INPUT_MAX];

	char *account_file; // 파일 이름 저장 변수
	int checkend; // 파일 끝 검사
public:
	// 쪽지 클래스 초기화
	memo(void) {
	account_file = "account.txt";
	}
};

// 계정 노드 
class node_account {
	friend class memo;
public:
	char name[NAME_INPUT_MAX];
		char pw[PW_INPUT_MAX];
		// 노드 이동 포인터 변수
		node_account *next;
};

