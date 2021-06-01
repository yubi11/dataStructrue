// 시작 정점으로부터 출발하여 신장트리 집합을 단계적으로 확장함
// 신장트리집합에 인접한 정점 중에서 최저간선으로 연결된 정점을 선택하게됨

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000

//kruskal 에 비해 prim은 시작정점에서 출발해서 신장트리 집합을 확장해나간다. 

typedef struct GraphTypePrim {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];		//kruskal은 가중치 간선을 사용한 반면, 
}GraphTypePrim;									//prim은 정점 행렬을 사용해 가중치를 표현할 것 이다.

int selected[MAX_VERTICES];		//
int distance[MAX_VERTICES];		//

int get_min_vertex(int n)	//가장 비용이 적은 값을 갖는 정점을 반환시키는 함수이다.
{
	int v, i;
	for (i = 0; i < n; i++) 
	{
		if (!selected[i])		//방문하지 않은 정점을 찾을 것임,
		{
			v = i;				//방문하지않은 정점 v를 찾아냄
			break;
		}
	}
	for (i = 0; i < n; i++)		// 방금 찾아낸 v와 중복되지 않는 방문하지 않은 다른 정점 i를 찾아내서, 거리를 비교함
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;				//i와 v중 더 가까운 정점을 반환 할 것임
	return v;
}

void prim(GraphTypePrim* g, int s)		//prim MST 알고리즘의 시간복잡도 O(n^2), 주반복문이 정점의 수 n만큼 반복, 내부반복문이 n번 반복
{										//sparse graph에 대해서는 kruskal (간선에 대해서)
	int i, u, v;						//dense graph에서는 prim이 유리하다 (정점에 대해서)
	for (u = 0; u < g->n; u++)			
		distance[u] = INF;				//초기에 모든 정점의 비용을 초기화시켜준다.
	distance[s] = 0;					//지금 선택된 정점에서 시작할것이므로, 지금 정점은 거리가 0 이다.

	for (i = 0; i < g->n; i++)			//정점개수만큼 반복함
	{
		u = get_min_vertex(g->n);		//최단거리를 찾을 것이다. (처음시도하면 시작 정점이 나옴)
		selected[u] = true;				//최단거리정점을 방문했다고 체크함
		if (distance[u] == INF)			//만약 최단거리 정점이 없어서 INF면 더 이상 연결못하니 return해야한다.
			return;
		printf("정점 %d 추가\n", u);		//선택된 정점을 추가하고, 정점개수만큼, 선택된 정점에서 인접한 정점을 찾는다.
		for (v = 0; v < g->n; v++)		
			if (g->weight[u][v] != INF)	//찾는데 성공하면, 그 찾은 정점의 방문여부와, 거리가 업데이트 되어있는지 확인한다.
				if (!selected[v] && g->weight[u][v] < distance[v])					// 거리가 비용보다 큰 경우는 업데이트가 안된경우
					distance[v] = g->weight[u][v];			//매 정점마다 인접정점의 거리를 가중치로 업데이트함
	}														// 매 for마다 초기화되므로, 각 정점 당 n번만큼 업데이트함
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