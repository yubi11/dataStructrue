#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef char elementF;					// 스택에 들어가는 자료형은 항상 바뀔 수 있으므로 typedef로

typedef struct StackTypeF
{
	elementF data[MAX_STACK_SIZE];
	int top;
}StackTypeF;

void init_stackF(StackTypeF* s)			// 초기화는 top을 -1로 만들면서 실행
{
	s->top = -1;
}


int is_emptyF(StackTypeF* s)
{
	return (s->top == -1);					// 요소가 없을 떄는 -1을 가리킴
}

int is_fullF(StackTypeF* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));	// 요소가 가득 찰 때는 MAX-1, top이 MAX면 인덱스범위를 넘어감
}

void pushF(StackTypeF* s, elementF item)
{
	if (is_fullF(s))
	{												// 스택 포화 예외처리 후,
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;						// top을 1 올리고 스택에 값을 넣어 줌
}

elementF popF(StackTypeF* s)
{
	if (is_emptyF(s))								//요소가 비었을 때 예외처리,
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];					// 스택에 top 값을 빼고난 후 -1 해줌
}



int eval(char exp[])
{
	int op1, op2, value, i = 0;				// op1 op2는 스택안에있는 수를 가져와서 연산할 때 수에 해당하는 부분
	int len = strlen(exp);					// 문자열 개수
	char ch;									
	StackTypeF s;							// 함수용 스택
	
	init_stackF(&s);							// 스택 초기화
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')	// 문자열이 연산자가 아닐경우 스택에 넣게됨
		{
			value = ch - '0';							// 스택에 넣을 때, 문자열의 숫자 또한 문자로 취급되므로 int형 정수에 아스키코드를 맞춰서 입력
			pushF(&s, value);							
		}
		else
		{										// ch가 연산자인 경우
			op2 = popF(&s);						//op 변수에 숫자 값들이 들어가 있음 
			op1 = popF(&s);						
			switch (ch)
			{
			case '+': pushF(&s, op1 + op2);		//+일경우 op1과op2를 더해서 스택에 넣음
				break;
			case '-': pushF(&s, op1 - op2);		//-일경우 op1과op2를 빼서 스택에 넣음
				break;
			case '*': pushF(&s, op1 * op2);		//+일경우 op1과op2를 곱해서 스택에 넣음
				break;
			case '/': pushF(&s, op1 / op2);		//+일경우 op1과op2를 나눠서 스택에 넣음
				break;
			}
		}

	}
	return popF(&s);								//마지막으로 계산되어 남아있는 수를 pop하면서 마무리
}
/*
int main()
{
	int result;
	printf("후위표기식은 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("결과값은 %d\n", result);
	return 0;
}
*/