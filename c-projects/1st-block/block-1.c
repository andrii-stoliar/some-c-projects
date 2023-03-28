#include <stdio.h>
#include <float.h>
#include "Header.h"

main() {
    Uloha1();
    Uloha2();
    Uloha3();
    Uloha4();
    Uloha5();
}

int funcfact(int y) {
    int sum = 1;
    while (y != 0) {
        sum = sum * y;
        y = y - 1; 
    }
    return sum;
}

float sinus(float radians, float epsilon) {
    int sumn = radians; 
    int sump = radians + 1;  
    int n = 3; 
    int x = radians;  
    int fact; 
    int slag = 0;
    while (sump - sumn != epsilon || sumn - sump != epsilon) {
        sump = sumn;
        fact = funcfact(n);
        slag = (x^n) / fact;
        sumn = sumn - slag;
        n = n + 2;
        fact = funcfact(n);
        slag = (x ^ n) / fact;
        sumn = sumn + slag;
        n = n + 2;
    }
    return sumn; 
}

void Uloha1() {
    printf("<Uloha 1.1>\n");
    printf("symbol: 1)X 2)33777\ndesiatkova: 1)%d 2)33777\nsestnastkova: 1)%0.2X 2)%0.2X\n", 'X', 'X', 33777);
    printf("binarna: 1)");

    int a = 'X';
    int array[16];
    for (int i = 0; i < 16; i++) {
        if (a % 2 == 0) array[15 - i] = 0;
        else array[15 - i] = 1;
        a = a / 2;
    }
    for (int i = 0; i < 16; i++) {
        printf("%d", array[i]);
    }
    printf(" 2)");

    int b = 33777;
    for (int j = 0; j < 16; j++) {
        if (b % 2 == 0) array[15 - j] = 0;
        else array[15 - j] = 1;
        b = b / 2;
    }
    for (int j = 0; j < 16; j++) {
        printf("%d", array[j]);
    }
}

void Uloha2() {
    int n;
    printf("\n\n<Uloha 1.2>");
    printf("\nUkazte cislo:");
    scanf_s("%d", &n);
    printf("\nRimske:");
    while (n != 0) {
        if (n == 100) {
            printf("C");
            n = n - 100;
        }
        else if (n >= 90) {
            printf("XC");
            n = n - 90;
        }
        else if (n >= 50) {
            printf("L");
            n = n - 50;
        }
        else if (n >= 40) {
            printf("XL");
            n = n - 40;
        }
        else if (n >= 10) {
            printf("X");
            n = n - 10;
        }
        else if (n >= 9) {
            printf("IX");
            n = n - 9; 
        }
        else if (n >= 5) {
            printf("V");
            n = n - 5;
        }
        else if (n >= 4) {
            printf("IV");
            n = n - 4;
        }
        else if (n >= 1) {
            printf("I");
            n = n - 1;
        }
    }

}

void Uloha3() {
    printf("\n\n<Uloha 1.3>");
    int k = 0;
	int a = 1;
	int b = 1;
	int temp = 0;
	printf("\nNapiste k: ");
	scanf_s("%d", &k);
	printf("%d ", a);
	while (b < k) {
		printf("%d ", b);
		temp = a;
		a = b;
		b = b + temp;
	}
}

void Uloha4() {
    printf("\n\n<Uloha 1.4>");
    float f_eps = 1;
    double d_eps = 1;
    while (f_eps/2 + 1 != 1) {
        f_eps = f_eps / 2;
    }
    while (d_eps/2 + 1 != 1) {
        d_eps = d_eps / 2;
    }
    printf("float:%g, const:%g", f_eps, FLT_EPSILON);
    printf("\ndouble:%g, const:%g", d_eps, DBL_EPSILON);
}

void Uloha5() {
    printf("\n\n<Uloha 1.5>");
    float rad = 0; float eps = 0; float f = 0;
    printf("\nUkazte sin:");
    scanf_s("%g", &rad);
    printf("\nUkazte eps:");
    scanf_s("%g", &eps);
    f = sinus(rad, eps);
    printf("%g", &f);
}

