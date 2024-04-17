#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum
{
    lparen = 0, /* ( ���� ��ȣ */
    rparen = 9, /* ) ������ ��ȣ*/
    times = 7,  /* * ���� */
    divide = 6, /* / ������ */
    plus = 5,   /* + ���� */
    minus = 4,  /* - ���� */
    operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];    /* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];        /* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1; /* postfixStack�� top */
int evalStackTop = -1;    /* evalStack�� top */

int evalResult = 0; /* ��� ����� ���� */

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
    printf("\n2021041069 ������\n");
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

void postfixPush(char x) // �����ڸ� postfix�� ��ȯ�ϱ� ���� ���� �迭
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() // �����ڵ��� ������ Pop �Լ�
{
    char x;
    if (postfixStackTop == -1) // postfixStack�� ���������
        return '\0';
    else
    {
        x = postfixStack[postfixStackTop--]; // StackPointer�� ���̸鼭 ���� ����.
    }
    return x;
}

void evalPush(int x) // �����ڵ��� ����ϱ� ���� ���� �迭
{
    evalStack[++evalStackTop] = x;
}

int evalPop() // ��� �����ڵ��� ������ Pop �Լ�
{
    if (evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
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
        return operand; // �ǿ�����
    }
}

precedence getPriority(char x) // �Է°����� �켱������ ���ϴ� �Լ�
{
    return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char *c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1); // ��������� ���̱�

    else
        strncat(postfixExp, c, 1); // ��������� �ڿ� �̾���̱�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
    /* infixExp�� ���� �ϳ����� �б����� ������ */
    char *exp = infixExp; // infixExp�� ���ڿ��� �ϳ��� �б� ���� ������ ���� exp ����.
    char x;               /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
    char token;
    precedence tokenType;
    /* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
    while (*exp != '\0')
    {
        token = *exp;                   // �������� ���� �迭���� �������� ���� ���ڿ��� �ޱ� ���� ���ڿ� ���� token���� ����.
        tokenType = getPriority(token); // ���� ���ڿ��� �켱������ ���.

        // �Ұ�ȣ�� �켱������ ���� ����. ( ��? ')'�� ���� ������ ���� �־�� �ϹǷ�)
        if (tokenType == operand) // �ǿ������̸� postfixExp �迭�� ���̱�.
            charCat(&token);
        else if (tokenType == lparen) //'(' �̸�
            postfixPush(token);       // postfix ��ȯ�� Stack�� ����.
        else if (tokenType == rparen) //')' �̸�
        {
            while ((x = postfixPop()) != '(') //'(' �ٷ� �ձ��� ��� pop�ؿͼ�
                charCat(&x);                  // postfixExp�迭�� �ٿ��ֱ�.
                                              // ��������� �Ұ�ȣ�� �ִ� ���� ��� postfix�� ������.
        }
        else // operator���
        {
            while (postfixStackTop != -1 && getPriority(postfixStack[postfixStackTop]) >= tokenType)
            {                     // operator ���ÿ� ���� �����ϸ鼭 Stack �ֻ�� �������� �켱������ token, �� ���� ����Ű�� �ͺ��� �켱�������� ���ٸ�
                x = postfixPop(); // �����ͼ�
                charCat(&x);      // postfixExp�� ���δ�.
            }
            postfixPush(token); // ���� ����Ű�� �����ڸ� postfixStack�� �߰�.
        }
        exp++;
        /* �ʿ��� ���� �ϼ� */
    }
    while (postfixStackTop != -1) // postfixStack�� �����ִ� �����ڵ��� ��� pop�ؼ� ��������.
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
    int op1, op2, value = 0; // op1, op2 : �ǿ�����, value�� ��� �����
    char x;                  // ó���� ���ڿ�

    while (*exp != '\0')
    {
        x = *exp;              // �������� ���� ���� ���ÿ� ����� char���� x�� �����.
        if (isdigit(x))        // ���� x�� �����̸�
            evalPush(x - '0'); // ����� ���� ���ÿ� ����.
                               //-'0'�� ���������� ��ȯ�ϴ� ��� (ACII�ڵ�)
                               // x-'0'�� �ƴ� symbol�� ���� ��� x�� ASCII���� push��.

        else // ���� char���� operator�� ���Դٸ�
        {
            // 2���� �ǿ����ڸ� ������. (�����̹Ƿ� �� �������� �޾ƿ�)
            op2 = evalPop();
            op1 = evalPop();

            switch (x) // �� operator�� �´� ����� �����ϰ���
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
            evalPush(value); // ����� ����� �ٽ� �������� push��.
        }
        exp++; // �����͸� ������Ű�� �� ������ �迭�� ���� '\0'�� ���� ������ �ݺ�.
    } // ���������� ������������ ���� ������� ����ǰ� �Ǹ�
    evalResult = evalPop(); // ������� evalResult ������ ����.
    /* postfixExp, evalStack�� �̿��� ��� */
}
