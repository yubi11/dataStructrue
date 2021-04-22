#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int elementL;					//자료형 타입은 바뀔수있으므로

typedef struct QueueTypeL				
{
	int front;						// 큐의 맨 앞
	int rear;						// 큐의 맨 뒤
	elementL data[MAX_QUEUE_SIZE];	// 큐의 자료를 배열로 나타냄, 크기 제한 있음
}QueueTypeL;

void errorL(char* message)		//에러 출력 함수
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queueL(QueueTypeL* q)		// 큐 초기화 (선형 큐는 front,rear를 -1로 초기화)
{
	q->rear = -1;
	q->front = -1;
}

void queue_printL(QueueTypeL* q)		// 큐의 모든 요소 출력
{
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i <= q->front || i > q->rear)		// 현재 순회하는 부분이 front와 rear사이에 없다면 빈공간 출력
			printf("  | ");
		else
			printf("%d| ", q->data[i]);			// 순회부분이 front와 rear 사이에 있다면 요소 출력
	}
	printf("\n");
}

int is_fullL(QueueTypeL* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)			// 큐 포화상태는 MAX -1 로  rear를 검사
		return 1;
	else
		return 0;
}

int is_emptyL(QueueTypeL* q)					// 큐 공백상태는 front와 rear값이 같아야 함
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueueL(QueueTypeL* q, int item)		
{
	if (is_fullL(q))
	{
		errorL("큐가 포화상태.\n");
		return;
	}
	q->data[++(q->rear)] = item;			// rear값을 올린 후, 해당 인덱스에 요소를 넣음 (rear는 -1부터 싲가하니 1올리고 삽입)
}

int dequeueL(QueueTypeL* q)
{
	if (is_emptyL(q))
	{
		errorL("큐가 공백상태.\n");
		return -1;
	}
	int item = q->data[++(q->front)];	//// front값을 올린 후, 해당 인덱스에 있는 값을 반환 ( front는 -1부터 시작하니 1올리고 반환)
	return item;
}


/*
int main(void)
{
	int item = 0;
	QueueType q;
	
	init_queue(&q);

	enqueue(&q, 10);
	queue_print(&q);
	enqueue(&q, 20);
	queue_print(&q);
	enqueue(&q, 30);
	queue_print(&q);

	item = dequeue(&q);
	queue_print(&q);
	item = dequeue(&q);
	queue_print(&q);
	item = dequeue(&q);
	queue_print(&q);

	return 0;
}
*/