// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIGITS 4
#define BUCKETS 10

typedef struct QueueNode
{
	int num;
	struct QueueNode* next;
}QueueNode;


typedef struct QueueType
{
	struct QueueNode* front;
	struct QueueNode* rear;
}QueueType;

bool is_empty(QueueType* q)
{
	if (q->front == NULL)
		return true;
	else
		return false;
}

void init(QueueType* q)
{
	q->front = NULL;
	q->rear = NULL;
}

void enqueue(QueueType* q, int num)
{
	QueueNode* temp;
	temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->num = num;
	temp->next = NULL;
	if (!is_empty(q))
	{
		q->rear->next = temp;
		q->rear = temp;
	}
	else
	{
		q->front = temp;
		q->rear = temp;
	}
}

int Dequeue(QueueType* q)
{
	QueueNode* temp = q->front;
	int num;
	q->front = temp->next;
	num = temp->num;
	free(temp);

	if (q->front == NULL)
		q->rear = NULL;

	return num;
}



void RadixSort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		init(&queues[b]);
												// 버킷을 queueType으로 넣어줌 
	for (d = 0; d < DIGITS; d++)				// DIGIT, 즉 숫자 자릿수만큼 반복함
	{
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]);	// 처음 자릿수를 구분하여 넣어주고
		for (b = i = 0; b < BUCKETS; b++)
		{
			while (!is_empty(&queues[b]))		// 다시 꺼냄, 
				list[i++] = Dequeue(&queues[b]);
		}											// 이짓을 자릿수만큼 반복할 시, 모든 수가 정렬될것임
		factor *= 10;
	}
}


// 숫자의 낮은 자릿수(1의자리)부터 버켓으로 이동시킨다.
// 그 후 낮은 수의(1의자리가 낮은) 버켓에서 순차적으로 꺼낸다.
// 그 다음 다음 자릿수(10의자리)부터  해당 버켓으로 이동시킨다.
// 그 후 다시 낮은 수의(10의자리가 낮은) 버켓에서 순차적으로 꺼내면 10의자리 수를 정렬시킬 수 있다.

// 버켓에 넣기전 읽고, 버켓에서 뺄 때 읽는다. d의 자리의 수라면,  d * 2n번을 읽어야 하는셈임
// 즉 시간복잡도는 O(dn)이 된다.

// 버켓의 개수는 키의 표현방법과 관련이 있다, 10진법은 10개, 알파벳은 26개 처럼
// 
// 32비트 정수의 경우, 8비트씩나누면, 2^8만큼의 수를 표현해야하니 버캣은 256개로 늘어나고, 필요한 패스의 수는 4로 줄어든다
// 4비트로 나누면 버캣은 2^4만큼의 수를 표현해야하니 16개의 버켓이 필요하고, 필요한 패스의수는 8,
// 2비트로 나누면 버캣은 4개, 필요한 패스의 수는 16


int main()
{
	int i;
	int n = 20;
	int list[20];

	srand(time(NULL));
	for (i = 0; i < n; i++)
		list[i] = rand() % 10000;

	printf("정렬전: ");
	for (int k = 0; k < n; k++)			//회차마다 출력하기
		printf("%d ", list[k]);
	printf("\n");


	RadixSort(list, 20);

	for (i = 0; i < n; i++)
		printf("%d ",list[i]);
	printf("\n");
	return 0;
}
