#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;					// 스택에 들어가는 자료형은 항상 바뀔 수 있으므로 typedef로

element stack[MAX_STACK_SIZE];			// 스택 통을 자료형배열로 선언함, 크기제한이 있음
int top = -1;							// top은 항상 -1로 설정됨, 그래야 0번째 인덱스부터 차례대로 들어가게 됨

int is_emptyGlob()		
{
	return (top == -1);					// 요소가 없을 떄는 -1을 가리킴
}

int is_fullGlob()
{
	return (top == (MAX_STACK_SIZE - 1));	// 요소가 가득 찰 때는 MAX-1, top이 MAX면 인덱스범위를 넘어감
}

void pushGlob(element item)
{
	if (is_fullGlob())
	{												// 스택 포화 예외처리 후,
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;						// top을 1 올리고 스택에 값을 넣어 줌
}

element popGlob()
{
	if (is_emptyGlob())								//요소가 비었을 때 예외처리,
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top--];					// 스택에 top 값을 빼고난 후 -1 해줌
}

/*
int main(void)
{
	push(1);
	push(2);
	push(3);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;
}
*/