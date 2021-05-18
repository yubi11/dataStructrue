// 그래프내의 모든 정점을 포함하는 트리, n개의 정점을 가지는 그래프의 신장트리는 n-1개의 간선을 가진다.
// ABC 정점을 다 가지고 있지만 환형으로 연결되어 있지는 않은 모양 A->B가 빠져있거나 B->C가 빠지거나 C->A가 빠지는 것이 예시
// ABCD가 있으면 A->B->C->D만 연결되어있음

//신장트리는 비용상관없이 한 경로로 끝 정점까지 갈수 있는 트리
//dfs로 구할 수 있음

//최소비용 신장트리 minimum spanning tree MST
//정점끼리 이동하는 것에 비용이 있다면, 모든 정점을 연결하고 비용을 최소화 하는 것이 최소비용 신장트리

// 비용이 낮은 간선 순으로 하나씩 탐색해가며 경로집합에 넣어주게된다.
// 경로집합이 싸이클을 이루게 만드는 경로는 제외를 하게된다.


//union-find알고리즘 
//MST는 싸이클을 이루는지를 확인할 알고리즘이 필요하다 -> union-find 알고리즘
//연결정점들을 차례대로 보면서 두 정점이 나중에 같은 정점에 연결되어있는경우 사이클이 됨
// ABCDEFGHIJ 노드가 있다고 가정하고, 루트노드값에는 -1이라는 값을 가짐
// 만약 A와 B가 연결되어있다면, B의 루트노드는 A의 인덱스(0) 값을 가지게 됨
// 만약 C와 H가 연결되어있다면, H는 루트노드는 C의 인덱스(2) 값을 가지게 됨

// 루트노드를 찾을 때는, 값이 -1이 나오는 노드를 찾으면 됨, 
// 만약 찾는 노드의 값이 -1일 시, 해당 노드의 인덱스가 결과로 나옴
// 두 노드의 루트노드가 같지 않다면, 두 루트노드중 하나를 다른 한 노드의 루트노드로 설정해준다.
// 즉, A-B , C-H 연결이 있고, B,H를 UNION함수에 넣으면  A-B-H-C 연결이 됨
// 이 상황에서 A와 C를 UNION함수에 넣으면 a의 부모노드, c의 부모노드가 0으로 같기 때문에 사이클이라고 판단되어 이어지지않는다.

#define MAX_VERTICES 50

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 100

int parent[MAX_VERTICES];

struct Edge 
{
	int start, end, weight;
};

typedef struct GraphType 
{
	int n;
	struct Edge edges[(MAX_VERTICES * (MAX_VERTICES-1))/2];
}GraphType;

void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

void set_union(int a, int b)
{
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)
		parent[root1] = root2;
}

void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < (MAX_VERTICES * (MAX_VERTICES - 1)) / 2; i++)
	{
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge_kruskal(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort에 사용
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

void kruskal(GraphType* g)		//kruskal mst 알고리즘의 시간복잡도는 O(e*log(e))가 된다.(퀵정렬)
{								// 최대 e개만큼 간선을 검사하고, 사이클 검사를 하는데, 사이클검사는 조상검사이며,
								// 매우 신속하게 가능함. 간선을 정렬하는데 걸리는 시간에 의해 시간복잡도가 좌우된다.
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->n); //정점 개수만큼 Union-find용 인덱스 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare); //정렬할배열, 요소개수 ,요소크기, 비교함수(비용 오름차순)
	printf("크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;
	while (edge_accepted < (g->n - 1)) //신장트리의 간선개수
	{
		e = g->edges[i];			//간선 찾기
		uset = set_find(e.start);	//선택된 간선의 시작노드의 루트노드 찾기
		vset = set_find(e.end);		//선택된 간선의 끝노드의 루트노드 찾기
		if (uset != vset)			//루트노드가 같지 않다면 (싸이클이 만들어지지 않음)
		{
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;		//신장트리 간선개수 축적량
			set_union(uset, vset);	//해당 루트노드들을 합쳐줌
		}
		i++; //모든 정점을 


	}


}

/*
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge_kruskal(g, 0, 1, 29);
	insert_edge_kruskal(g, 1, 2, 16);
	insert_edge_kruskal(g, 2, 3, 12);
	insert_edge_kruskal(g, 3, 4, 22);
	insert_edge_kruskal(g, 4, 5, 27);
	insert_edge_kruskal(g, 5, 0, 10);
	insert_edge_kruskal(g, 6, 1, 15);
	insert_edge_kruskal(g, 6, 3, 18);
	insert_edge_kruskal(g, 6, 4, 25);
	kruskal(g);
	free(g);
	return 0;

}
*/