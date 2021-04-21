#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;					// 스택에 들어가는 자료형은 항상 바뀔 수 있으므로 typedef로

typedef struct StackType
{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)			// 초기화는 top을 -1로 만들면서 실행
{
	s->top = -1;
}


int is_empty(StackType* s)
{
	return (s->top == -1);					// 요소가 없을 떄는 -1을 가리킴
}

int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));	// 요소가 가득 찰 때는 MAX-1, top이 MAX면 인덱스범위를 넘어감
}

void push(StackType* s,element item)
{
	if (is_full(s))
	{												// 스택 포화 예외처리 후,
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;						// top을 1 올리고 스택에 값을 넣어 줌
}

element pop(StackType* s)
{
	if (is_empty(s))								//요소가 비었을 때 예외처리,
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];					// 스택에 top 값을 빼고난 후 -1 해줌
}

/*
int main(void)
{
	
					Stack Stack
	StackType s;

	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	
	

	
	
					Dynamic Stack
	StackType* s;

	s = (StackType*)malloc(sizeof(StackType));
	init_stack(s);
	push(s, 1);
	push(s, 2);
	push(s, 3);
	printf("%d\n", pop(s));
	printf("%d\n", pop(s));
	printf("%d\n", pop(s));

	return 0;
	
}
*/