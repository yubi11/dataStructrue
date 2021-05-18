// 시작 정점으로부터 출발하여 신장트리 집합을 단계적으로 확장함
// 신장트리집합에 인접한 정점 중에서 최저간선으로 연결된 정점을 선택하게됨

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphTypePrim {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphTypePrim;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;
	return v;
}

void prim(GraphTypePrim* g, int s)		//prim MST 알고리즘의 시간복잡도 O(n^2), 주반복문이 정점의 수 n만큼 반복, 내부반복문이 n번 반복
{										//sparse graph에 대해서는 kruskal (간선에 대해서)
	int i, u, v;						//dense graph에서는 prim이 유리하다 (정점에 대해서)
	for (u = 0; u < g->n; u++)			
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++)
	{
		u = get_min_vertex(g->n);
		selected[u] = true;
		if (distance[u] == INF)
			return;
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
	}
}
/*
int main(void)
{
	GraphTypePrim g = { 7,
	{{0,29,INF,INF,INF,10,INF},
	{29,0,16,INF,INF,INF,15},
	{INF,16,0,12,INF,INF,INF},
	{INF,INF,12,0,22,INF,18},
	{INF,INF,INF,22,0,27,25},
	{10,INF,INF,INF,27,0,INF},
	{INF,15,INF,18,25,INF,0}}
	};
	prim(&g, 0);
	return 0;
}
*/