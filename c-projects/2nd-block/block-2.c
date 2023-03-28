#include <stdio.h>
#include <stdlib.h>

#include "Header.h"

#pragma comment(lib, "Winmm.lib")



void Uloha211() {
	printf("Uloha211\n");
	int a = 0; int b = 0;
	printf("put a: ");
	scanf_s("%d", &a);
	printf("put b: ");
	scanf_s("%d", &b);
	int sum = 0;
	//asm works only on x86(x32) system, on x64 will be mistakes, or u should optimize function for x64 system
	__asm {
		mov eax, a
		add eax, b
		mov sum, eax
	}
	getchar();
	printf("Sum: %d", sum);
}

void Uloha212() {
	printf("\n\nUloha212");
	int a = 0;
	printf("\nput a: ");
	scanf_s("%d", &a);
	__asm {
		mov eax, a
		shl eax, 1
		mov a, eax
	}
	getchar();
	printf("Sum: %d", a);

}

void Uloha213() {
	printf("\n\nUloha213\n");
	int a = 0; int b = 10; int o = 55; int p = 48;
	printf("put a: ");
	scanf_s("%d", &a);
	if (a < -1 || a > 15) {
		a = 0;
		printf("a must be more than -1 and less than 16: ");
		scanf_s("%d", &a);
	}
	else {
		a = a;
	}
	__asm {
		mov eax, a
		mov ebx, b
		mov ecx, o
		mov edx, p
		cmp eax, ebx
		jb L1
		add eax, ecx
		mov a, eax
		jmp L2
		L1 : add eax, edx
		mov a, eax
		L2 : mov a, eax


	}
	printf("a v hex. syst. : %c", a);


}

char* empty(char* x, int y) {
	for (int i = 0; i < y; i++) {
		x[i] = 0;
	}
}


void Uloha214() {
	printf("\n\nUloha214");
	char* ar[30];
	char* a[10];
	char* b[10];
	char* c[10];
	empty(a, 10);
	empty(b, 10);
	empty(c, 10);
	empty(ar, 30);
	__asm {
		mov ebx, 0
		mov eax, 0
		mov edx, 0
		mov ecx, 0
		cpuid
		mov a, ebx
		mov b, edx
		mov c, ecx

	}

	strcat(ar, a);
	strcat(ar, b);
	strcat(ar, c);

	printf("\nYour CPU tupe: %s", ar);



}



void Uloha251() {
	printf("\n\nUloha251\n");
	printf("put a:");
	int max = 0; int c = 0;
	scanf("%d", &max);
	HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < max; i++) {
		SetConsoleTextAttribute(Color, c);
		printf("%d\n", i);
		if (i%11==0) {
			c = c + 1;
		}
		Sleep(1000);
	}
	SetConsoleTextAttribute(Color, 15);
}


char arr[1500];

int start()
{
	char ran = ('A' + rand() % ('Z' - 'A'));
	char let = ran;
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PlCH;
	PlCH.X = 60;
	PlCH.Y = 15;
	SetConsoleCursorPosition(hC, PlCH);
	printf("%c", let);
	clock_t t0 = clock();
	while (!GetAsyncKeyState(let)) {
		if (GetAsyncKeyState(VK_F1) == -32767) {
			printf("\nYou must press the letter that will be in the center of the screen");
		}
		if (GetAsyncKeyState(VK_F10) == -32767 || GetAsyncKeyState(VK_ESCAPE) == -32767)
		{
			printf("\nEnd");
			Sleep(1000);
			return 0;
		}
	}
	clock_t t1 = clock();
	double time_seconds = (t1 - t0) * CLOCKS_PER_SEC / 10000;
	system("cls");
	printf("Hi");
	printf("\nTo get info press F1");
	printf("\nTo start press F2");
	printf("\nTo exit press F10 or ESC\n");
	char str1[2];
	char str2[16];
	sprintf(&str2, "%.2fs%s", time_seconds / 100, " >  <");
	sprintf(&str1, " %c - ", let);
	strcat(arr, str1);
	strcat(arr, str2);
	printf("%s", arr);
	start();
}

int Uloha26()
{
	system("cls");
	printf("Uloha26");
	printf("\nHi");
	printf("\nTo get info press F1");
	printf("\nTo start press F2");
	printf("\nTo exit press F10 or ESC\n");
	while (1) {
		if (GetAsyncKeyState(VK_F1) == -32767) {
			printf("\nYou must press the letter that will be in the center of the screen");
			printf("\nTo exit press F10 or ESC");
		}
		if (GetAsyncKeyState(VK_F2) == -32767)
			return start(&arr);
		if (GetAsyncKeyState(VK_F10) == -32767 || GetAsyncKeyState(VK_ESCAPE) == -32767)
		{
			printf("\nEnd!");
			Sleep(1000);
			return 0;
		}
	}
}

int Uloha24() {
	system("cls");
	printf("Uloha24");
	printf("\nHi\nPress <F1> to select file\nPress <Space> to play\nPress <Alt> to stop video\nPress <Shift> to stop playing\nPress <F10> to escape player\n");
	while (1) {
		if (GetAsyncKeyState(VK_F1) == -32767) {
			char array[100];
			char c[100];
			printf("\nwrite file name:\n");
			scanf("%s", &array);
			strcat(strcat(strcpy(c, "open "), array), " alias myFile");
			DWORD r = mciSendString(c, NULL, 0, 0);
			if (r) {
				printf("Cant`t find file");
			}
			else {
				printf("Your file was found");
			}
			getchar();
		}
		if (GetAsyncKeyState(VK_SPACE) == -32767) {
			mciSendString("play myFile", NULL, 0, 0);
		}
		if (GetAsyncKeyState(VK_MENU) == -32767) {
			mciSendString("pause myFile", NULL, 0, 0);
		}
		if (GetAsyncKeyState(VK_SHIFT) == -32767) {
			mciSendString("close myFile", NULL, 0, 0);
			char array[100];
			char c[100];
			printf("\nwrite file name\n");
			scanf("%s", &array);
			strcat(strcat(strcpy(c, "open "), array), " alias myFile");
			DWORD r = mciSendString(c, NULL, 0, 0);
			if (r) {
				printf("Cant`t find file");
			}
			else {
				printf("Your file was found");
				getchar();
			}
		}
		if (GetAsyncKeyState(VK_F10) == -32767) {
			return 0;
		}
	}
	return 0;
}

main() {
	Uloha211();
	Uloha212();
	Uloha213();
	Uloha214();
	Uloha251();
	Uloha26();
	Uloha24();
}

