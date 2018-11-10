/*=====================================================
 *課題：クイズアカデミー
 *date：2018.11.10
 *coder：Josh
 *===================================================== */
#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#define question_num 10
#define objectnum(obj) (sizeof(obj)/sizeof(obj[0]))
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//クイズを保存する構造体
typedef struct {
	char question[100];
	char choices[3][100];
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

//最初のTEXT
const char * startText[] =
{
	"ゲームクイズへようこそ！！\n",
	"問題10個あります。\n",
	"問題一個を正しく答えたら10点が取れます。\n",
	"さあ！満点100点が取れますか？？？\n",
	"では、始めましょう！！\n"
};

void drawchoices(HANDLE hWindow, char(*choice)[100], int listNum, int index);

int getinput(int *row, int rowNum);

void outputResult(int*);

void DrawRectangle(int, int, int, int, char, char);

//Cursorの座標
COORD pos = { 0, 0 };

//問題を保存する変数配列を宣告する
Quiz mondai[question_num];

int main() {

	//window handleを掴む
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hWindow, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	DrawRectangle(0, 0, 50, 7, '*', ' ');

	//Cursor情報を取る
	CONSOLE_CURSOR_INFO CCI;

	//window titleを設定する
	SetConsoleTitleA("クイズアカデミー");

	//windowのcursorを高める
	CCI.dwSize = 100;
	SetConsoleCursorInfo(hWindow, &CCI);

	//開始画面を表示する
	SetConsoleTextAttribute(hWindow, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int i = 0; i < objectnum(startText); i++)
	{
		pos.X = 2; pos.Y = 1 + i;
		SetConsoleCursorPosition(hWindow, pos);
		int strlength = strlen(startText[i]);
		for (int j = 0; j < strlength; j++) {
			Sleep(50);
			printf("%c", startText[i][j]);
		}
	}

	//windowのcursorを隠す
	CCI.bVisible = false;
	SetConsoleCursorInfo(hWindow, &CCI);

	_getch();
	system("cls");

	//クイズや選択肢や正解などを読み込む
	FILE *fp;
	fp = fopen("myquestion.txt", "r");
	for (int i = 0; i < question_num; i++) {
		fscanf(fp, "%s%s%s%s%d", mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], &mondai[i].correct);
	}

	int answered[10];

	for (int i = 0; i < question_num; i++) {
		printf("さ~さ~第%d問、準備しましたか？\n", i + 1);
		Sleep(500);
		printf("よし！始めよう！！\n\n");
		Sleep(500);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("%s\n\n", mondai[i].question);

		SetConsoleTextAttribute(hWindow, 0x3);
		printf("では！君の答えはどちらでしょうか？\n\n");

		bool finish = true;
		int press, row = 1;
		while (finish) {
			drawchoices(hWindow, mondai[i].choices, 3, row);
			printf("\n\n\n\n\n row = %d", row);
			press = getinput(&row, 3);
			if (press == ENTER) {
				answered[i] = row;
				system("cls");
				break;
			}
		}
		system("cls");
	}

	outputResult(answered);

	printf("結果がでました！result.txtを確認してください！\n");
	printf("遊んでくれてありがとう！   Coder : Josh\n");

	//ファイルクロース
	fclose(fp);

	system("pause");
	return 0;
}

void drawchoices(HANDLE hWindow, char(*choice)[100], int listNum, int index) {

	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(hWindow, pos);
	for (int i = 1; i <= listNum; i++) {

		if (i == index) {
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | 0x8);
			pos.X = 0;
			pos.Y = 7 + i;
			SetConsoleCursorPosition(hWindow, pos);
			printf("%s", choice[i-1]);
		}
		else {
			SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			pos.X = 0;
			pos.Y = 7 + i;
			SetConsoleCursorPosition(hWindow, pos);
			printf("%s", choice[i-1]);
		}
	}
	return;
}

int getinput(int *row, int rowNum) {

	int get;
	get = _getch();
	if (get == UP) {
		if (*row > 1) {
			*row -= 1;
		}
		else {
			*row = rowNum;
		}
	}
	else if (get == DOWN) {
		if (*row < rowNum) {
			*row += 1;
		}
		else {
			*row = 1;
		}
	}
	else if (get == ENTER)
		return ENTER;

	return 0;
}

void outputResult(int *answers) {

	int correctNum = 0;
	bool RorW[question_num];

	//答えが正しいかどうか判断する
	for (int i = 0; i < question_num; i++) {
		if (answers[i] == mondai[i].correct) {
			RorW[i] = true;
			correctNum++;
		}
		else
			RorW[i] = false;
	}

	//結果をresult.txtに出力する
	FILE *fp;
	fp = fopen("result.txt", "w+");

	fprintf(fp, "%s\n", "********************************************************");
	fprintf(fp, "%s\n", "**                                                    **");
	fprintf(fp, "%s\n", "**          『クイズ☆アカデミー』結果発表            **");
	fprintf(fp, "%s\n", "**                                                    **");
	fprintf(fp, "%s\n", "********************************************************");
	fprintf(fp, "\n");

	for (int i = 0; i < question_num; i++) {
		if (RorW[i] == true)
			fprintf(fp, "第  %2d 問：☆  正解  ☆\n", i + 1);
		else
			fprintf(fp, "第  %2d 問：◆ 不正解 ◆\n", i + 1);
	}
	fprintf(fp, "\n");

	fprintf(fp, "%s\n", "+------------------------------------+");
	fprintf(fp, "%s\n", "|                                    |");
	fprintf(fp, "| %2d 問中  %2d 問正解 (正答率：%3d.0%%)|\n", question_num, correctNum, correctNum * 10);
	fprintf(fp, "%s\n", "|                                    |");
	fprintf(fp, "%s\n", "+------------------------------------+");
	fprintf(fp, "\n");

	if (correctNum < 6)
		fprintf(fp, "%s\n", "『さようなら…(ﾉД`)ﾉ~~』■■■ 退学 ■■■");
	else
		fprintf(fp, "%s\n", "『凄いね！よく頑張ったじゃない？ヽ(*ﾟдﾟ)ノ』■■■ 進級 ■■■");

	fclose(fp);
}

void DrawRectangle(int posX, int posY, int width, int height, char drawChar, char emptyChar) {

	string firstAndLastRow(width, drawChar);
	string posXstring(posX, ' ');

	//fist add some empty line to match posY
	for (int row = 0; row < posY; row++)
		cout << endl;

	//first row
	cout << posXstring;
	cout << firstAndLastRow << endl;

	//rows between first and last
	for (int row = 0; row < height - 2; row++) {
		string betweenRow(width, emptyChar);
		betweenRow[0] = drawChar;
		betweenRow[width - 1] = drawChar;
		//here we add the posX, so adding posX spaces in front of each line
		cout << posXstring;
		cout << betweenRow << endl;
	}

	//last row
	cout << posXstring;
	cout << firstAndLastRow << endl;
}