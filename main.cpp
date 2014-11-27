#include "account.h"

// 메인 함수
int main(void) {
	account ac;
	
	// 파일 열기 오류 검사
	if(ac.load_acfile() == 1)
		return 1;
	ac.add_account();
	ac.find_account();
	ac.del_account();
	
	return 0;
}
