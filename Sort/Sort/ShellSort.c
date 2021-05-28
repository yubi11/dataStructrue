
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void inc_insertion_sort(int list[],int first, int last, int gap)
{
	int i, j, key;
	for (i = first+gap; i <= last; i=i+gap) 
	{
		key = list[i];		// 뒤에있는 수 저장
		for (j = i - gap; j >= first && list[j] > key; j=j-gap)
			list[j + gap] = list[j]; //첫번째요소와 뒤에있는 수 비교후, 첫번째 요소가 값이 더 크면 교체
		list[j + gap] = key;
	}

}

void shell_sort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			gap++;				//gap을 요소개수에서 2로나누고, 짝수면 1을 더해 홀수로만듬
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap); // 리스트, 반복횟수, 마지막요소인덱스, gap을 넣음

		printf("%d번째 회차", i);
		for (int k = 0; k < n; k++)			//회차마다 출력하기
			printf("%d ", list[k]);
		printf("\n");
	}
}

// 쉘정렬은 삽입정렬을 사용하게 된다.
// 삽입정렬은 어느정도 정렬된 리스트에서 상당히 빠른데,
// 삽입정렬은 요소들이 이웃한 위치로만 이동하여, 많은 이동에 의해 요소가 제자리로 돌아간다.
// 요소들이 멀리 떨어진 위치로 이동할 수 있으면 적게 이동하지 않을까? 라는 생각에서 착안한 것이 쉘정렬

// 쉘정렬은 전체 리스트를 일정 간격의 부분리스트로 나누고 각각의 부분리스트를 삽입정렬하도록 되어있다. 
// 예를들어, 다음인덱스를 n칸앞으로 설정하고 비교하는 방법임
// 5칸 삽입정렬, 3칸 삽입정렬, 1칸 삽입정렬 - 이런식으로 정렬하는 것을 쉘정렬이라함 
// 적은위치이동으로 제자리를 찾을 가능성이 크다.
// 시간복잡도는 최악의 경우 O(n^2)이고 평균적으로 O(n^1.5)이다 


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


	shell_sort(list, n);
	for (i = 0; i < n; i++)
		printf("%d ",list[i]);
	printf("\n");
	return 0;
}
*/
