/**
 * circularQ.c
 *
 * School of Computer Science,
 * Chungbuk National University
 */
#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct
{
	element queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
} QueueType;

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element *item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	printf("\n2021041069 ������\n");
	QueueType *cQ = createQueue();
	element data;
	char command;

	do
	{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'i':
		case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd':
		case 'D':
			deQueue(cQ, &data);
			break;
		case 'p':
		case 'P':
			printQ(cQ);
			break;
		case 'b':
		case 'B':
			debugQ(cQ);
			break;
		case 'q':
		case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

QueueType *createQueue() // ť ����
{
	QueueType *cQ = (QueueType *)malloc(sizeof(QueueType));
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		cQ->queue[i] = printf(" ");
		/* code */
	}

	// front, rear�� ��� 0���� �ʱⰪ ����.
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
	if (cQ == NULL)
		return 1;
	free(cQ); // ť �����Ҵ� ����
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); // ���� �Է¹���
	return item;
}

/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear) // ���� ť���� front == rear, �� ���� ���� ����ų ��� ť�� ��������� ��Ÿ��.
		return 1;

	return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if (cQ->front == (cQ->rear + 1) % MAX_QUEUE_SIZE)
	{
		// rear+1�� �ϸ� ��ü ������ ������ MAX QUEUE_SIZE�̹Ƿ�
		// ���� �� ���� ť���� ���� ���, �������� 0�� front�� �������� ���� ����.
		return 1;
	}
	return 0;
}

/* complete the function */
void enQueue(QueueType *cQ, element item) // ť�� ���� �ִ� �Լ�
{
	if (isFull(cQ)) // ť�� ���� ���ִ� ���
	{
		printf("\nQueue is full\n"); // ���� á�ٴ� �޽����� ����ϰ�
		return;						 // �Լ� ����
	}
	else
	{
		// 0,1,2,3�� ������ ������ ��.
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // cQ->rear++;
		cQ->queue[cQ->rear] = item;					// ������Ų rear�� ����Ű�� ���� ���� �־���.
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) // ť���� ���� �����ϴ� �Լ�
{
	if (isEmpty(cQ)) // ť�� ������� ���
	{
		printf("\nQueue is empty\n"); // ����ִٴ� �޽����� ����ϰ�
		return;						  // �Լ� ����
	}
	else
	{
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front�� ����Ű�� �ε����� �� ĭ ������Ű��
		*item = cQ->queue[cQ->front];				  // front�� ����Ű�� ���� ���� item�� ����
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; // front�� ����Ű�� �ε����� �������� ���
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;	  // rear�� ����Ű�� �ε����� �������� ���

	printf("Circular Queue : [");

	i = first;
	while (i != last)
	{
		printf("%3c", cQ->queue[i]);  // ť�� ���� ���
		i = (i + 1) % MAX_QUEUE_SIZE; // i++;
	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) // ��ü ť�� ũ�⸸ŭ
	{
		if (i == cQ->front) // front�� ����Ű�� ���̸�
		{
			printf("  [%d] = front\n", i); // front�� ����Ű�� ���� ���.
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // front�� ����Ű�� ���� �ƴ� ���, �� ť�� ����ִ� ���� ���.
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front�� rear�� ����Ű�� �ִ� ���� ���
}
