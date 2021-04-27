#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left, * right;
}TreeNode;

#define MAX_QUEUE_SIZE 100

typedef TreeNode* element;
typedef struct QueueType
{
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태 입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}


void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q);

	if (ptr == NULL)
		return;
	enqueue(&q, ptr);
	while (!is_empty(&q))
	{
		ptr = dequeue(&q);
		printf("[%d]", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

TreeNode qn1 = { 1,NULL,NULL };
TreeNode qn2 = { 4, &qn1,NULL };
TreeNode qn3 = { 16,NULL,NULL };
TreeNode qn4 = { 25,NULL,NULL };
TreeNode qn5 = { 20,&qn3,&qn4 };
TreeNode qn6 = { 15,&qn2,&qn5 };
TreeNode* qroot = &qn6;

/*
int main()
{
	printf("레벨 순회=");
	level_order(qroot);
	printf("\n");
	return 0;
	return 0;
}
*/