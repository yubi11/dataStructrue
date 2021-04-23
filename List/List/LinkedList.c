
#include <stdio.h>
#include <stdlib.h>

typedef int elementL;

typedef struct ListNodeL
{
	elementL data;
	struct ListNodeL* link;				//연결리스트의 노드는 다음 노드와 연결되어야하므로 노드포인터를 지님

}ListNodeL;

ListNodeL* insert_firstL(ListNodeL* head, int value)
{
	ListNodeL* p = (ListNodeL*)malloc(sizeof(ListNodeL));		// 맨 앞 노드를 삽입하는 과정
	p->data = value;											// p에 잠시 동적할당을 하고 데이터를 담은 후 반환 해줌
	p->link = head;												// p의 다음노드link는 기존의 헤드를 가리키며
	head = p;													// head는 지금 생성한 노드가 된다.
	return head;
}

ListNodeL* insertL(ListNodeL* head, ListNodeL* pre, elementL value)
{																//pre의 오른쪽에 노드 추가
	ListNodeL* p = (ListNodeL*)malloc(sizeof(ListNodeL));		// p를 생성
	p->data = value;											// p의 데이터를 담고
	p->link = pre->link;										// pre의 다음 노드를 p의 link로 설정하여, 끼어 넣어줌
	pre->link = p;												// pre는 다음 노드를 방금 생성한 p로 설정
	return head;
}


ListNodeL* delete_fristL(ListNodeL* head)
{
	ListNodeL* removed;										// head노드로 연결리스트에 진입함
	if (head == NULL) return NULL;							// head가 NULL이라면 연결리스트는 아무노드도 없는 것이므로 반환
	removed = head;											// 지울노드를 잠시 저장할 객체
	head = removed->link;									// head는 이제 removed->link를 가리킴, 즉 맨앞노드의 다음노드를 가리킴
	free(removed);											// removed는 동적할당된 맨앞주소를 가리키므로 이를 제거함
	return head;											
}

ListNodeL* deleteL(ListNodeL* head, ListNodeL* pre)		
{															//head노드로 연결리스트 진입
	ListNodeL* removed;										// 지울객체 저장
	removed = pre->link;									// 지울노드는 pre의 다음 노드
	pre->link = removed->link;								// pre의 다음노드는 이제 지울노드의 다음노드
	free(removed);											// 지울노드를 삭제
	return head;											
}

void print_listL(ListNodeL* head)
{
	for (ListNodeL* p = head; p != NULL; p = p->link)		//p가 NULL이 아닐때까지 p = p->link로 순회하면서 출력 
		printf("%d->", p->data);
	printf("NULL\n");
}

ListNodeL* search_listL(ListNodeL* head, elementL x)	
{	
	ListNodeL* p = head;								// 찾을 데이터를 가지고 있는 노드들을 검사한다.

	while (p != NULL)									// 리스트를 순회시킨다.
	{
		if (p->data == x)								// 노드에서 탐색데이터를 찾을 시, 해당 노드주소를 반환
			return p;
		p = p->link;
	}
	return NULL;										//없으면 NULL
}

ListNodeL* concat_listL(ListNodeL* head1, ListNodeL* head2)
{														//리스트를 이어주는 함수, 첫 리스트의 뒤로 두번째 리스트가 오게 됨
	if (head1 == NULL)									// 리스트1이 없을경우 리스트2반환
		return head2;
	else if (head2 == NULL)								// 리스트2가 없을경우 리스트1 반환
		return head1;
	else												// 리스트 12 모두 있을경우
	{
		ListNodeL* p;									// 새 노드를 만들고 리스트 1 복사
		p = head1;										 
		while (p->link != NULL)							// 리스트의 끝으로 감
			p = p->link;
		p->link = head2;								// 리스트의 끝을 리스트2로 이어줌
		return head1;
	}

}

ListNodeL* reverse(ListNodeL* head)
{
	ListNodeL* p,* q,* r;								//리스트를 역순으로 만드는 함수
	
	p = head;											//p는 순회노드
	q = NULL;											//q는 이어주는 노드
	while (p != NULL)									//r은 이어져지는 노드
	{
		r = q;											// r은 q로 이동
		q = p;											// q는 p로 이동
		p = p->link;									// p는 다음노드로 이동
		q->link = r;									// q는 전노드인 r을 이어주게 됨
	}
	return q;											// q로 시작하는 head노드 반환
}

/*
int main()
{
	ListNodeL* head = NULL;
	ListNodeL* search = NULL;
	for (int i = 0; i < 5; i++)
	{
		head = insert_firstL(head, i);
		print_listL(head);
		head = reverse(head);
		search = search_listL(head, 2);
		if(search!=NULL)
			printf("%d\n", search->data);
		print_listL(head);
	}
	for (int i = 0; i < 5; i++)
	{
		head = delete_fristL(head);
		print_listL(head);
	}
	return 0;

}
*/