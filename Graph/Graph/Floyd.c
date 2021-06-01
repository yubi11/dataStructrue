// 모든 정점 사이의 최단경로를 찾는 알고리즘
// 2차원 배열을 이용해 3중반복을 함

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType
{
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];		// 정점 행렬로 가중치 표현
}GraphTypeF;

int A[MAX_VERTICES][MAX_VERTICES];		// 

int distance_f[MAX_VERTICES];			// 거리 배열
int found_f[MAX_VERTICES];				// 업데이트 배열

void floyd(GraphTypeF* g, int start)		//floyd경우 O(n^3)의 시간복잡도를 가진다.
{													
	int i, j, k;
	for (i = 0; i < g->n; i++)		//정점의 개수만큼 처음 가중치를 A에다가 초기화해준다.
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j];
	
	printf("업데이트 전\n");
	for (i = 0; i < g->n; i++)		//초기 업데이트 전
	{
		for (j = 0; j < g->n; j++)
		{
			printf("%d ", A[i][j]==INF?-1:A[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	for (k = 0; k < g->n; k++)					//핵심부분
	{
		for (i = 0; i < g->n; i++)				
			for (j = 0; j < g->n; j++)				
				if (A[i][k] + A[k][j] < A[i][j])		//업데이트를 하기 위한 조건은, 새로운 값이 현재 거리보다 낮아야 한다는점	
					A[i][j] = A[i][k] + A[k][j];		
													//행렬로치면, 예를들어 새로운값에 해당하는, 0을 거쳐가는 구간의 거리는 업데이트는,
													// i에서 j로가기위한 거리는, A[i][0]+A[0][j]이다.
													// 1로 거치면 A[i][1]+A[1][j], 즉, 이 짓을 n번에 대해서 한다음, 가장 낮은 값이 업데이트됨


		printf("업데이트 %d회\n",k+1);
		for (i = 0; i < g->n; i++)					//플로이드의 결과는 모든정점에서 모든 정점으로 가는 비용을 나타낸다.
		{											//다익스트라는 시작지점을 기준으로 해서 모든 정점으로 가는 비용을 나타낸다.
			for (j = 0; j < g->n; j++)
			{
				printf("%d ", A[i][j] == INF ? -1 : A[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	

}

/*
int main(void)
{
	GraphTypeF g = { 7,
	{{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{INF,4,0,2,INF,INF,INF},
	{INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF},
	{INF,INF,INF,4,5,INF,0},}
	};

	floyd(&g, 0);
	return 0;
}
*/