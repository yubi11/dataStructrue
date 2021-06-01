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
	int weight[MAX_VERTICES][MAX_VERTICES];		//다익스트라는 정점행렬을 이용해서 가중치를 표시함
}GraphTypeP;

int distance[MAX_VERTICES];						//거리
int found[MAX_VERTICES];						// 

int choose(int distance[], int n, int found[])	// choose함수는 지금까지 업데이트한 정점리스트와 거리리스트들을 받는다.
{															
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)			//n번반복
		if (distance[i] < min && !found[i])	// 아직 업데이트 되지 않은 정점이 있다면
		{									// 그 중에서 가장 낮은 거리비용을 가지고 있는 인덱스를 찾고 반환한다.
			min = distance[i];				// 이 부분이 만약 완전이진탐색으로 구현이 되면 다익스트라는 O(nlogn)의 시간복잡도를 가질 수 있게 된다.
			minpos = i;
		}
	return minpos;
}

void dijkstra(GraphTypeP* g, int start)		//일반적으로는 O(nlogn)이나 여기선 시간복잡도 O(n^2)임, 모든 정점에 대해서 탐색을 하고, 업데이트를 하기때문
{
	int i, u, w,j;
	for (i = 0; i < g->n; i++)			 
	{
		distance[i] = g->weight[start][i];		// 시작점기준으로부터 거리를 정하게 됨
		found[i] = false;						// 가지않은 경로는 false로 설정
	}
	found[start] = true;						// 처음 자신위치는 true와 거리 0으로 설정해줌 
	distance[start] = 0;						

	for (i = 0; i < g->n - 1; i++)				//O(n^2)
	{											// 
		printf("distance :");
		for (j = 0; j < g->n; j++)
		{
			printf("%d ", distance[j] == INF ? -1 : distance[j]);	//정점 입장에서 각 정점들에 대한 거리를 표시한다.
		}
		printf("\n");
		printf("found    :");
		for (j = 0; j < g->n; j++)
		{
			printf("%d ", found[j]);			// 아직 업데이트를 하지 않은 정점들에 대해선 0을 표시하도록 출력한다.
		}
		printf("\n");

		u = choose(distance, g->n, found);		// min distance를 찾을 때 이진탐색을 할경우 log n으로 줄기 때문에, O(nlogn)까지 갈 수 있음
		found[u] = true;						// 가장 비용이 낮은 부분을 찾고 이를 중점으로 업데이트를한다.
		for (w = 0; w < g->n; w++)				// 이 부분에서는 업데이트가 안 된 정점을 찾고,
			if (!found[w])						// 가장 비용이 낮은 부분의 거리 + 업데이트가 안된 정점의 비용 < 업데이트가 안된 정점의 거리 일 시,
				if (distance[u] + g->weight[u][w] < distance[w])	// 업데이트가 안된 정점의 거리 = 가장 비용이 낮은 정점의 거리+ 업데이트가 안된 정점의 비용
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