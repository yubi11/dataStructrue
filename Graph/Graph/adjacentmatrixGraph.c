#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//인접행렬은 정방행렬임, N x N행렬, 

#define MAX_VERTICES 50
typedef struct graphtype 
{
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];

}GraphType;


typedef struct queueNode
{
	int v;
	struct queueNode* link;
}QueueNode;

typedef struct queueType
{
	int size;
	struct queueNode* head;
	struct queueNode* tail;
}QueueType;

void init_queue_mat(QueueType* q)
{
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
}

void enqueue_mat(QueueType* q, int v)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->v = v;
	if (q->size == 0)
	{
		q->head = newNode;
		q->tail = newNode;
		q->head->link = NULL;
	}
	else
	{
		q->tail->link = newNode;
		q->tail = newNode;
	}
	q->size++;
}

int dequeue_mat(QueueType* q)
{
	if (q->size == 0)
		return -1;
	int res = q->head->v;
	QueueNode* temp = q->head;
	q->head = q->head->link;
	free(temp);
	q->size--;
	return res;
}

void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end)	//start end 는 인덱스이므로 graphtype의 n을 넘기면 없는 인덱스에 접근한다는것
{
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "그래프: 정점번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//그래프의 탐색으로는 DFS, BFS가 있다. 깊이 우선 탐색, 너비 우선 탐색

//DFS는 한방향으로 갈 수 있을 때까지 가다가 더 이상 갈 수 없게 되면 갈림길로 돌아가기 시작함
//그러므로 스택이 필요하다 (순환호출로 묵시적인 스택 사용).

visited[MAX_VERTICES];
void dfs_mat(GraphType* g, int v)		//시간복잡도 O(n^2) 순환호출때문에 n번, for문 때문에 n번이기때문에 n^2
{
	int w;
	visited[v] = true;
	printf("정점 %d->", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
}

void bfs_mat(GraphType* g, int v)
{
	int w;
	QueueType q;
	init_queue_mat(&q);
	visited[v] = true;
	printf("%d 방문-> ", v);
	enqueue_mat(&q, v);
	while (q.size != 0)
	{
		v = dequeue_mat(&q);
		for(w=0;w<g->n;w++)
			if (g->adj_mat[v][w] && !visited[w])
			{
				visited[w] = true;
				printf("%d 방문->", w);
				enqueue_mat(&q, w);
			}
	}
}




/*
void main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 6; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);
	
	
//	printf("깊이 우선 탐색\n");
//	bfs_mat(g, 0);
//	printf("\n");
	

	printf("너비 우선 탐색\n");
	bfs_mat(g, 0);
	printf("\n");
	free(g);


}
*/