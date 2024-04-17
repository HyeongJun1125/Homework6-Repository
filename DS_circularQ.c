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
	printf("\n2021041069 조형준\n");
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

QueueType *createQueue() // 큐 생성
{
	QueueType *cQ = (QueueType *)malloc(sizeof(QueueType));
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		cQ->queue[i] = printf(" ");
		/* code */
	}

	// front, rear를 모두 0으로 초기값 설정.
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
	if (cQ == NULL)
		return 1;
	free(cQ); // 큐 동적할당 해제
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); // 값을 입력받음
	return item;
}

/* complete the function */
int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear) // 원형 큐에서 front == rear, 즉 같은 곳을 가리킬 경우 큐는 비어있음을 나타냄.
		return 1;

	return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if (cQ->front == (cQ->rear + 1) % MAX_QUEUE_SIZE)
	{
		// rear+1을 하면 전체 데이터 개수인 MAX QUEUE_SIZE이므로
		// 가득 찬 원형 큐에서 나눌 경우, 나머지가 0인 front가 나오도록 유도 가능.
		return 1;
	}
	return 0;
}

/* complete the function */
void enQueue(QueueType *cQ, element item) // 큐에 값을 넣는 함수
{
	if (isFull(cQ)) // 큐가 가득 차있는 경우
	{
		printf("\nQueue is full\n"); // 가득 찼다는 메시지를 출력하고
		return;						 // 함수 종료
	}
	else
	{
		// 0,1,2,3의 값만을 가지게 됨.
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // cQ->rear++;
		cQ->queue[cQ->rear] = item;					// 증가시킨 rear가 가리키는 곳에 값을 넣어줌.
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) // 큐에서 값을 제거하는 함수
{
	if (isEmpty(cQ)) // 큐가 비어있을 경우
	{
		printf("\nQueue is empty\n"); // 비어있다는 메시지를 출력하고
		return;						  // 함수 종료
	}
	else
	{
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front가 가리키는 인덱스를 한 칸 증가시키고
		*item = cQ->queue[cQ->front];				  // front가 가리키는 곳의 값을 item에 저장
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; // front가 가리키는 인덱스의 다음부터 출력
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;	  // rear가 가리키는 인덱스의 다음까지 출력

	printf("Circular Queue : [");

	i = first;
	while (i != last)
	{
		printf("%3c", cQ->queue[i]);  // 큐의 값을 출력
		i = (i + 1) % MAX_QUEUE_SIZE; // i++;
	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) // 전체 큐의 크기만큼
	{
		if (i == cQ->front) // front가 가리키는 곧이면
		{
			printf("  [%d] = front\n", i); // front가 가리키는 값을 출력.
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // front가 가리키는 값이 아닌 경우, 각 큐에 들어있는 값을 출력.
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front와 rear가 가리키고 있는 곳을 출력
}
