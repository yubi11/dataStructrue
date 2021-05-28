// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int sorted[20];

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;	// i ~ mid , j ~ right로 쪼갤 예정

	while (i <= mid && j <= right)	//왼쪽분할과 오른쪽분할의 요소들을 각각의 오른쪽요소를 넘지않을때까지 비교해줄 것임
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];	// 작은것을 sorted에 넣고 왼쪽에서 온 요소라면 i를 증가시킴
		else
			sorted[k++] = list[j++];	// 오른쪽은 j
	}								// i나 j 즉, 왼쪽 오른쪽 중 한 요소가 먼저 이미 다 정렬되었다면

	if (i > mid)					// 아직남아있는 쪽의 요소를 한번에 다 넣게 된다.
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left; l <= right; l++)	// sorted에 정렬이 다 되어있으니 이것을 list에 다시 담아줌
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;		//받은 왼쪽인덱스, 오른쪽인덱스를 나눌 기준
		merge_sort(list, left, mid);	// 쪼개진 왼쪽을 기준을두고 계속 쪼개서 1:1관계르 이루게함,
		merge_sort(list, mid + 1, right); // 오른쪽도 마찬가지
		merge(list, left, mid, right); // 1:1까지 쪼개진 것을 합병 정렬하게함
	
	}

}


// 크기 n인 리스트를 균등 분배하므로 log n번의 패스(분할)이 일어나고,
// 각 패스에서 리스트의 모든 레코드를 n개 비교하므로 n log n번의 비교연산을 한다.

// 이동횟수는 각 패스에서 2n번 발생하므로 전체 레코드 이동은 2n*log(n)번 발생한다
// 합병정렬은 리스트를 분할한 후, 리스트를 정렬하는 방법이다.
// Divde, conquer, combine 이라 하여, 분할 ,정복 ,결합의 단계로 이루어져 있다.

// 시간복잡도 평균,최적,최악 O(n*log(n))을 가진다.
// 또한 안정적이며 데이터의 초기 분산 순서에 영향을 덜받는다.

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


	merge_sort(list, 0,n-1);

	for (i = 0; i < n; i++)
		printf("%d ",list[i]);
	printf("\n");
	return 0;
}
*/
