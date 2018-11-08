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
	"各難易度に問題10個あります\n",
	"問題一個を正しく答えたら10点が取られます。\n",
	"さあ！満点100点が取られますか？\n",
	"難易度を選んで始めましょう！！\n"
};

void drawchoices();

int getinput();

void DrawRectangle(int, int, int, int, char, char);

//Cursorの座標
COORD pos = { 0, 0 };

int main() {

	DrawRectangle(10, 5, 30, 15, '*', ' ');

	Quiz mondai[question_num];
	char check;

	//window handleを掴む
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	//Cursor情報を取る
	CONSOLE_CURSOR_INFO CCI;

	//window titleを設定する
	SetConsoleTitleA("クイズアカデミー");

	//windowのcursorを高める
	CCI.dwSize = 100;
	SetConsoleCursorInfo(hWindow, &CCI);

	//開始画面を表示する
	SetConsoleTextAttribute(hWindow, 0x3);
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
	fp = fopen("question.txt", "r");
	for (int i = 0; i < question_num; i++) {
		fscanf(fp, "%s%s%s%s%d%c", mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], &mondai[i].correct, &check);
	}

	/*int answered[10];

	for (int i = 0; i < question_num; i++) {
		printf("さ~さ~第%d問、準備しましたか？\n", i + 1);
		Sleep(500);
		printf("よし！始めよう！！\n");
		Sleep(500);
		printf("%s\n", mondai[i].question);
		printf("%s\n%s\n%s\n", mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2]);
		printf("では！君の答えはどちらでしょうか？ 答：");
		scanf("%d", &answered[i]);
		system("cls");
	}*/

	//ファイルクロース
	fclose(fp);

	system("pause");
	return 0;
}

void drawchoices() {

}

int getinput() {

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