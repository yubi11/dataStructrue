#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t)((t)=(x), (x)=(y), (y)=(t))

void BubbleSort(int list[], int n)
{
	int i, j, temp;
	for (i =n-1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}


		printf("%d번째 회차", i);
		for (int k = 0; k < n; k++)			//회차마다 출력하기
			printf("%d ", list[k]);
		printf("\n");
	}

}


// 비교횟수는 최상,평균,최악 항상 O(n^2)임
// 역순으로 정렬된 최악의 경우 3*비교횟수이며
// 이미 정렬된 경우 이동횟수는 0
// 평균의 경우는 O(n^2)이다


/*
int main()
{
	int i;
	int n = 20;
	int list[20];

	srand(time(NULL));
	for (i = 0; i < n; i++)
		list[i] = rand() % 100;

	BubbleSort(list, n);
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;

}

*/