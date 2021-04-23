
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int elementA;

typedef struct ArrayListTypeA 
{
	elementA array[MAX_LIST_SIZE];			// 배열의 크기가 정해져있는 리스트임
	int size;
}ArrayListTypeA;

void errorA(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void initA(ArrayListTypeA* L)
{
	L->size = 0;					// 초기화 시 사이즈는 0
}

int is_emptyA(ArrayListTypeA* L)
{
	return L->size == 0;			// 비었는지 확인하는 함수
}

int is_fullA(ArrayListTypeA* L)
{
	return L->size == MAX_LIST_SIZE;		//꽉 찼는지 확인하는 함수
}

elementA get_entryA(ArrayListTypeA* L, int pos)
{
	if (pos < 0 || pos >= L->size)				//해당 인덱스의 요소를 반환
		errorA("위치 오류");
	return L->array[pos];
}

void print_listA(ArrayListTypeA* L)
{
	int i;
	for (i = 0; i < L->size; i++)				// 모든 요소들을 출력
		printf("%d->", L->array[i]);
	printf("\n");
}

void insert_lastA(ArrayListTypeA* L, elementA item)
{
	if (L->size >= MAX_LIST_SIZE)				// 사이즈가 최대치가 아니라면,
	{
		errorA("리스트 오버플로우");				// 마지막 요소를 삽입
	}
	L->array[L->size++] = item;					// 사이즈에 해당하는 부분에 요소를 넣고 더해야 함 인덱스0에 있으면 사이즈1로 뜨니,
}												// 다음에 넣게되면 인덱스1에 넣고, 요소 개수는 2개가 되는것임 

void insertA(ArrayListTypeA* L, int pos, elementA item)
{
	if (!is_fullA(L) && (pos >= 0) && (pos <= L->size))	// 리스트가 꽉 차지 않고, 인덱스 값이 사이즈 범위 안에 있다면
	{
		for (int i = (L->size - 1); i >= pos; i--)		//마지막 요소부터 pos까지 한칸씩 뒤로 옮긴다.		
			L->array[i + 1] = L->array[i];				
		L->array[pos] = item;							// 마지막으로 pos에 값을 넣음
		L->size++;										// 사이즈 +1
	}
}

elementA deleteA(ArrayListTypeA* L, int pos)
{
	elementA item;
	if (pos < 0 || pos >= L->size)
		errorA("위치 오류");
	item = L->array[pos];								// 지우기전에 저장
	for (int i = pos; i < (L->size - 1); i++)			// pos부터 size-1까지 한칸씩 앞으로 당겨온다. 
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}

/*
int main()
{
	ArrayListTypeA list;
	
	init(&list);
	insert(&list, 0, 10);
	print_list(&list);
	insert(&list, 0, 20);
	print_list(&list);
	insert(&list, 0, 30);
	print_list(&list);
	insert_last(&list, 40);
	insert(&list, 2, 3);
	print_list(&list);

	delete(&list, 0);
	print_list(&list);
	return 0;

}
*/