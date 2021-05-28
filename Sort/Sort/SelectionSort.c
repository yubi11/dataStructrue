// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++)
	{
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);

		printf("%d번째 회차", i);
		for (int k = 0; k < n; k++)			//회차마다 출력하기
			printf("%d ", list[k]);
		printf("\n");
	}
}

//안정적이지않음 ,비교횟수 O(n^2)임, 이동횟수는 3(n-1), O(n)
// 전체 시간적 복잡도는 O(n^2)임

/*
int main()
{
	int i;
	int n = 20;
	int list[20];

	srand(time(NULL));
	for (i = 0; i < n; i++)
		list[i] = rand() % 100;

	printf("정렬전: ");
	for (int k = 0; k < n; k++)			//회차마다 출력하기
		printf("%d ", list[k]);
	printf("\n");


	selection_sort(list, n);
	for (i = 0; i < n; i++)
		printf("%d ",list[i]);
	printf("\n");
	return 0;
}
*/
