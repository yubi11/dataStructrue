#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef char elementITP;					// 스택에 들어가는 자료형은 항상 바뀔 수 있으므로 typedef로

typedef struct StackTypeITP
{
	elementITP data[MAX_STACK_SIZE];
	int top;
}StackTypeITP;

void init_stackITP(StackTypeITP* s)			// 초기화는 top을 -1로 만들면서 실행
{
	s->top = -1;
}


int is_emptyITP(StackTypeITP* s)
{
	return (s->top == -1);					// 요소가 없을 떄는 -1을 가리킴
}

int is_fullITP(StackTypeITP* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));	// 요소가 가득 찰 때는 MAX-1, top이 MAX면 인덱스범위를 넘어감
}

void pushITP(StackTypeITP* s, elementITP item)
{
	if (is_fullITP(s))
	{												// 스택 포화 예외처리 후,
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;						// top을 1 올리고 스택에 값을 넣어 줌
}

elementITP peekITP(StackTypeITP* s)
{
	return s->data[s->top];
}


elementITP popITP(StackTypeITP* s)
{
	if (is_emptyITP(s))								//요소가 비었을 때 예외처리,
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];					// 스택에 top 값을 빼고난 후 -1 해줌
}

int prec(char op)						//연산자의 우선순위를 정하는 함수
{
	switch (op)
	{
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}


void infix_to_postfix(char exp[])
{
	int i = 0;						 
	char ch, top_op;				// ch에 글자를 받음, top_op는 저장된 스택을 꺼내올때 담을 변수 
	int len = strlen(exp);			 
	StackTypeITP s;					// 스택 초기화

	init_stackITP(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];				// 글자 한글자를 받아옴
		switch (ch)
		{
			case '+': case '-' : case '*': case '/':		// 그 글자가 연산자 일 시,
				while (!is_emptyITP(&s) && (prec(ch) <= prec(peekITP(&s))))	// 스택이 비지않았고, 방금들어온 연산자가 전에들어온 것보다 연산 순위가 높다면. 전에들어온 연산자 출력
				{
					printf("%c", popITP(&s));	// 스택을 꺼내옴
				}
				pushITP(&s, ch);
				break;

			case '(':					//그 글자가 괄호 시작 일 시,
				pushITP(&s, ch);		// 괄호 저장
				break;

			case ')':					// 그 글자가 괄호 끝 일 시,
				top_op = popITP(&s);	// top_op에 저장된 연산자를 꺼내옴
				while (top_op != '(')	// top이 괄호가 아닐 때 까지 top_op를 계속 뽑으면서 출력 함 
				{
					printf("%c", top_op);	 
					top_op = popITP(&s);	
				}
				break;
			default:
				printf("%c", ch);		// 숫자는 그냥 출력
				break;
		}
	}
	while (!is_emptyITP(&s))			// 모든 과정이 끝나고 스택을 비움 
		printf("%c", popITP(&s));
}

/*
int main(void)
{
	char* s = "(2+3)*4+9";
	printf("중위표시수식 %s\n", s);
	printf("후위표시수식 %s\n", s);
	infix_to_postfix(s);
	printf("\n");
	return 0;

}
*/