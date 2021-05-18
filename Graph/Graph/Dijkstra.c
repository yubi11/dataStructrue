// 가중치 인접행렬. 연결을 0,1로 표현하는 것이 아닌, 비용으로 쓴다. 연결되어 있어도 비용값은 다르며, 데칼코마니 형식임(양방향연결)
// 연결되지 않았다면 INF로 표시

// 다익스트라 알고리즘 ,플로이드 알고리즘 두개로 나뉨

// 다익스트라는 1->n까지의 최단경로, 플로이드는 n->n까지의 최단경로 모든 정점에서 다른 모든 정점까지의 최단경로
// 한 시작점부터, 디스턴스 배열에서 비용이 가장 낮게 연결된 정점들을 돌게되면서,최단정점을 저장하면서, 최단경로비용을 디스턴스배열에 업데이트 해놓음(전국일주하면서 거리계산한다고생각)
// 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType 
{
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphTypeP;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)
		if (distance[i] < min && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void dijkstra(GraphTypeP* g, int start)		//일반적으로는 O(nlogn)이나 여기선 시간복잡도 O(n^2)임, 모든 정점에 대해서 탐색을 하고, 업데이트를 하기때문
{
	int i, u, w,j;
	for (i = 0; i < g->n; i++)
	{
		distance[i] = g->weight[start][i];
		found[i] = false;
	}
	found[start] = true;
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++)				//내부반복문 2n에 외부 n번, 즉 2n^2이나 빅오표기법에서는 n^2
	{
		printf("distance :");
		for (j = 0; j < g->n; j++)
		{
			printf("%d ", distance[j] == INF ? -1 : distance[j]);
		}
		printf("\n");
		printf("found    :");
		for (j = 0; j < g->n; j++)
		{
			printf("%d ", found[j]);
		}
		printf("\n");

		u = choose(distance, g->n, found);		// min distance를 찾을 때 이진탐색을 할경우 log n으로 줄기 때문에, O(nlogn)까지 갈 수 있음
		found[u] = true;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
		
	}
}

/*
int main(void)
{
	GraphTypeP g = { 7,
	{{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{INF,4,0,2,INF,INF,INF},
	{INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF},
	{INF,INF,INF,4,5,INF,0},}
	};

	dijkstra(&g, 0);
	return 0;
}
*/