#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int elementC;

typedef struct QueueTypeC
{
	elementC data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueTypeC;

void errorC(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queueC(QueueTypeC* q)
{
	q->front = q->rear = 0;				//환형 큐는 선형 큐와 달리 0부터 시작함, 초기에 인덱스 0부분은 비워진상태로 큐가 채워짐, 즉 배열사이즈 -1 만큼 저장가능
}

int is_emptyC(QueueTypeC* q)
{
	return (q->front == q->rear);		// 선형큐와 마찬가지로 front와 rear가 같으면 공백상태임
}

int is_fullC(QueueTypeC* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);		// 큐의 마지막인덱스+1 을 큐사이즈로 나누고, 그 나머지 값을 front와 비교 
}

void queue_printC(QueueTypeC* q)
{
	printf("QUEUE(front=%d rear=%d) =", q->front, q->rear);
	if (!is_emptyC(q))
	{
		int i = q->front;
		do
		{
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void enqueueC(QueueTypeC* q, elementC item)
{
	if (is_fullC(q))
		errorC("큐가 포화상태.\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;				// rear는 +1 하고 큐 사이즈로 나눈 나머지값이 된다.
	q->data[q->rear] = item;								// 그리고 그 인덱스에 값을 넣게 됨, 요소를 넣기 전에 인덱스를 1올리고, 값을 일정범위로 유지하는 셈
}

elementC dequeueC(QueueTypeC* q)
{
	if (is_emptyC(q))								
		errorC("큐가 공백\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;				// dequeue 할 시, 바로 해당 인덱스를 pop하는 것이아니라,
	return q->data[q->front];								// front에 1을 올리고 큐 사이즈로 나눈 나머지값을 채택 한 후, 그 인덱스 값을 반환한다.
}


/*
int main(void)
{
	QueueTypeC queue;
	int element;

	init_queueC(&queue);
	printf("데이터 추가단계\n");
	while (!is_fullC(&queue))
	{
		printf("정수를 입력하세요.");
		scanf_s("%d", &element);
		enqueueC(&queue, element);
		queue_printC(&queue);
	}
	printf("큐는 포화상태\n\n");

	printf("데이터 삭제단계\n");
	while (!is_emptyC(&queue))
	{
		element = dequeueC(&queue);
		printf("꺼낸 정수: %d\n", element);
		queue_printC(&queue);
	}
	printf("큐는 공백상태.\n");
	return 0;
}
*/