#include <stdio.h>
#include <stdlib.h>

typedef char elementC[100];

typedef struct ListNodeC
{
	elementC data;
	struct ListNodeC* link;								//다항식의 차수와 계수를 담는 노드
}ListNodeC;

typedef struct ListTypeC
{
	int size;
	ListNodeC* head;									// 다항식노드를 가리킬 헤드테일을 지닌 헤더
}ListTypeC;

void errorC(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


ListTypeC* createC()
{																// 동적할당주소를 만들고 초기화 하고 반환하는 팩토리함수
	ListTypeC* plist = (ListTypeC*)malloc(sizeof(ListTypeC));
	plist->size = 0;
	plist->head = NULL;
	return plist;
}

ListTypeC* insert_firstC(ListTypeC* header, elementC data)		// 맨앞에 노드를 넣음
{
	ListNodeC* node = (ListNodeC*)malloc(sizeof(ListNodeC));	//노드 동적 할당하고 데이터 저장
	strcpy(node->data, data);
	if (header->head == NULL)									// 헤더가 NULL일 시
	{
		header->head = node;									// 헤더는 방금 생성한 노드
		node->link = header->head;								// 방금 생성한 노드는 자신을 가리킴
	}
	else
	{
		node->link = header->head->link;						// 환형연결리스트는 헤더가 마지막부분을 가리키고, 헤더는 맨앞을 가리킴
		header->head->link = node;								// 헤더의 다음 노드는 방금 생성한 노드
	}
	header->size++;												//헤더사이즈를 올림
	return header;
}

ListTypeC* insert_lastC(ListTypeC* header, elementC data)
{
	ListNodeC* node = (ListNodeC*)malloc(sizeof(ListNodeC));
	strcpy(node->data, data);
	if (header->head == NULL)
	{
		header->head = node;
		node->link = header->head;
	}
	else
	{
		node->link = header->head->link;						// 방금 만든 노드의 다음은 헤더가 가리키고있던 부분
		header->head->link = node;								// 헤더의 다음은 방금 생성한 노드가 되며
		header->head = node;									// 방금 생성한 노드는 마지막 노드이므로 헤더가 됨
	}
	header->size++;
	return header;
}

ListTypeC* insert_middleC(ListTypeC* header, int pos, elementC data)
{
	if (!(pos >= 0 || pos <= header->size))					//예외처리로 pos값을 걸러낸다
		return header;
	if (pos == header->size)								// 만약 연결리스트의 개수와 같다면 마지막에 넣는것이므로 last insert
	{
		insert_lastC(header, data);
		return header;
	}
	else if (pos == 0)							
	{
		insert_firstC(header, data);
		return header;
	}

	ListNodeC* node = (ListNodeC*)malloc(sizeof(ListNodeC));
	strcpy(node->data, data);
	ListNodeC* temp = header->head;

	for (int i = 0; i < pos; i++)						//temp로 해당 포지션에 위치하는 노드에 접근
	{
		temp = temp->link;
	}
	node->link = temp->link;							// 새로운 노드의 다음 값은 방금 접근한 노드의 다음 값
	temp->link = node;									// 방금 접근한 노드의 다음 값은 새로운 노드
	header->size++;										
	return header;

}

void print_ListC(ListTypeC* header)
{
	ListNodeC* itr = header->head->link;
	for (; itr != header->head; itr = itr->link)
		printf("%s | ", itr->data);
	printf("%s", itr->data);

	printf("\n");
}

ListNodeC delete_first(ListTypeC* header)
{
	ListNodeC* p = header->head->link;			// 환형은 헤더가 마지막 부분이므로 한칸 더 앞으로 가야 맨 앞노드가 된다.
	ListNodeC dat = {p->data,NULL};				// 지우기전에 데이터를 저장해주고
	header->head->link = p->link;				// 헤더의 다음 값은 맨 앞노드의 다음값으로 지정
	free(p);									// 지운다.
	header->size--;								// 사이즈를 내리고, 0이면 NULL로 지정해준다.
	if (header->size == 0)
		header->head = NULL;
	return dat;
}

ListNodeC delete_last(ListTypeC* header)
{
	ListNodeC* p = header->head;
	ListNodeC data = {p->data,NULL};
	
	ListNodeC* q = header->head->link;			// 마지막 값으로 접근하여 값을 조정해줌 위와 같은 방식
	while (q->link != p)
	{
		q = q->link;
	}
	header->head = q;
	q->link = p->link;
	free(p); 
	header->size--;
	if (header->size == 0)
		header->head = NULL;
	return data;
}

ListNodeC delete_Middle(ListTypeC* header,int pos)
{
	if(pos>=0 || pos< header->size)


	if (pos == 0)
	{
		ListNodeC res = delete_first(header);
		return res;
	}
	else if (pos == header->size-1)
	{
		ListNodeC res = delete_last(header);
		return res;
	}

	ListNodeC* p = header->head->link;
	ListNodeC data = { p->data,NULL };
	for (int i = 0; i < pos-1; i++)
	{
		p = p->link;
	}
	ListNodeC* q = p->link;
	ListNodeC dat = { q->data,NULL };
	p->link = q->link;
	
	free(q);
	header->size--;
	if (header->size == 0)
		header->head = NULL;
	return dat;
}


/*
int main()
{
	ListTypeC* box;
	box = createC();

	
	insert_firstC(box, "생각대로");
	print_ListC(box);
	insert_lastC(box, "잘되는");
	print_ListC(box);
	insert_lastC(box, "군요");
	print_ListC(box);
	insert_firstC(box, "역시");
	print_ListC(box);

	insert_middleC(box, 4, "무사히");
	print_ListC(box);
	insert_middleC(box, 0, "굿");
	print_ListC(box);
	
	delete_first(box);
	print_ListC(box);
	delete_last(box);
	print_ListC(box);
	delete_Middle(box, 3);
	print_ListC(box);

	
	insert_firstC(box, "Kim");
	insert_firstC(box, "Park");
	insert_firstC(box, "Choi");

	ListNodeC* p = box->head;
	for (int i = 0; i < 10; i++)
	{
		printf("현재 차례 = %s\n", p->data);
		p = p->link;
	}
	
	return 0;
}
*/