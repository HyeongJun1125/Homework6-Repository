#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum
{
    lparen = 0, /* ( 왼쪽 괄호 */
    rparen = 9, /* ) 오른쪽 괄호*/
    times = 7,  /* * 곱셈 */
    divide = 6, /* / 나눗셈 */
    plus = 5,   /* + 덧셈 */
    minus = 4,  /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1; /* postfixStack용 top */
int evalStackTop = -1;    /* evalStack용 top */

int evalResult = 0; /* 계산 결과를 저장 */

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char *c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    printf("\n2021041069 조형준\n");
    char command;

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'i':
        case 'I':
            getInfix();
            break;
        case 'p':
        case 'P':
            toPostfix();
            break;
        case 'e':
        case 'E':
            evaluation();
            break;
        case 'd':
        case 'D':
            debug();
            break;
        case 'r':
        case 'R':
            reset();
            break;
        case 'q':
        case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

void postfixPush(char x) // 연산자를 postfix로 변환하기 위한 스택 배열
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() // 연산자들을 빼내는 Pop 함수
{
    char x;
    if (postfixStackTop == -1) // postfixStack이 비어있으면
        return '\0';
    else
    {
        x = postfixStack[postfixStackTop--]; // StackPointer를 줄이면서 값을 빼냄.
    }
    return x;
}

void evalPush(int x) // 연산자들을 계산하기 위한 스택 배열
{
    evalStack[++evalStackTop] = x;
}

int evalPop() // 계산 연산자들을 빼내는 Pop 함수
{
    if (evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
    switch (symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    default:
        return operand; // 피연산자
    }
}

precedence getPriority(char x) // 입력값에서 우선순위를 비교하는 함수
{
    return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char *c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1); // 비어있으면 붙이기

    else
        strncat(postfixExp, c, 1); // 들어있으면 뒤에 이어붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp; // infixExp의 문자열을 하나씩 읽기 위한 포인터 변수 exp 선언.
    char x;               /* 문자하나를 임시로 저장하기 위한 변수 */
    char token;
    precedence tokenType;
    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while (*exp != '\0')
    {
        token = *exp;                   // 중위수식 연산 배열에서 역참조를 통해 문자열을 받기 위한 문자열 변수 token변수 선언.
        tokenType = getPriority(token); // 읽은 문자열의 우선순위를 계산.

        // 소괄호의 우선순위가 제일 낮음. ( 왜? ')'가 나올 때까지 남아 있어야 하므로)
        if (tokenType == operand) // 피연산자이면 postfixExp 배열에 붙이기.
            charCat(&token);
        else if (tokenType == lparen) //'(' 이면
            postfixPush(token);       // postfix 변환용 Stack에 넣음.
        else if (tokenType == rparen) //')' 이면
        {
            while ((x = postfixPop()) != '(') //'(' 바로 앞까지 모두 pop해와서
                charCat(&x);                  // postfixExp배열에 붙여넣기.
                                              // 결과적으로 소괄호에 있는 값을 모두 postfix로 가져옴.
        }
        else // operator라면
        {
            while (postfixStackTop != -1 && getPriority(postfixStack[postfixStackTop]) >= tokenType)
            {                     // operator 스택에 값이 존재하면서 Stack 최상단 연산자의 우선순위가 token, 즉 현재 가리키는 것보다 우선순위보다 높다면
                x = postfixPop(); // 꺼내와서
                charCat(&x);      // postfixExp에 붙인다.
            }
            postfixPush(token); // 현재 가리키는 연산자를 postfixStack에 추가.
        }
        exp++;
        /* 필요한 로직 완성 */
    }
    while (postfixStackTop != -1) // postfixStack에 남아있는 연산자들을 모두 pop해서 가져오기.
    {
        x = postfixPop();
        charCat(&x);
    }
}
void debug()
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);
    printf("postExp =  %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c  ", postfixStack[i]);

    printf("\n");
}

void reset()
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation()
{
    char *exp = postfixExp;
    int op1, op2, value = 0; // op1, op2 : 피연산자, value는 계산 결과값
    char x;                  // 처리할 문자열

    while (*exp != '\0')
    {
        x = *exp;              // 역참조를 통해 실제 스택에 저장된 char값이 x에 저장됨.
        if (isdigit(x))        // 만약 x가 정수이면
            evalPush(x - '0'); // 계산을 위한 스택에 저장.
                               //-'0'은 정수형으로 변환하는 기법 (ACII코드)
                               // x-'0'이 아닌 symbol을 넣을 경우 x의 ASCII값이 push됨.

        else // 만약 char값에 operator가 나왔다면
        {
            // 2개의 피연산자를 꺼내옴. (스택이므로 들어간 역순으로 받아옴)
            op2 = evalPop();
            op1 = evalPop();

            switch (x) // 각 operator에 맞는 계산을 수행하고나서
            {
            case '+':
                value = op1 + op2;
                break;
            case '-':
                value = op1 - op2;
                break;
            case '*':
                value = op1 * op2;
                break;
            case '/':
                value = op1 / op2;
                break;
            }
            evalPush(value); // 수행된 계산을 다시 스택으로 push함.
        }
        exp++; // 포인터를 증가시키며 이 과정을 배열의 끝인 '\0'이 나올 때까지 반복.
    } // 최종적으로 후위수식자의 연산 결과값이 저장되게 되며
    evalResult = evalPop(); // 결과값을 evalResult 변수에 저장.
    /* postfixExp, evalStack을 이용한 계산 */
}
