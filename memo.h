#include <iostream>

using namespace std;

// char 형 배열 사이즈 조정
#define NAME_INPUT_MAX 30
#define PW_INPUT_MAX 40
#define MAX_CHAR_INPUT 255

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