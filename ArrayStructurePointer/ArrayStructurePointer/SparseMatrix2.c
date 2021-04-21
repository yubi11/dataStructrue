#include <stdio.h>
#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct 
{
	int row, col, value;
}element;

typedef struct SparseMatrix 
{
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c;
	int ca = 0;		//a의 현재 항 수 (최고차항보다 커지면 끝남)
	int cb = 0;		//b의 현재 항 수
	int cc = 0;
	if (a.rows != b.rows || a.cols != b.cols)
	{
		fprintf(stderr, "희소 해렬 크기에러\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) //a와 b의 현재 항 수가 각 a,b의 항의 개수보다 커지면 끝
	{
		int inda = a.data[ca].row * a.cols + a.data[ca].col; //		  0,1,2 행렬을 이런 식으로 인덱스화 한 것,
															//		  3,4,5 그래서 row의 인덱스에 col 개수를 곱해준 후,
															//		  6,7,8 마지막으로 col 인덱스를 더해줌 
															//		  ex) [1][1]은 인덱스로치면 4에 해당하는 곳
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb)	// 행렬에서 빼내온 인덱스를 비교함, 만약 a의 인덱스가 먼저나올 시
		{
			c.data[cc++] = a.data[ca++];		//인덱스가 먼저나오는 부분을 통째로 가져옴
		}
		else if (inda == indb)	// a,b 인덱스가 같을 시
		{
			c.data[cc].row = a.data[ca].row;	// 덧셈은 a와 b를 더한 값을 value에 넣어야 하므로 통째로 카피는 불가능
			c.data[cc].col = a.data[ca].col;	// c 행렬의 row,col을 넣어주고
			c.data[cc++].value = a.data[ca++].value + b.data[cb++].value; // c행렬의 값에 a,b행렬의 덧셈값을 넣어줌
		}
		else
		{
			c.data[cc++] = b.data[cb++]; 
		}
	}

	for (; ca < a.terms; ca++)		//만약 위에서  b가 먼저 모든 값에 대해서 카피가 끝난다면 a가 남아있음
	{
		c.data[cc++] = a.data[ca++];	// a 행렬을 c행렬의 남은 인덱스에 다 넣어줌
	}
	for (; cb < b.terms; cb++)		// 만약 위에서 a가 먼저 모든 값에 대해서 카피가 끝났다면 b가 남아있음
	{
		c.data[cc++] = b.data[cb++];	// b행렬을 c행렬의 남은 인덱스에 다 넣어줌
	}
	c.terms = cc;					//모든 과정이 끝나면 현재 cc가 가리키고 있는 인덱스가 c행렬의 수가 됨
	return c;
}


/*
int main()
{
	SparseMatrix m1 = { { {1,1,5}, {1,2,7} ,{2,0,13} ,{2,2,9} }, 3,3,4 }; // 인덱스 순에 맞는 행렬, 행, 열, 항의 수
	SparseMatrix m2 = { {{0,0,5} ,{2,2,9}},3,3,2 }; 
	SparseMatrix m3;
	m3 = sparse_matrix_add2(m1, m2);
	
	for (int i = 0; i < m3.terms; i++)
		printf("[%d][%d] %d\n",m3.data[i].row,m3.data[i].col ,m3.data[i].value);

}
*/