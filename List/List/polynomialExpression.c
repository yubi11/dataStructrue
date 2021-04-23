
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNodeP
{
	int coef;
	int expon;
	struct ListNodeP* link;								//다항식의 차수와 계수를 담는 노드
}ListNodeP;

typedef struct ListTypeP
{
	int size;
	ListNodeP* head;									// 다항식노드를 가리킬 헤드테일을 지닌 헤더
	ListNodeP* tail;
}ListTypeP;

void errorP(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


ListTypeP* createP()
{																// 동적할당주소를 만들고 초기화 하고 반환하는 팩토리함수
	ListTypeP* plist = (ListTypeP*)malloc(sizeof(ListTypeP));	
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_lastP(ListTypeP* plist, int coef, int expon)		// 연결리스트의 마지막 노드로 하나를 추가 해줌
{
	ListNodeP* temp = (ListNodeP*)malloc(sizeof(ListNodeP));	// 노드동적으로 할당
	if (temp == NULL) errorP("메모리 할당 에러\n");				// 해당 노드에 데이터를 추가
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL)									// 만약 연결리스트가 비어있는경우
	{
		plist->head = plist->tail = temp;						// 연결리스트의 헤드,테일을 방금 생성한 노드에 연결
	}
	else
	{															// 어떤 노드가 이미 들어있는경우,
		plist->tail->link = temp;								// 노드의 마지막은 방금 생성한 노드가 되므로, 기존의 마지막 노드를 방금 생성한 노드로 연결
		plist->tail = temp;										// 노드의 마지막이, 방금 생성한 노드가 됨
	}
	plist->size++;												// 연결리스트에 하나의 노드가 추가 되었으므로 사이즈 +1
}

void poly_add(ListTypeP* plist1, ListTypeP* plist2, ListTypeP* plist3)
{
	ListNodeP* a = plist1->head;									// 두 다항식을 더해서 마지막 매개변수에 해당하는 다항식노드에 넣는 방법
	ListNodeP* b = plist2->head;									// 3개의 연결리스트 헤더가 사용 됨
	int sum;														// sum은 합 값을 넣어줄 임시변수

	while (a && b)													// a와 b가 존재, a와 b는 점점 tail쪽으로 가게될 것이며, 마지막노드에 다다를때 NULL이 될 것임
	{
		if (a->expon == b->expon)									// a와 b의 차수를 비교하고, 같다면
		{
			sum = a->coef + b->coef;								// sum 변수에 a와 b의 차수를 더한 값을 넣는다.
			if (sum != 0)											// 만약 그 값이 0이 아니라면
				insert_lastP(plist3, sum, a->expon);				// 3번째 연결리스트에 해당 값을, 해당 차수로 하여 넣는다
			a = a->link;											// 끝나면 a와 b는 다음 노드로 이동
			b = b->link;
		}
		else if (a->expon > b->expon)								// a와 b의 차수를 비교하고 a가 더 크다면
		{
			insert_lastP(plist3, a->coef, a->expon);				// a의 차수와 계수를 그대로 삽입
			a = a->link;											// 그리고 a만 다음 노드로 이동
		}
		else
		{
			insert_lastP(plist3, b->coef, b->expon);				// 위와 같으나, b가 더 큰경우
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link)									// 두 리스트 중 하나라도 먼저 끝나면 while문이 끝나고, 이 말은 즉, 더 이상 겹치는 차수가 없다는 의미 (순서대로 있다는 가정하에)
		insert_lastP(plist3, a->coef, a->expon);					// 그러므로 남은 노드데이터들을 리스트3에 넣어준다.
	for (; b != NULL; b = b->link)
		insert_lastP(plist3, b->coef, b->expon);
}

void poly_print(ListTypeP* plist)
{
	ListNodeP* p = plist->head;										// 리스트헤더를 받아서
	
	printf("Polynomial =");
	for (; p; p = p->link)											// 마지막 노드 까지 출력
	{
		if(p->expon !=0)											
			printf("%dx^%d+ ",p->coef, p->expon);					
		else
			printf("%d", p->coef);
	}
	printf("\n");
}

/*
int main(void)
{
	ListTypeP* list1, * list2, * list3;

	list1 = createP();
	list2 = createP();
	list3 = createP();

	insert_lastP(list1, 3, 12);
	insert_lastP(list1, 2, 8);
	insert_lastP(list1, 1, 0);

	insert_lastP(list2, 8, 12);
	insert_lastP(list2, -3, 10);
	insert_lastP(list2, 10, 6);
											//여기서 쓰인 poly_add는 다항식들이 모두 이미 순서정렬이 되어있어야 함
	poly_print(list1);
	poly_print(list2);

	poly_add(list1, list2, list3);
	poly_print(list3);

	free(list1);
	free(list2);
	free(list3);
}
*/