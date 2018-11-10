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
	"���10����܂��B\n",
	"����𐳂�����������10�_�����܂��B\n",
	"�����I���_100�_�����܂����H�H�H\n",
	"�ł́A�n�߂܂��傤�I�I\n"
};

void drawchoices(HANDLE hWindow, char(*choice)[100], int listNum, int index);

int getinput(int *row, int rowNum);

void outputResult(int*);

void DrawRectangle(int, int, int, int, char, char);

//Cursor�̍��W
COORD pos = { 0, 0 };

//����ۑ�����ϐ��z���鍐����
Quiz mondai[question_num];

int main() {

	//window handle��͂�
	HANDLE hWindow;
	hWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hWindow, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	DrawRectangle(0, 0, 50, 7, '*', ' ');

	//Cursor�������
	CONSOLE_CURSOR_INFO CCI;

	//window title��ݒ肷��
	SetConsoleTitleA("�N�C�Y�A�J�f�~�[");

	//window��cursor�����߂�
	CCI.dwSize = 100;
	SetConsoleCursorInfo(hWindow, &CCI);

	//�J�n��ʂ�\������
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

	//window��cursor���B��
	CCI.bVisible = false;
	SetConsoleCursorInfo(hWindow, &CCI);

	_getch();
	system("cls");

	//�N�C�Y��I�����␳���Ȃǂ�ǂݍ���
	FILE *fp;
	fp = fopen("myquestion.txt", "r");
	for (int i = 0; i < question_num; i++) {
		fscanf(fp, "%s%s%s%s%d", mondai[i].question, mondai[i].choices[0], mondai[i].choices[1], mondai[i].choices[2], &mondai[i].correct);
	}

	int answered[10];

	for (int i = 0; i < question_num; i++) {
		printf("��~��~��%d��A�������܂������H\n", i + 1);
		Sleep(500);
		printf("�悵�I�n�߂悤�I�I\n\n");
		Sleep(500);
		SetConsoleTextAttribute(hWindow, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("%s\n\n", mondai[i].question);

		SetConsoleTextAttribute(hWindow, 0x3);
		printf("�ł́I�N�̓����͂ǂ���ł��傤���H\n\n");

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

	printf("���ʂ��ł܂����Iresult.txt���m�F���Ă��������I\n");
	printf("�V��ł���Ă��肪�Ƃ��I   Coder : Josh\n");

	//�t�@�C���N���[�X
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

	//���������������ǂ������f����
	for (int i = 0; i < question_num; i++) {
		if (answers[i] == mondai[i].correct) {
			RorW[i] = true;
			correctNum++;
		}
		else
			RorW[i] = false;
	}

	//���ʂ�result.txt�ɏo�͂���
	FILE *fp;
	fp = fopen("result.txt", "w+");

	fprintf(fp, "%s\n", "********************************************************");
	fprintf(fp, "%s\n", "**                                                    **");
	fprintf(fp, "%s\n", "**          �w�N�C�Y���A�J�f�~�[�x���ʔ��\            **");
	fprintf(fp, "%s\n", "**                                                    **");
	fprintf(fp, "%s\n", "********************************************************");
	fprintf(fp, "\n");

	for (int i = 0; i < question_num; i++) {
		if (RorW[i] == true)
			fprintf(fp, "��  %2d ��F��  ����  ��\n", i + 1);
		else
			fprintf(fp, "��  %2d ��F�� �s���� ��\n", i + 1);
	}
	fprintf(fp, "\n");

	fprintf(fp, "%s\n", "+------------------------------------+");
	fprintf(fp, "%s\n", "|                                    |");
	fprintf(fp, "| %2d �⒆  %2d �␳�� (�������F%3d.0%%)|\n", question_num, correctNum, correctNum * 10);
	fprintf(fp, "%s\n", "|                                    |");
	fprintf(fp, "%s\n", "+------------------------------------+");
	fprintf(fp, "\n");

	if (correctNum < 6)
		fprintf(fp, "%s\n", "�w���悤�Ȃ�c(ɄD`)�~~�x������ �ފw ������");
	else
		fprintf(fp, "%s\n", "�w�����ˁI�悭�撣��������Ȃ��H�R(*߄t�)�m�x������ �i�� ������");

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