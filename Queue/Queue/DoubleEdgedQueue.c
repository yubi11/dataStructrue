#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int elementD;
typedef struct DequeTypeD
{
	elementD data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeTypeD;

void errorD(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_dequeD(DequeTypeD* q)				//덱은 환형큐와 마찬가지로 front,rear가 0으로 초기화 된다.
{
	q->front = q->rear = 0;
}

int is_emptyD(DequeTypeD* q)
{
	return (q->front == q->rear);			// 비어있는지 할 때는 front와 rear이 같으면 된다.
}

int is_fullD(DequeTypeD* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);	//가득찼는지 확인할 때는 front와  rear+1 % 큐사이즈 비교
}

void deque_print(DequeTypeD* q)
{
	printf("DEQUE(front=%d rear = %d) =", q->front, q->rear);	
	if (!is_emptyD(q))
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

void add_rear(DequeTypeD* q, elementD item)
{
	if (is_fullD(q))
		errorD("큐가 포화상태\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;		//뒤쪽에 요소를 추가 할 시, rear를 1증가시키는데, 덱도 환형 큐이므로 rear+ 1 % MAX_QUEUE_SIZE
	q->data[q->rear] = item;
}

elementD delete_front(DequeTypeD* q)
{
	if (is_emptyD(q))
		errorD("큐가 공백상태\n");			
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;		//앞의 요소를 제거 할 시, front를 1증가시킴, 이 또한 rear+1 % MAX_QUEUE_SIZE
	return q->data[q->front];
}

elementD get_front(DequeTypeD* q)
{
	if (is_emptyD(q))
		errorD("큐가 공백상태\n");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];	// front는 그자체로 사용하지 않고, 1칸 증가시켜 사용하는데, 그 이유는 공백과 포화를 구분하기 위해서다.

}

void add_front(DequeTypeD* q, elementD val)
{
	if (is_fullD(q))
		errorD("큐가 포화상태\n");
	q->data[q->front] = val;							// front 부분에 바로 값을 넣고, front를 1칸 감소시킨다. front에 있는 값을 바로사용하지 않으므로 가능.
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

elementD delete_rear(DequeTypeD* q)
{
	int prev = q->rear;
	if (is_emptyD(q))
		errorD("큐가 공백\n");						// rear를 1칸 줄이고, 해당 부분에 값을 넣게 된다. rear는 front와 달리 유효 데이터를 가리키고 있음
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];		// prev는 방금 가리키던 값을 반환하기 위한 용도
}

elementD get_rear(DequeTypeD* q)
{
	if (is_emptyD(q))
		errorD("큐가 공백\n");
	return q->data[q->rear];		// rear부분을 가져옴 
}

/*
int main(void)
{
	DequeTypeD queue;
	
	init_dequeD(&queue);
	for (int i = 0; i < 3; i++)
	{
		add_front(&queue, i);
		deque_print(&queue);
	}
	for (int i = 0; i < 3; i++)
	{
		delete_rear(&queue);
		deque_print(&queue);
	}
	return 0;
}
*/