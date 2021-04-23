/*
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNodeP
{
	int coef;
	int expon;
	struct ListNodeP* link;
}ListNodeP;

typedef struct ListTypeP
{
	int size;
	ListNodeP* head;
	ListNodeP* tail;
}ListTypeP;

void errorP(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


ListTypeP* createP()
{
	ListTypeP* plist = (ListTypeP*)malloc(sizeof(ListTypeP));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_lastP(ListTypeP* plist, int coef, int expon)
{
	ListNodeP* temp = (ListNodeP*)malloc(sizeof(ListNodeP));
	if (temp == NULL) errorP("메모리 할당 에러\n");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL)
	{
		plist->head = plist->tail = temp;
	}
	else
	{
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void poly_add(ListTypeP* plist1, ListTypeP* plist2, ListTypeP* plist3)
{
	ListNodeP* a = plist1->head;
	ListNodeP* b = plist2->head;
	int sum;

	while (a && b)
	{
		if (a->expon == b->expon)
		{
			sum = a->coef + b->coef;
			if (sum != 0)
				insert_lastP(plist3, sum, a->expon);
			a = a->link;
			b = b->link;
		}
		else if (a->expon > b->expon)
		{
			insert_lastP(plist3, a->coef, a->expon);
			a = a->link;
		}
		else
		{
			insert_lastP(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link)
		insert_lastP(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_lastP(plist3, b->coef, b->expon);
}

void poly_print(ListTypeP* plist)
{
	ListNodeP* p = plist->head;
	
	printf("Polynomial =");
	for (; p; p = p->link)
	{
		if(p->expon !=0)
			printf("%dx^%d+ ",p->coef, p->expon);
		else
			printf("%d", p->coef);
	}
	printf("\n");
}

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

	poly_print(list1);
	poly_print(list2);

	poly_add(list1, list2, list3);
	poly_print(list3);

	free(list1);
	free(list2);
	free(list3);
}
*/