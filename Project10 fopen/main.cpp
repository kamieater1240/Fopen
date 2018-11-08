/*=====================================================
 *�ۑ�F�N�C�Y�A�J�f�~�[
 *date�F2018.11.10
 *coder�FJosh
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

//�N�C�Y��ۑ�����\����
typedef struct {
	char question[100];
	char choices[3][100];
	int correct;
} Quiz;

//�L�[�{�[�h�̓��̓R�[�h��ENUM
enum INPUTCOMMAND
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};

//�ŏ���TEXT
const char * startText[] =
{
	"�Q�[���N�C�Y�ւ悤�����I�I\n",
	"�e��Փx�ɖ��10����܂�\n",
	"����𐳂�����������10�_������܂��B\n",
	"�����I���_100�_������܂����H\n",
	"��Փx��I��Ŏn�߂܂��傤�I�I\n"
};

void drawchoices();

int getinput();

void DrawRectangle(int, int, int, int, char, char);

//Cursor�̍��W
COORD pos = { 0, 0 };

int main() {

	DrawRectangle(10, 5, 30, 15, '*', ' ');

	Quiz mondai[question_num];
	char check;

	//window handle��͂�
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	//Cursor�������
	CONSOLE_CURSOR_INFO CCI;

	//window title��ݒ肷��
	SetConsoleTitleA("�N�C�Y�A�J�f�~�[");

	//window��cursor�����߂�
	CCI.dwSize = 100;
	SetConsoleCursorInfo(hWindow, &CCI);

	//�J�n��ʂ�\������
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

	//window��cursor���B��
	CCI.bVisible = false;
	SetConsoleCursorInfo(hWindow, &CCI);

	_getch();
	system("cls");

	//�N�C�Y��I�����␳���Ȃǂ�ǂݍ���
	FILE *fp;
	fp = fopen("question.txt", "r");
	for (int i = 0; i < question_num; i++) {
		fscanf(fp, "%s%s%s%s%d%c", mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], &mondai[i].correct, &check);
	}

	/*int answered[10];

	for (int i = 0; i < question_num; i++) {
		printf("��~��~��%d��A�������܂������H\n", i + 1);
		Sleep(500);
		printf("�悵�I�n�߂悤�I�I\n");
		Sleep(500);
		printf("%s\n", mondai[i].question);
		printf("%s\n%s\n%s\n", mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2]);
		printf("�ł́I�N�̓����͂ǂ���ł��傤���H ���F");
		scanf("%d", &answered[i]);
		system("cls");
	}*/

	//�t�@�C���N���[�X
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