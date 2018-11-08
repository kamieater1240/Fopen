#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {

	FILE *fp;				//ファイルポインタの宣言
	char A[30] = {"hanayama"};
	int num, fN;

	//ファイルオープン
	fp = fopen("name.txt", "r");
	if (fp == NULL)
		printf("File open error.");
	else {
		while ((num = fscanf(fp, "%s%d", A, &fN)) != EOF) {
			printf("Get!! %s is %d 位\n", A, fN);
			printf("num = %d\n", num);
		}
		printf("Last num = %d\n", num);
	}

	//ファイルクロース
	fclose(fp);

	system("pause");
	return 0;
}