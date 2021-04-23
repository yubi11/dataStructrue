#include <stdio.h>
#include <malloc.h>

typedef int elementS;

typedef struct StackNode
{
	elementS data;
	struct StackNode* link;
}QueueNode;


typedef struct
{
	QueueNode* top;					//스택이므로 top노드를 가리키는 top포인터
}LinkedStackType;

void initS(LinkedStackType* s)
{
	s->top = NULL;
}

int is_emptyS(LinkedStackType* s)
{
	return (s->top == NULL);
}

int is_fullS(LinkedStackType* s)
{
	return 0;
}

void pushS(LinkedStackType* s, elementS item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));		// 스택노드를 생성해준다
	temp->data = item;												// 스택노드의 데이터를 저장 한 후,
	temp->link = s->top;											// 이 노드가  바로아래노드를 가리키게 한다.
	s->top = temp;													// top포인터는 현재 최상위에 있는 top노드를 가리킨다.
}

void print_stack(LinkedStackType* s)
{
	for (QueueNode* p = s->top; p != NULL; p = p->link)			// top먼저 하나씩 실행, 하나씩 순차적으로 내려가면서 출력하게 됨
		printf("%d->", p->data);
	printf("NULL\n");
}

elementS popS(LinkedStackType* s)
{
	if (is_emptyS(s))
	{
		fprintf(stderr, "스택 빔");
		exit(1);
	}
	else
	{
		QueueNode* temp = s->top;								// 탑노드를 임시로 저장하여
		int data = temp->data;									// 해당 노드의 데이터를 빼주고
		s->top = s->top->link;									// top포인터를 이제 top을 삭제할거니까 top밑에 있는 데이터로 지정
		free(temp);												// top은 삭제
		return data;
	}
}

/*
int main(void)
{
	LinkedStackType s;
	initS(&s);
	pushS(&s, 1);
	print_stack(&s);
	pushS(&s, 2);
	print_stack(&s);
	pushS(&s, 3);
	print_stack(&s);

	popS(&s);
	print_stack(&s);
	popS(&s);
	print_stack(&s);
	popS(&s);
	print_stack(&s);
	return 0;
}
*/