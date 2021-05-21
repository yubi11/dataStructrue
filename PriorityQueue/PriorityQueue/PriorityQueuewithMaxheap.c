#include <stdio.h>
#define MAX_ELEMENT 200

//�켱������ ���� �����͸� �����ϴ� ť, FIFO�� �ƴϰ� �켱������ ���� �����Ͱ� ��������
// �켱���� ť��, �ּ� �켱���� ť, �ִ� �켱���� ť�� ����
// ���� ������� �迭, ���Ḯ��Ʈ, ���� ����
// ������ ���� ��, �ð����⵵�� �е������� ����

//���� �������� Ʈ��
//����� �θ��尡 �ڽĳ�庸�� ���� ū ��������Ʈ���� �ִ�ť max queue
//����� �θ��尡 �ڽĳ�庸�� ���� ���� ��������Ʈ���� �ּ�ť min queue

// ���� ���̴� log2 n, ������ ��������Ʈ���̸� ������ ���� h�� �����ϰ� �� ������ 2^i-1���� ��尡 �����Ѵ�. ex)1�� 1�� 2�� 2�� 3�� 4�� 

// ��������Ʈ���� ��ȣ�� �ű� �� �ִµ�, ���������� ������ �Ű���


//�� �������
//���� �迭�� �̿��Ͽ� ������, ��������Ʈ���̹Ƿ� �� ��忡 ��ȣ�� ���� �� ����,
// �迭�ε����� �̿��� �� �����Ƿ�, �θ��� �������� �����ڽ��� 2*�θ��ε��� �������ڽ��� 2*�θ��ε���+1�� ���ٰ���, �ڽ����忡�� �ڽ��ε���/2�� ���� 


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
	int i;													// ���� ���� ��� (up heap)
															// ���ο��Ҹ� ������ ��忡 ���� ��, �θ����� ���ϰ� �ڸ��� ��ü��
															// ���� ����� �ø��� ������ ��忡 ������, �θ����� ���ϰ� �ڸ���ü �ϴ� upheap ����
	i = ++(h->heap_size);
	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//���� ������ ���� ū Ű ���� ���� ��带 �����ϴ� ���� �ǹ��Ѵ�.
//��Ʈ���� �����ǰ� ���ܳ�尡 ��Ʈ���� �ö󰡸�, �ڽĳ���� ����ϸ� ���� ���ڸ��� ã�ư����� �����ؾ��Ѵ�.

element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];					//��Ʈ����� ��
	temp = h->heap[(h->heap_size)--];	//��������带 �������� ����� ����
	parent = 1;							//��Ʈ����ε���
	child = 2;							//�ڽĳ���ε���
	while (child <= h->heap_size)		// �ڽĳ���ε����� ���� ������� �۴ٸ� ��� �ݺ���
	{
		if ((child < h->heap_size) && h->heap[child].key < h->heap[child + 1].key)	// �ڽ��� ��������� �۰�, ���ڽĳ�尡 �����ڽĳ�庸�� ������
			child++;						//����� �ڽ��� �ٲ���
		if (temp.key >= h->heap[child].key) //��������尪�� ���������� �ڽĳ���� ������ ũ�ٸ�
			break;							//�ٷ� ������ ��Ʈ��忡 ��������带 �־��ش�.
		h->heap[parent] = h->heap[child];	//�װ� �ƴ϶�� �θ��忡 �ڽĳ�带 �ְԵȴ�. �ڽĳ��� *2�� �Ͽ� �� �ܰ踦 ���� (�ٿ���)
		parent = child;						
		child *= 2;
	}
	h->heap[parent] = temp;				//��, ������ڸ�, �θ�� �ڽ� ��, ���ڽ��� ��ū�� �����ڽ��� �� ū�� ���� ��, 
	return item;						//���ܳ�尡 �� �ڽĺ��� ũ�ٸ� �ٷ� �θ��忡 ���ܳ�带 �ְ�
}										//�ƴ϶��, �θ��带 �ڽĳ��� �ٲٰ�, �ڽĳ���� �ڽ��� ������ �� ������ �ѹ� �� ��ġ�� ����.



//������
										//���� �̿��ϸ� ������ �����ѵ�, ���� �� n���� ��Ҹ� �ִ����� �ְԵǸ�
										//���Կ���, ���������� ���ؼ� ���������� ������ �� ���� ��������� �ȴ�.
										//�̶� n���� ��Ҹ� ������ O(nlog n)�� �ð����⵵�� ������ �ȴ�.
void heap_sort(element a[], int n)
{
	int i;
	HeapType* h;
	h = create();
	init(h);							//���������� �� �ʱ�ȭ

	for (i = 0; i < n; i++)
	{
		insert_max_heap(h, a[i]);		//�Ű������� ���� ��� ������ heap�� ������
	}

	for (i = (n - 1); i >= 0; i--)
	{
		a[i] = delete_max_heap(h);		//a[i]�� ���ĵ� ������ 1���� ������ (�θ� ���� �ִ����̹Ƿ� �ִ밪�� ���ʷ� ������ ��)
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
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };		// ���Կ��꿡�� �־��ǰ��, ��Ʈ ������ �ö󰡾� �Ѵ�. O(log n)
	element e4, e5, e6;									// �������꿡���� �־��ǰ��, ��Ʈ ���������� �������� ��. O(log n)
	HeapType* heap;										// => Ʈ������� ���̸�ŭ �ð��� �ɸ�
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