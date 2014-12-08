#include "account.h"
#include <stdlib.h>

void printlogo();

// 메인 함수
int main(void) {
	printlogo();
	account ac;
	
	// 파일 열기 오류 검사
	if(ac.load_acfile() == 1)
		return 1;
	
	char selectmenu[MAX_CHAR_INPUT];
	char selectmenu2[MAX_CHAR_INPUT];
	int endmenu=0;
	char inputID [NAME_INPUT_MAX];
	char inputPW [PW_INPUT_MAX];
	char *loginID;

	cout << endl << endl;

	do {
		//////////////////
		/// 첫번째 매뉴///
		//////////////////
		cout << "1. 회원 가입" << endl;
		cout << "2. 로그인" << endl;
		cout << "3. 종료" << endl << endl;

		cin >> selectmenu;
		switch (*selectmenu){
		case '1':
			ac.add_account();
#ifdef LINUX
			system("clear");
#else
			system ("cls");
#endif
			break;
		case '2':
			cout << "Input ID : ";
			cin >> inputID;
			cout << "Input Password : ";
			cin >> inputPW;
			loginID = ac.login (inputID, inputPW);
#ifdef LINUX
			system("clear");
#else
			system ("cls");
#endif
			if (loginID == "0"){
				cout << "아이디, 혹은 비밀번호가 일치하지 않습니다." << endl << endl;
			} else {
				//////////////////
				/// 두번째 매뉴///
				//////////////////
				printlogo();
				cout << loginID << " 로 로그인 하셨습니다." << endl << endl;
				do {
					cout << "1. 쪽지 보내기" << endl;
					cout << "2. 계정 삭제" << endl;
					cout << "3. 로그 아웃" << endl << endl;;
					cout << "4. 쪽지 읽기" << endl;

					cin >> selectmenu2;
					switch (*selectmenu2){
					case '1':
						ac.find_account (loginID);
#ifdef LINUX
						system("clear");
#else
						system ("cls");
#endif
						printlogo();
					break;
					case '2':
#ifdef LINUX
						system("clear");
#else
						system ("cls");
#endif
						if(ac.del_account(inputID) == 1)
							cout << endl << "에러 : 계정을 삭제하는 중 오류가 발생하였습니다!!" << endl;
						else
							cout << endl << inputID << " 계정을 성공적으로 삭제하였습니다." << endl;
						endmenu = 1;
					break;
					case '3':
						endmenu = 1;
#ifdef LINUX
						system("clear");
#else
						system ("cls");
#endif
						break;
					case '4':
#ifdef LINUX
						system("clear");
#else
						system ("cls");
#endif
						ac.read_msg (loginID);
						break;
					default:
#ifdef LINUX
						system("clear");
#else
						system ("cls");
#endif
						printlogo();
						break;
					}
				} while (endmenu == 0);
			}
			break;
		case '3':
			exit (1);
			break;
		default:
#ifdef LINUX
			system("clear");
#else
			system ("cls");
#endif
			break;
		}
		printlogo();
	} while (1);
	
	return 0;
}

void printlogo () {
	cout << endl << endl << endl;
	cout << "┌─────────────────────────────────┐" << endl;;
	cout << "│        쪽지 전송 프로그램       │" << endl;;
	cout << "└─────────────────────────────────┘" << endl;;
	cout << endl << endl << endl;
}

