#include <stdio.h>
#define MAX_ELEMENT 200

//우선순위를 가진 데이터를 저장하는 큐, FIFO가 아니고 우선순위가 높은 데이터가 먼저나감
// 우선순위 큐는, 최소 우선순위 큐, 최대 우선순위 큐로 나뉨
// 구현 방법에는 배열, 연결리스트, 힙이 있음
// 무조건 힙을 씀, 시간복잡도가 압도적으로 좋음

//힙은 완전이진 트리
//노드의 부모노드가 자식노드보다 값이 큰 완전이진트리를 최대큐 max queue
//노드의 부모노드가 자식노드보다 값이 작은 완전이진트리를 최소큐 min queue

// 힙의 높이는 log2 n, 히프는 완전이진트리이며 마지막 레벨 h를 제외하곤 각 레벨에 2^i-1개의 노드가 존재한다. ex)1층 1개 2층 2개 3층 4개 

// 완전이진트리는 번호를 매길 수 있는데, 레벨오더의 순서로 매겨짐


//힙 구현방법
//힙은 배열을 이용하여 구현함, 완전이진트리이므로 각 노드에 번호를 붙일 수 있음,
// 배열인덱스를 이용할 수 있으므로, 부모노드 기준으로 왼쪽자식은 2*부모인덱스 오른쪽자식은 2*부모인덱스+1로 접근가능, 자식입장에선 자식인덱스/2로 접근 

// 힙의 삽입 방법
// 새로운요소를 마지막 노드에 삽입 후, 부모노드들과 비교하고 자리를 교체함
// 힙의 사이즈를 늘리고 마지막 노드에 삽입후, 부모노드들과 비교하고 자리교체 하는 upheap 수행

typedef struct
{
	int key;
}element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType heap;

void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}


int main()
{
	

	return 0;
}
