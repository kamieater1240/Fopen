/*=====================================================
 *課題：クイズアカデミー
 *date：2018.11.10
 *coder：Josh
 *===================================================== */
#define _CRT_SECURE_NO_WARNINGS
#define question_num 10
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	string question;
	string choices[3];
	int correct;
} Quiz;

//キーボードの入力コードのENUM
enum INPUTCOMMAND
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};

int main() {

	Quiz mondai[question_num];
	char check;

	//window handleを掴む
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	//window titleを設定する
	SetConsoleTitleA("クイズアカデミー");

	//クイズや選択肢や正解などを読み込む
	//FILE *fp;
	fstream fin;
	//fp = fopen("question.txt", "r");
	fin.open("question.txt", ios::in);
	for (int i = 0; i < question_num; i++) {
		//fscanf(fp, "%s%s%s%s%d%c", &mondai[i].question, &mondai[i].choices[0], &mondai[i].choices[1], &mondai[i].choices[2], &mondai[i].correct, &check);
		//printf("%s\n%s\n%s\n%s\n%d\n", mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], mondai[i].correct);
		//fscanf(fp, "%s%s%s%s%d%c", &mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], &mondai[i].correct, &check);
		//printf("%s\n%s\n%s\n%s\n%d\n", mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], mondai[i].correct);
	}


	//ファイルクロース
	fclose(fp);

	system("pause");
	return 0;
}