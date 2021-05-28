#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int list[],int n)
{
	int i,j,key;
	for (i = 1; i < n; i++)
	{
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];
		list[j + 1] = key;

		printf("%d번째 회차", i);
		for (int k=0; k < n; k++)			//회차마다 출력하기
			printf("%d ", list[k]);
		printf("\n");
	}

}


// 대부분 정렬되어있으면 효율적임, 최선의 경우 비교횟수 O(n)까지 나옴,
// 레코드가 클 경우 불리하다. 안정적이다(키값이 같아도 순서 안바뀜)
// 최악의 경우 비교 횟수 O(n^2) 이동횟수 O(n^2)이 나온다. 



/*
int main()
{
	int i;
	int n = 20;
	int list[20];

	srand(time(NULL));
	for (i = 0; i < n; i++)
		list[i] = rand() % 100;

	InsertionSort(list, n);
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;

}
*/