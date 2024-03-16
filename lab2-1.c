#include <stdio.h>
int main()
{
    printf("----- 2021041069 조형준 -----\n");
    char charType;
    int integerType;
    float floatType;
    double doubleType;
    // 깃허브 올리는 용도
    printf("Size of char: %ld byte\n", sizeof(charType));      // 자료형 char은 1byte이므로 1이 출력.
    printf("Size of int: %ld bytes\n", sizeof(integerType));   // 자료형 int는 4byte 이므로 4가 출력.
    printf("Size of float: %ld bytes\n", sizeof(floatType));   // 자료형 float는 4byte 이므로 4이 출력.
    printf("Size of double: %ld bytes\n", sizeof(doubleType)); // 자료형 double는 8byte 이므로 8이 출력.
    printf("-----------------------------------------\n");
    printf("Size of char: %ld byte\n", sizeof(charType));      // 자료형 char은 1byte이므로 1이 출력.
    printf("Size of int: %ld bytes\n", sizeof(integerType));   // 자료형 int는 4byte 이므로 4가 출력.
    printf("Size of float: %ld bytes\n", sizeof(floatType));   // 자료형 float는 4byte 이므로 4이 출력.
    printf("Size of double: %ld bytes\n", sizeof(doubleType)); // 자료형 double는 8byte 이므로 8이 출력.
    printf("-----------------------------------------\n");
    printf("Size of char*: %ld byte\n", sizeof(char *));      // 포인터 자료형 char의 메모리 공간은 4이므로 4가 출력. (x86기준)
    printf("Size of int*: %ld bytes\n", sizeof(int *));       // 포인터 자료형 int의 메모리 공간은 4이므로 4가 출력. (x86기준)
    printf("Size of float*: %ld bytes\n", sizeof(float *));   // 포인터 자료형 float의 메모리 공간은 4이므로 4가 출력. (x86기준)
    printf("Size of double*: %ld bytes\n", sizeof(double *)); // 포인터 자료형 double의 메모리 공간은 4이므로 4가 출력. (x86기준)
    return 0;
}

// git 연동

/*포인터 자료형의 경우 x86인 32bit 운영체제에서는 4바이트가 출력이 되지만
  x64인 64it 운영체제에서는 8바이트로 출력이 되는 것을 확인함.*/

// 포인터는 특정 변수의 메모리 주소를 저장하는 자료형이며 1byte가 8bit이므로
//  따라서 32bit에서 저장 가능한 메모리의 크기는 최대 4byte이다.
//  그러므로 x86인 32비트 운영체제 안에서 모든 포인터 자료형의 크기는 4byte이므로 4를 출력.

// 이와 같은 이유로 64비트 운영체제에서는 64bit는 8byte이므로
// 8byte로 모든 주소를 표현할 수 있기에 8byte가 메모리의 크기가 되며,
//  실제로 x64에서 실행 결과 모든 포인터 자료형의 크기가 8byte인 것을 확인할 수 있음.