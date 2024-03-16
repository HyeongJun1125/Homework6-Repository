#include <stdio.h>
int main()
{
    printf("----- 2021041069 조형준 -----\n");
    int i;
    int *ptr;
    int **dptr;
    i = 1234;

    // 해당 메모리= 주소는 컴파일되어 실행된 창에 있는
    // 제 메모리 주소값을 기준으로 작성하였습니다.

    printf("[checking values before ptr = &i] \n");
    printf("value of i == %d\n", i);    // i값을 출력하므로 (1234)가 출력됨.
    printf("address of i == %p\n", &i); // i의 주소값 (0116F994)를 출력.
    // printf("value of ptr == %p\n", ptr); //ptr이 가리키는 값이 없음.(초기화 X)
    printf("address of ptr == %p\n", &ptr);             // ptr이라는 포인터 변수가 저장된 메모리 주소값(0116F988)을 출력.
    ptr = &i; /* ptr is now holding the address of i */ // 포인터 변수 ptr이 int형 변수 i의 주소값을 가짐.
    printf("\n[checking values after ptr = &i] \n");
    printf("value of i == %d\n", i);                          // i의 값은 바뀌지 않았으므로 똑같이 (1234)를 출력.
    printf("address of i == %p\n", &i);                       // i의 주소값 또한 바뀌지 않았으므로 동일하게 (0116F994).
    printf("value of ptr == %p\n", ptr);                      // ptr의 값은 i의 주소값을 참조하므로 i의 주소값인 (0116F994)를 출력.
    printf("address of ptr == %p\n", &ptr);                   // 포인터 변수 ptr의 주소값은 기존과 동일한 (0116F988).
    printf("value of *ptr == %d\n", *ptr);                    // 포인터 변수가 참조하는 값은 i의 값이므로 (1234) 출력.
    dptr = &ptr; /* dptr is now holding the address of ptr */ // 포인터변수 dptr이 포인터변수 ptr의 주소값을 가짐.
    printf("\n[checking values after dptr = &ptr] \n");
    printf("value of i == %d\n", i);           // 변동 없으므로 (1234) 출력.
    printf("address of i == %p\n", &i);        // 변동 없으므로 (0116F994) 출력.
    printf("value of ptr == %p\n", ptr);       // 변동 없으므로 (0116F994)출력.
    printf("address of ptr == %p\n", &ptr);    // 변동 없으므로 (0116F988) 출력.
    printf("value of *ptr == %d\n", *ptr);     // 변동 없으므로 (1234) 출력.
    printf("value of dptr == %p\n", dptr);     // dptr은 ptr의 주소값을 가지므로 (0116F988) 출력.
    printf("address of dptr == %p\n", &dptr);  // dptr의 주소값은 0116F97C에 할당이 됨. (내 컴퓨터 기준)
    printf("value of *dptr == %p\n", *dptr);   // dptr의 참조값, 즉 ptr의 값을 참조하므로 (0116F994) 출력.
    printf("value of **dptr == %d\n", **dptr); // dptr=&ptr, *dptr=*&ptr=ptr=&i 이므로 따라서 **dptr=i가 성립됨.
    // 따라서 i의 값인 1234가 출력됨.

    *ptr = 7777; /* changing the value of *ptr */ // ptr이 가지는 주소의 참조값을 변경.
    printf("\n[after *ptr = 7777] \n");
    printf("value of i == %d\n", i);                  // ptr은 i의 주소값을 가지는데 그 주소의 참조값이 변경되었으므로 i의 값 또한 7777로 변경됨.
    printf("value of *ptr == %d\n", *ptr);            //*ptr은 위에서 서술했듯 i이므로 따라서 변경된 i의 값인 (7777)이 출력.
    printf("value of **dptr == %d\n", **dptr);        // dptr의 이중 참조 또한 위에서 서술했듯 i의 값이므로 따라서 (7777) 출력.
    **dptr = 8888; /* changing the value of **dptr */ //**dptr이 참조하는 값이 8888로 변경.
    printf("\n[after **dptr = 8888] \n");
    printf("value of i == %d\n", i); // dptr=&ptr, *dptr=*&ptr=ptr=&i 이므로 따라서 **dptr=i가 성립.
    // 그러므로 변경된 i의 값인 8888이 출력.
    printf("value of *ptr == %d\n", *ptr);     // 위와 같은 이유로 *ptr=i이므로 i의 값인 8888 출력.
    printf("value of **dptr == %d\n", **dptr); // 위와 같은 이유로 i의 값인 8888이 출력.
    return 0;
}