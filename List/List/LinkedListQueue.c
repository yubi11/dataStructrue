#include <stdio.h>
#include <malloc.h>

typedef int elementQ;

typedef struct QueueNode
{
	elementQ data;
	struct QueueNode* link;
}QueueNode;


typedef struct
{
	QueueNode* front,*rear;					//큐이므로 front와 rear를 가리키는 포인터 (doubled edged queue임)
}LinkedQueueType;

void initQ(LinkedQueueType* q)
{
	q->front = NULL;
	q->rear = NULL;								// 큐는 front와 rear를 NULL로 하여 초기화
}

int is_emptyQ(LinkedQueueType* q)
{
	return (q->front == NULL);					// front가 빈다는 말은 곧 큐에 아무것도 없다는 뜻
}

void enqueueQ(LinkedQueueType* q, elementQ item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));		//temp 동적할당 후
	temp->data = item;												
	temp->link = NULL;												//데이터 저장
	if (is_emptyQ(q))											// 초기에 큐가 비어있다면 front와 rear를 자신으로 만들음
	{
		q->front = temp;
		q->rear = temp;
	}
	else
	{															// 만약 값이 들어있다면, 맨 뒤에있는 노드를 지금생성한 노드로 이어줌
		q->rear->link = temp;									// rear포인터는 방금 생성한 노드로 설정
		q->rear = temp;
	}
}
void print_queue(LinkedQueueType* q)
{
	for (QueueNode* p = q->front; p != NULL; p = p->link)		// front에서 시작해서 위로 쭉올라가면서 출력
		printf("%d->", p->data);								// 스택과 다르게 왼쪽부터 오른쪽으로 출력함
	printf("NULL\n");
}

elementQ dequeueQ(LinkedQueueType* q)
{
	if (is_emptyQ(q))
	{
		fprintf(stderr, "큐 빔");
		exit(1);
	}
	else
	{
		QueueNode* temp = q->front;								// 삭제할 디큐 노드를 임시로 저장하여
		int data = temp->data;									// 해당 노드의 데이터를 빼주고
		q->front = q->front->link;								// front포인터에 있는 노드를 삭제할 것이므로, q->front의 다음값을 설정
		free(temp);												// 기존 front는 삭제
		return data;
	}
}

int main(void)
{
	LinkedQueueType q;
	initQ(&q);
	enqueueQ(&q, 1);
	print_queue(&q);
	enqueueQ(&q, 2);
	print_queue(&q);
	enqueueQ(&q, 3);
	print_queue(&q);

	dequeueQ(&q);
	print_queue(&q);
	dequeueQ(&q);
	print_queue(&q);
	dequeueQ(&q);
	print_queue(&q);
	return 0;
}