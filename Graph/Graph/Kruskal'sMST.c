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

int parent[MAX_VERTICES];			// parent로 사이클을 확인 할 것임

struct Edge 
{
	int start, end, weight;			// 최소비용신장트리이므로, 간선에 가중치가 있어야함
};

typedef struct GraphType 
{
	int n;
	struct Edge edges[(MAX_VERTICES * (MAX_VERTICES-1))/2];		//간선의 개수는 최대개수로 설정 n* (n-1) /2
}GraphType;

void set_init(int n)
{
	for (int i = 0; i < n; i++)		// parent를 -1로 초기화
		parent[i] = -1;
}

int set_find(int curr)			// 매개변수가 현재 어디에 속하는지 반환해주는 함수이다. 
{
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

void set_union(int a, int b)	// 두개의 원소가 속한 집합을 합친다.
{
	int root1 = set_find(a);	// 노드 a가 어디에 속하는지,
	int root2 = set_find(b);	// 노드 b가 어디에 속하는지,
	if (root1 != root2)
		parent[root1] = root2;	// 만약 소속이 같지 않다면, 노드 a가 노드 b에 속하게 된다.
}

void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < (MAX_VERTICES * (MAX_VERTICES - 1)) / 2; i++)
	{
		g->edges[i].start = 0;				// 가중치그래프를 초기화하는 과정이다.
		g->edges[i].end = 0;				// start는 시작정점 end는 끝정점 이라 생각하면 되고 weight는 비용이라 보면된다.
		g->edges[i].weight = INF;
	}
}

void insert_edge_kruskal(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;			// 가중치 간선을 그래프에 포함시키는 부분이다.
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort에 사용
int compare(const void* a, const void* b)		//퀵소트에서 사용할 compare 함수
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

	set_init(g->n);		//간선 개수만큼 Union-find용 인덱스 초기화


	qsort(g->edges, g->n, sizeof(struct Edge), compare); //정렬할배열, 요소개수 ,요소크기, 비교함수(비용 오름차순)
														//그래프 내의 간선을 가중치 순으로 정렬 한 것이다.
														// O(e*log(e))이다. 여기서 g->n은 간선의 개수를 의미하므로
											

	printf("크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;

										// 퀵정렬이 while문 보다 더 느리므로 O(e*log(e))가 됨 
										//while문 자체는 시간복잡도 e에 달함

	while (edge_accepted < (g->n - 1)) //최소비용 신장트리의 간선개수에 달하면 종료하게된다.
	{
		e = g->edges[i];			// 그래프내의 i번째 간선을 택하고,

		uset = set_find(e.start);	// i번째 간선의 시작정점의 루트노드 찾기
		vset = set_find(e.end);		// i번째 간선의 끝정점의 루트노드 찾기
									// 즉 i번째 간선이 이어져 있는 부분이 선택된 것이다.

		if (uset != vset)			// 만약, 간선의 시작정점과 끝정점의 소속이 다르다면,
		{
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);		//간선 이 선택되었다는 문구를 출력하고
			edge_accepted++;		// 신장트리의 간선개수를 늘린다 -> n-1까지 늘 예정임
			set_union(uset, vset);	// 선택된 간선의 정점들을 set_union으로 합치면 uset이 vset에 소속될 것 이다.
		}
		i++; //한 루틴을 돌았으니 i를 더해준다. 
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