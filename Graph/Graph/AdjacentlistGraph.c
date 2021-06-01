// 각 정점에 인접한 정점들을 연결리스트로 표현
// 동일한 정점에 대해서:
// edge가 많을 때는(dense) 인접행렬이 유리 
// edge가 적을 때는(sparse) 인접리스트가 유리함
// 요즘 컴퓨터는 메모리가 넉넉하기 때문에, 인접행렬을 사용하여 연산을 더 쉽게 함

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct graphNode
{
	struct graphNode* link;
	int vertex;
}GraphNode;


typedef struct graphtype
{
	int n;
	struct graphNode* adj_list[MAX_VERTICES];
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

void init_queue(QueueType* q)
{
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
}

void enqueue(QueueType* q,int v)
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

int dequeue(QueueType* q)
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


void init_list(GraphType* g)
{
	int i = 0;
	g->n = 0;
	for (i = 0; i <MAX_VERTICES; i++)
		g->adj_list[i] = NULL;
}

void insert_vertex_list(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge_list(GraphType* g, int start, int end)	//start end 는 인덱스이므로 graphtype의 n을 넘기면 없는 인덱스에 접근한다는것
{
	GraphNode* temp;
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "그래프: 정점번호 오류");
		return;
	}
	temp = (GraphNode*)malloc(sizeof(GraphNode));
	temp->vertex = end;
	temp->link = g->adj_list[start];
	g->adj_list[start] = temp;
}

//그래프의 탐색으로는 DFS, BFS가 있다. 깊이 우선 탐색, 너비 우선 탐색

//DFS는 한방향으로 갈 수 있을 때까지 가다가 더 이상 갈 수 없게 되면 갈림길로 돌아가기 시작함
//그러므로 스택이 필요하다 (순환호출로 묵시적인 스택 사용).

visited[MAX_VERTICES];
void dfs_list(GraphType* g, int v)		// 시간복잡도 O(n+e) 순환호출 때문에 n번 + 간선의 개수만큼 돌아가게 됨 
{
	GraphNode* w;
	visited[v] = true;
	printf("정점 %d->", v);
	for (w = g->adj_list[v]; w; w = w->link)	// for문은 총 e(정점간선)번 돌아감 (자신과 연결된 부분만 순회하므로 나중에 총합 e(총간선)밖에 안됨) 
		if (!visited[w->vertex])				// 즉 for문은 e(정점간선)번 수행되고, 결국엔 모든 정점을 돌게 되므로 n번 
			dfs_list(g, w->vertex);				// 총 O(n+e(총간선))임
}										//각각의 정점이 이미 인접리스트와 연결되어 있어서, 
										//각각의 정점의 연결된 간선만 for문으로 e번 호출하는 것임
										//결과적으로는 모든 정점에 가기위해 dfs n번, for문의 총합은 e번이 될 것임


void bfs_list(GraphType* g, int v)		// 시간복잡도 O(n+e) 순환호출 때문에 n번 + 간선의 개수만큼 돌아가게 됨
{
	GraphNode* w;
	QueueType q;
	init_queue(&q);
	visited[v] = true;
	printf("%d 방문-> ", v);			// 처음 정점을 출력하고.
	enqueue(&q, v);					// 처음 정점을 인큐로 저장한다.
	while (q.size != 0)
	{
		v = dequeue(&q);			// 정점을 디큐하여 그 인접 정점을 모두 찾고 출력하고, 그 인접정점의 인접정점을 또 찾아나가는 식임
		for (w = g->adj_list[v]; w; w = w->link)	// dfs와 마찬가지로 for문에 대해서는 간선의 개수 만큼 돌아가고, 정점방문은 n번이다.
			if (!visited[w->vertex])				// 즉 시간복잡도는 O(n+e)
			{
				visited[w->vertex] = true;
				printf("%d 방문->", w->vertex);
				enqueue(&q, w->vertex);
			}
	}
}


/*
void main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init_list(g);
	for (int i = 0; i < 4; i++)
		insert_vertex_list(g, i);
	insert_edge_list(g, 0, 1);
	insert_edge_list(g, 0, 2);
	insert_edge_list(g, 0, 3);
	insert_edge_list(g, 1, 2);
	insert_edge_list(g, 2, 3);

	
//	printf("깊이 우선 탐색\n");
//	dfs_list(g, 0);
//	printf("\n");
	
	printf("너비 우선 탐색\n");
	bfs_list(g, 0);
	printf("\n");

	free(g);
}
*/