#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNodeH 
{
	int weight;
	char ch;
	struct TreeNodeH* left;
	struct TreeNodeH* right;
}TreeNodeH;

typedef struct 
{
	TreeNodeH* ptree;
	char ch;
	int key;
}elementH;

typedef struct 
{
	elementH heap[MAX_ELEMENT];
	int heap_size;
}HeapTypeH;

HeapTypeH* createH()
{
	return (HeapTypeH*)malloc(sizeof(HeapTypeH));
}

void initH(HeapTypeH* h)
{
	h->heap_size = 0;
}

void insert_min_heap(HeapTypeH* h, elementH item)
{
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key) )
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

elementH delete_min_heap(HeapTypeH* h)
{
	int parent, child;
	elementH item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child > h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

TreeNodeH* make_tree(TreeNodeH* left,TreeNodeH* right)
{
	TreeNodeH* node = (TreeNodeH*)malloc(sizeof(TreeNodeH));
	node->left = left;
	node->right = right;
	return node;
}

void destroy_tree(TreeNodeH* root)
{
	if (root == NULL)
		return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNodeH* root)
{
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNodeH* root, int codes[], int top)
{
	if (root->left)
	{
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	if (root->right)
	{
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	if (is_leaf(root))
	{
		printf("%c:", root->ch);
		print_array(codes, top);
	}

}

void huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNodeH* node, * x;
	HeapTypeH* heap;
	elementH e, e1, e2;
	int codes[100];
	int top = 0;
	heap = createH();
	initH(heap);
	for (i = 0; i < n; i++)
	{
		node = make_tree(NULL, NULL);			//문자노드를 만들고 최소큐에 넣는 과정
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	for (i = 1; i < n; i++)
	{
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("%d+%d->%d\n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap);
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);
	free(heap);

}

int main(void)
{
	char ch_list[] = { 's','i','n','t','e' };
	int freq[] = { 4,6,8,12,15 };
	huffman_tree(freq, ch_list, 5);
	return 0;
}

//텍스트가 e,t,n,i,s 5개 글자로만 이루어졌다고 가정한다.
// 각 글자가 쓰인 빈도의 총합은 45, 5개의 글자를 표현하기 위해선 (000,001,010,011,100) 3비트가 필요함
// 즉 45개의 글자 * 3비트 = 145비트가 필요

//만약 자주나오는 코드를 2비트로 줄이고, 자주안나오는경우 3비트로 표현한다면 필요비트를 줄일 수 있다.
//ex) e t n이 자주쓰이는 글자라면(00 01 10), i s가 자주 쓰이지 않는다면 (110 111) 비트를 줄일 수 있음, 다른코드의 접두부가 포함되면안됨
// 예를들어 00으로 시작하는 녀석이 있다면 001은 안됨, 11이 있다면 110이나 111도 안됨

//만약 01000010 이란 코드가 있다면, 어디서 끊을건지 정해야한다. 01 or 010 허나 여기선 010은 없으므로 01
//다음 코드는 00 or 000, 000도 없으므로 00임

//절차:
/*
	1. 모든 문자를 출현 빈도수에 따라 나열,
	2. 가장 빈도가 낮은 문자 2개를 최소 힙을 이용해서, 이진트리로 만들기, 루트는 두 노드의 합
	3. 마지막 단말노드 2개를 제외하고 루트 노드를 넣음
	4. 목록에 1개만 남을 때 까지 2-3을 반복
	5. 왼쪽 자식은 1, 오른쪽 자식은 0을 마크

	결과적으로 단어의 코드는 이 트리에 의해서 정해지게 된다.
	
	예를들어) s는 루트를 따라 내려가면 1,1,1이란 코드를 얻게 됨(111)
			 i는 루트를 따라 내려가면 1,1,0이란 코드를 얻게됨 (110)

					   45
					/	  \
			      /	        \
		      18(1)			  \
		    /	    \	        \
		10(1)	     \		    27(0)
		/    \        \	        /	  \
	4(s)(1)  6(i)(0) 8(n)(0) 12(t)(1) 15(e)(0)


	실제 구축단계:
	1. 빈도수에 따라 우선순위 큐 구축 (s,i,n,t,e)순으로 최소큐가 놓이게 됨
	2. 우선순위가 높은 2개를 삭제 후 이진트리 구축, 삭제한 2개를 반환받아 왼쪽하단부분트리를 만든다. 원래 최소큐는 n,t,e만 남게됨
	3. 삭제된 2개의 노드 두 값의 합(10)에 해당하는 부모노드를, 원래 최소큐에 삽입해줌
	
	최소큐가 비어있을 때 까지 2와 3을 계속 반복
	끝나고 오른쪽,왼쪽자식에 따라 0,1 마크
*/



