// Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int sorted[20];

void sort_three(int* l,int* m,int* r)
{
	int temp;
	if (*l > *m)
		SWAP(*l, *m,temp);
	if (*m > *r)
		SWAP(*m, *r, temp);
	if (*l > *m)
		SWAP(*l, *m, temp);
}

int partition(int list[], int left, int right)
{
	

	int pivot, temp;
	int low, high;

	low = left;			//왼쪽순회
	high = right + 1;	// 오른쪽순회 +1인 이유는 처음시작하자마자 --될것이기 때문
	pivot = list[left];	// 피벗, 맨 왼쪽값으로 설정될 것임
	
	do 
	{
		do
			low++;		//시작하자마자 low가 늘어나고 왼쪽요소에서 바로 오른쪽에있는 값을 피벗이랑 비교하게됨
		while (low <= right && list[low] < pivot); //피벗보다 작고, 오른쪽끝 인덱스까지 도달하지못하면 반복
			
		do
			high--;		// low순회가 끝나고 high를 순회하기 시작함
		while (high >= left && list[high] > pivot); // high가 피벗보다 크고, 왼쪽끝까지 도달하지 못하면 반복 
		
		if (low < high)		// 둘 다 조건을 충족 못해 멈춰있을 때, low와 high간 트레이드가 일어남 
			SWAP(list[low], list[high], temp);

	} while (low < high);	// 이를 계속해서 반복하다보면, low가 high보다 커지는 때가 옴,

	SWAP(list[left], list[high], temp);	// 그 때 high의 인덱스에있는 요소와 맨왼쪽값을 바꿔줌
	return high;	// 그리고 그 high를 새로운 기준값으로 반환해줌
}


void quick_sort(int list[], int left, int right)
{
	
	if (left < right)
	{
		int q = partition(list, left, right);	// 처음 파티션을 나누고 그 기준을 얻어서 그값으로 다시 순환호출 돌림
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// 평균적으로 가장 빠른 정렬방법

// 이 또한 분할정복법을 사용하는데, 분할정렬과는 달리 비균등하게 분할한다.
// 피벗을 나누어서 피벗보다 작은값 큰 값을 분할함


// 최선의경우( 거의 균등한 리스트로 분할되는경우)
// 패스의 수가 log(n) (트리의 높이)이 되기 때문이다.
// 패스 안에서 비교는 n번 일어남
// 그래서 비교횟수는 n*log(n)
// 이동횟수는 비교횟수보다 적기에 무시 가능할 정도

//반면 최악의 경우, 극도로 불균등한 리스트로 분할되는경우
// 패스의 수는 n이 되며 각 패스 안에서의 비교횟수는 n이되어 총 비교횟수는 n^2이 된다.
// 이동횟수는 무시가 가능하다.
// 예를들어 이미 정렬된 리스트를 정렬할경우 
// 피벗이 최저 값으로 정해지게되는데, 그 때 n^2의 시간복잡도를 가지게된다.

// 이를 피하기 위해선 중간값을 피벗으로 선택하면 불균등 분할을 완화할 수 있다.

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


	quick_sort(list, 0, n-1);

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}
*/
