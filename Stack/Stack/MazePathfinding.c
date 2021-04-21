#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct elementM
{
	short r;
	short c;
}elementM;					// 스택에 들어가는 자료형은 항상 바뀔 수 있으므로 typedef로

typedef struct StackTypeM
{
	elementM data[MAX_STACK_SIZE];
	int top;
}StackTypeM;

elementM here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] =
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};



void init_stackM(StackTypeM* s)			// 초기화는 top을 -1로 만들면서 실행
{
	s->top = -1;
}


int is_emptyM(StackTypeM* s)
{
	return (s->top == -1);					// 요소가 없을 떄는 -1을 가리킴
}

int is_fullM(StackTypeM* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));	// 요소가 가득 찰 때는 MAX-1, top이 MAX면 인덱스범위를 넘어감
}

void pushM(StackTypeM* s, elementM item)
{
	if (is_fullM(s))
	{												// 스택 포화 예외처리 후,
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;						// top을 1 올리고 스택에 값을 넣어 줌
}

elementM popM(StackTypeM* s)
{
	if (is_emptyM(s))								//요소가 비었을 때 예외처리,
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];					// 스택에 top 값을 빼고난 후 -1 해줌
}

void push_loc(StackTypeM* s, int r, int c)				// r,c 기준에서 뚫려있는 길을 스택에 넣게 됨
{
	if (r < 0 || c < 0) return;							// r,c는 무조건 0 이상
	if (maze[r][c] != '1' && maze[r][c] != '.')			// 벽이면 안되며, 왔던곳이면 안됨
	{											
		elementM tmp;									// 요소를 만들어
		tmp.r = r;										
		tmp.c = c;
		pushM(s, tmp);									//뚫린좌표를 스택에 넣음
	}

}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])			// 맵을 넣음
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++)						//맵 출력
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}

}

int main()
{
	int r, c;
	StackTypeM s;
	
	init_stack(&s);								//스택 초기화
	here = entry;								// 진입점,시작점 동일
	while (maze[here.r][here.c] != 'x')			// 현재 위치가 끝지점이 아닐때 까지 계속 찾음
	{
		r = here.r;
		c = here.c;
		maze[r][c] = '.';						// 들린 위치는 .으로 표시
		maze_print(maze);						// 어느 한 곳을 들릴 때 마다 계속 출력
		push_loc(&s, r - 1, c);					// 좌우 위아래 다 체크
		push_loc(&s, r + 1, c);
		push_loc(&s, r , c-1);
		push_loc(&s, r, c+1);

		if (is_emptyM(&s))						// 스택이 비면 더 이상 갈 길이 없으므로 실패
		{
			printf("실패\n");
		}
		else
			here = popM(&s);					// 스택이 비지않았다면 계속 pop하면서 그 좌표를 here로 표시하여 진행함
	}
	printf("성공");								// 끝나면 성공

	return 0;
}