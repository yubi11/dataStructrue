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


typedef struct
{
	int key;
}element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}


void insert_max_heap(HeapType* h, element item)
{
	int i;													// 힙의 삽입 방법 (up heap)
															// 새로운요소를 마지막 노드에 삽입 후, 부모노드들과 비교하고 자리를 교체함
															// 힙의 사이즈를 늘리고 마지막 노드에 삽입후, 부모노드들과 비교하고 자리교체 하는 upheap 수행
	i = ++(h->heap_size);
	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{											// 만약 현재 들어오는 노드와 그 노드의 부모 키를 비교 후,
		h->heap[i] = h->heap[i / 2];			// 현재 들어오는 노드가 부모보다 크면 부모를 현재 들어오는 노드위치에 놓는다.
		i /= 2;									// 마치 부모가 한칸 내려오는것 처럼,
												// 만약 들어오는 친구가 정말 큰값이라면 부모가 계속해서 한칸씩 내려오게 됨 
	}	
	h->heap[i] = item;			//그리고 마지막에 한번씩 밑으로 다 밀렸으니 부모 값은 자식이 차지하면 됨
}

//힙의 삭제는 가장 큰 키 값을 가진 노드를 삭제하는 것을 의미한다.
//루트노드는 삭제되고 말단노드가 루트노드로 올라가며, 자식노드들과 대결하며 점점 제자리를 찾아가도록 구현해야한다.

element delete_max_heap(HeapType* h)
{												//루트에 제일 작은값을 넣고, 하나씩 내려보낼 예정임
	int parent, child;						
	element item, temp;

	item = h->heap[1];					//루트노드의 값
	temp = h->heap[(h->heap_size)--];	//마지막노드를 가져오고 사이즈를 줄임
	parent = 1;					//루트노드인덱스
	child = 2;					//자식노드인덱스
	while (child <= h->heap_size)		// 자식노드인덱스가 힙의 사이즈보다 작다면 계속 반복됨 
	{									// 힙사이즈가 만약 자식인덱스보다 낮다면, 더 이상 순회할 자식이없으므로

		if ((child < h->heap_size) && h->heap[child].key < h->heap[child + 1].key)	// 자식이 힙사이즈보다 작고, 왼자식노드가 오른자식노드보다 작으면
			child++;						//왼쪽 자식 or 오른쪽 자식으로 내려갈지 정해짐

		if (temp.key >= h->heap[child].key) //마지막노드값이 지금정해진 자식노드의 값보다 크거나 같다면
			break;							//바로 끝내고 정해진 루트노드에 마지막노드를 넣어준다.

		h->heap[parent] = h->heap[child];	//그게 아니라면 부모노드에 자식노드를 넣게된다. 자식노드는 *2를 하여 한 단계를 내림 (다운힙)
		parent = child;						//부모노드는 자식노드인덱스를 가리키게됨
		child *= 2;							// 부모인덱스, 자식인덱스 모두 한 층씩 내려간다 보면 됨
	}
									//=> 부모기준 왼쪽자식과 오른쪽자식 중 더 큰 쪽을 찾고, 큰 쪽을 택해서 그쪽으로 내려가게 됨
									// 	방금 정한 자식노드의 값과 마지막노드(값이 가장낮은)와 비교하게 됨,
									//	비교한 그 값이 같거나, 마지막노드가 크면 바로 반복문을 종료하고,
									//	부모에다가 바로 마지막노드를 넣는다.

	h->heap[parent] = temp;				//즉, 요약하자면, 부모와 자식 간, 왼자식이 더큰지 오른자식이 더 큰지 결정 후, 
	return item;						//말단노드가 그 자식보다 크다면 바로 부모노드에 말단노드를 넣고
}										//아니라면, 부모노드를 자식노드로 바꾸고, 자식노드의 자식을 가지고 위 과정을 한번 더 거치는 것임.



//힙정렬
										//힙을 이용하면 정렬이 가능한데, 정렬 할 n개의 요소를 최대힙에 넣게되면
										//삽입연산, 삭제연산을 통해서 내부적으로 정렬이 된 힙이 만들어지게 된다.
										//이때 n개의 요소를 넣으니 O(nlog n)의 시간복잡도를 가지게 된다.
void heap_sort(element a[], int n)
{
	int i;
	HeapType* h;
	h = create();
	init(h);							//내부적으로 힙 초기화

	for (i = 0; i < n; i++)
	{
		insert_max_heap(h, a[i]);		//매개변수로 받은 모든 정수를 heap에 삽입함
	}

	for (i = (n - 1); i >= 0; i--)		// n방향만 바꿔도 내림차순으로 바뀜
	{
		a[i] = delete_max_heap(h);		//a[i]에 정렬된 힙에서 1개씩 빼내줌 (부모 노드는 최대힙이므로 최대값이 차례로 나오게 됨)
	}
	free(h);
}


void print_all(HeapType* h)
{
	for (int i = 1; i < h->heap_size+1; i++)
		printf("%d\n", h->heap[i]);
}


/*
int main()
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };		// 삽입연산에서 최악의경우, 루트 노드까지 올라가야 한다. O(log n)
	element e4, e5, e6;									// 삭제연산에서는 최악의경우, 루트 마지막까지 내려가는 것. O(log n)
	HeapType* heap;										// => 트리노드의 높이만큼 시간이 걸림
	heap = create();
	init(heap);

	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	print_all(heap);

	e4 = delete_max_heap(heap);
	printf("<%d>", e4.key);
	e5 = delete_max_heap(heap);
	printf("<%d>", e5.key);
	e6 = delete_max_heap(heap);
	printf("<%d>", e6.key);

	element list[8] = { 23,56,11,9,56,99,27,34 };
	heap_sort(list, 8);
	for (int i = 0; i < 8; i++)
	{
		printf("%d,", list[i].key);
	}

	free(heap);
	return 0;
}
*/
