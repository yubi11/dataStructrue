// 방향그래프에서 간선 <u,v>가 있다면 정점 u는 정점 v에 선행함
// 방향 그래프 정점들의 선행순서를 위배하지 않으면서 모든 정점을 나열하는 것,

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

typedef struct stackNode
{
	int v;
	struct stackNode* link;
}StackNode;

typedef struct stackType
{
	int size;
	struct stackNode* top;
}StackType;

void init_stack(StackType* s)
{
	s->size = 0;
	s->top = NULL;
}

void push(StackType* s, int v)
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (s->size == 0)
	{
		newNode->link = NULL;
	}
	newNode->link = s->top;
	newNode->v = v;
	s->top = newNode;

	s->size++;
}

int pop(StackType* s)
{
	if (s->size == 0)
		return -1;
	int res = s->top->v;
	StackNode* temp = s->top;
	s->top = s->top->link;
	free(temp);
	s->size--;
	return res;
}


void init_listT(GraphType* g)
{
	int i = 0;
	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		g->adj_list[i] = NULL;
}

void insert_vertex_listT(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge_listT(GraphType* g, int start, int end)	//start end 는 인덱스이므로 graphtype의 n을 넘기면 없는 인덱스에 접근한다는것
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


int topo_sort(GraphType* g)										//위상정렬은 단방향그래프에서 사용되는것으로, 순서를 위배하지 않고
{																//정렬하는것이 목적임, 계층에 맞게 출력하면 됨
	int i;
	StackType s;
	GraphNode* node;

	int* in_degree = (int*)malloc(g->n * sizeof(int));		//모든 정점의 내차수을(연결이 들어오는 수) 나타내는 포인터
	for (i = 0; i < g->n; i++)
		in_degree[i] = 0;									// 차수 초기화
	for (i = 0; i < g->n; i++)
	{
		GraphNode* node = g->adj_list[i];					// 그래프 i정점의 인접리스트를 while로 돌려서
		while (node != NULL)								// 인접해있는 모든 정점들의 내차수를 올린다.
		{
			in_degree[node->vertex]++;						// 
			node = node->link;
		}
	}

	init_stack(&s);
	
	for (i = 0; i < g->n; i++)
	{
		if (in_degree[i] == 0)						//만약 내차수가 없는 정점이라면 지워도 되므로 스택에저장
			push(&s, i);
	}
	while (s.size != 0)								//스택에 무언가 있다면
	{
		int w;
		w = pop(&s);								//스택에서 내차수가 없는 정점을 빼내고, 출력함
		printf("정점 %d->", w);
		node = g->adj_list[w];						//내차수가 없는 정점의 인접리스트에 접근하여
		while (node != NULL)
		{
			int u = node->vertex;					//인접리스트 들의 차수가 줄어들게 된다. (방금 앞에있는녀석이 사라졌기 때문)
			in_degree[u]--;

			if (in_degree[u] == 0)					//내차수를 뺐는데 0이 되면 이제 그녀석도 스택에 넣어준다.
				push(&s, u);
			node = node->link;						//반복
		}
	}
	free(in_degree);
	printf("\n");
	return (i == g->n);
}

/*
void main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init_listT(g);
	
	insert_vertex_listT(g,0);
	insert_vertex_listT(g,1);
	insert_vertex_listT(g,2);
	insert_vertex_listT(g,3);
	insert_vertex_listT(g,4);
	insert_vertex_listT(g,5);

	insert_edge_listT(g,0,2);
	insert_edge_listT(g,0,3);
	insert_edge_listT(g,1,3);
	insert_edge_listT(g,1,4);
	insert_edge_listT(g,2,3);
	insert_edge_listT(g,2,5);
	insert_edge_listT(g,3,5);
	insert_edge_listT(g,4,5);
	topo_sort(g);

	free(g);
	return 0;
}

*/