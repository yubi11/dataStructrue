#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int elementP;					// 스택에 들어가는 자료형은 항상 바뀔 수 있으므로 typedef로

typedef struct StackTypeP
{
	elementP data[MAX_STACK_SIZE];
	int top;
}StackTypeP;

void init_stackP(StackTypeP* s)			// 초기화는 top을 -1로 만들면서 실행
{
	s->top = -1;
}


int is_emptyP(StackTypeP* s)
{
	return (s->top == -1);					// 요소가 없을 떄는 -1을 가리킴
}

int is_fullP(StackTypeP* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));	// 요소가 가득 찰 때는 MAX-1, top이 MAX면 인덱스범위를 넘어감
}

void pushP(StackTypeP* s, elementP item)
{
	if (is_fullP(s))
	{												// 스택 포화 예외처리 후,
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;						// top을 1 올리고 스택에 값을 넣어 줌
}

elementP popP(StackTypeP* s)
{
	if (is_emptyP(s))								//요소가 비었을 때 예외처리,
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];					// 스택에 top 값을 빼고난 후 -1 해줌
}


int check_matching(const char* in)
{
	StackTypeP s;							// 함수내에서 사용할 임시 스택
	char ch, open_ch;						// ch는 문자열을 한글자씩 받아올 변수 open_ch는 스택내부의 괄호를 받아올 변수

	int i, n = strlen(in);					// i는 for문 순회용, n은 문자열의 길이(NULL 문자 포함 x)
	init_stackP(&s);						// 스택 초기화

	for (i = 0; i < n; i++)
	{
		ch = in[i];							
		switch (ch)
		{
		case '(': case '[' : case '{':		// ( [ { 처럼 괄호시작 문자를 받을 시
			pushP(&s, ch);					// 해당 문자를 스택에 저장한다.
			break;
		
		case ')': case ']': case '}':		// ) ] } 처럼 괄호끝 문자를 받을 시
			if (is_emptyP(&s)) return 0;	// 스택이 비었는지 확인 하고
			else
			{
				open_ch = popP(&s);			// 비어있지않다면 pop을해서 open_ch에 넣는다 
				if ((open_ch == '(' && ch != ')' ||	//opench가 괄호 시작문자인데, ch가 괄호 끝문자가 아닐 시, 오류
					(open_ch == '[' && ch != ']') ||
					(open_ch == "{" && ch != '}')))
				{
					return 0;
				}
			}

		}

	}
	if (!is_emptyP(&s))				// 모두 끝나고 스택이 비워져 있어야함
		return 0;				
	return 1;						// 정상적으로 마칠 시, 1이 리턴됨
}

/*
int main(void)
{
	char* p = "{A[(i+1)]=0;}";
	if (check_matching(p) == 1)
		printf("%s 괄호검사 성공\n", p);
	else
		printf("%s 괄호검사 실패\n", p);
	return 0;
}
*/