#include <iostream>
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
   // 사용자 입력 변수
   char input_name[NAME_INPUT_MAX];
   char input_pw[PW_INPUT_MAX];

   char *account_file; // 파일 이름 저장 변수
   int checkend; // 파일 끝 검사
public:
   // 파일 이름 변수에 저장하는 생성자
   memo(void) {
      account_file = "account.txt";
   }
};

// 계정 클래스 - 쪽지 클래스로 부터 상속 받음
class account : public memo {
public:
   int add_account(void);      // 계정 추가
   int find_account(void);      // 계정 찾기
   int del_account(void);   // 계정 삭제
};

// 계정 추가/
int account ::add_account(void) {
   unsigned int iscontinue;
   char input[MAX_CHAR_INPUT];

   // 파일 출력 모드로 파일 열기
   ofstream acfile;
   acfile.open(account_file, ios::out | ios::app);

   // 파일 열기 정상 여부
   if(!acfile) {
      cout << \
         "[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
      return 1;
   }

   while(!acfile.eof()) {
      // 입출력 정상 여부
      if(!acfile.good() && !acfile.eof()) {
         cout << "[Error] I/O Error!! Exiting..." << endl;
         return 2;
      }

      cout << "계정명 입력 : ";
      cin >> input_name;
      acfile << "ID : " << input_name;
      cout << "암호 입력 : ";
      cin >> input_pw;
      acfile << " PW : " << input_pw << endl;

      // 추가로 계속 등록할 건지 물어봄
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
   acfile.close();
}

// 계정 찾기
int account ::find_account(void) {
   cout << "찾고자 하는 계정명을 입력하세요 : ";
   cin >> input_name;

   // rt 모드로 파일 열기 : r-읽기모드, t-텍스트 모드
   FILE *fp = NULL;
   fp = fopen(account_file, "rt");

   // 파일 열기 정상 여부
   if(!fp) {
      cout << \
         "[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
      return 1;
   }

   // 계정 조회
   cout << endl << "계정 조회중..." << endl;
   do {
         // 파일로 부터 한줄씩 읽어옴
         checkend = fscanf(fp, "ID : %s PW : %s\n", name, pw);

         // 사용자가 입력한 계정명이 계정 파일 안에 있는지 검사
         if(strcmp(input_name, name) == 0)
            break;
         // 파일 끝까지 검사해서 해당 계정명이 없으면 에러 출력후 함수 종료
         else if(checkend == EOF) {
            cout << endl;
            cout << "\"" << input_name << "\"는 등록되지 않은 계정입니다." << endl;
            return 0;
         }
   } while(1);

   cout << endl << "찾은 계정명 : " << name << endl;

   return 0;
}

// 계정 삭제
int account ::del_account(void) {
   char **ac_name_list;
   char **ac_pw_list;
   int isfound = 0;
   int count = 0;
   int i;
   int j;

   cout << "삭제하고자 하는 계정명을 입력하세요 : ";
   cin >> input_name;

   FILE *fp1 = NULL;
   fp1 = fopen(account_file, "rt");

   if(!fp1) {
      cout << \
         "[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
      return 1;
   }

   cout << endl << "계정 조회중..." << endl;
   do {
         checkend = fscanf(fp1, "ID : %s PW : %s\n", name, pw);

         if(strcmp(input_name, name) == 0) {
            isfound = 1;
         continue;
         } else if(checkend == EOF) {
         if(!isfound) {
            cout << endl;
            cout << "\"" << input_name << "\"는 등록되지 않은 계정입니다." << endl;
            return 0;
         }
         break;
         }

       count++;
   } while(1);

   // 2차원 포인터 메모리 할당
   // 가로축 : name, pw 사이즈 만큼 할당 / 세로축 : count 갯수 만큼 할당
   ac_name_list = new char*[count];
   for(i=0; i<count; i++)
      ac_name_list[i] = new char[NAME_INPUT_MAX];

   ac_pw_list = new char*[count];
   for(i=0; i<count; i++)
      ac_pw_list[i] = new char[PW_INPUT_MAX];

   FILE *fp2 = NULL;
   fp2 = fopen(account_file, "rt");

   if(!fp2) {
      cout << \
         "[에러] \"" << account_file << "\" 파일을 열 수 없습니다!!\n";
      return 1;
   }

   i = 0;
   do {
      checkend = fscanf(fp2, "ID : %s PW : %s\n", name, pw);

      for(j=0; j<NAME_INPUT_MAX; j++)
         ac_name_list[i][j] = name[j];
      for(j=0; j<PW_INPUT_MAX; j++)
         ac_pw_list[i][j] = pw[j];

      if(strcmp(input_name, name) == 0) {
         checkend = fscanf(fp2, "ID : %s PW : %s\n", name, pw);
         continue;
      } else if(checkend == EOF) {
      break;
      }

      i++;
   } while(1);

   for(i=0; i<count; i++) {
      cout << "ID : " << ac_name_list[i] << \
         " PW : " << ac_pw_list[i] << endl;
   }

   cout << endl << "삭제된 계정명 : " << input_name << endl;
   /*
   // 2차원 포인터 메모리 해제
   for(i=0; i<count; i++) {
   delete [] ac_name_list[i];
   delete [] ac_pw_list[i];
   }
   delete [] ac_name_list;
   delete [] ac_pw_list;
   */

   return 0;
}

// 메인 함수
int main(void) {
   account ac;

   ac.add_account();
   ac.find_account();
   ac.del_account();

   return 0;
}
