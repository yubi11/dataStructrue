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
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphTypeF;

int A[MAX_VERTICES][MAX_VERTICES];

int distance_f[MAX_VERTICES];
int found_f[MAX_VERTICES];

void floyd(GraphTypeF* g, int start)		//floyd경우 O(n^3)의 시간복잡도를 가진다.
{													
	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j];
	
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			printf("%d ", A[i][j]==INF?-1:A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (k = 0; k < g->n; k++)
	{
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];

			
		for (i = 0; i < g->n; i++)
		{
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