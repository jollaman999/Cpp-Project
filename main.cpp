#include "account.h"

// 메인 함수
int main(void) {
	account ac;
	
	ac.load_acfile();
	ac.add_account();
	ac.find_account();
	ac.del_account();
	
	return 0;
}
