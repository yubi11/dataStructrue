#include <stdio.h>
#define ROWS 3
#define COLS 3

//희소행렬을 이미 정해져 있는 2차원 배열로 표현한다.
// 허나 희소행렬에는 0이 많으므로 메모리 공간이 아무 값 없이 낭비 된다. 허나 간단하게 구현 가능

void sparse_matrix_add1(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS])
{
	int r, c;
	for (r = 0; r < ROWS; r++) 
	{
		for (c = 0; c < COLS; c++)
			C[r][c] = A[r][c] + B[r][c];			//배열 각 요소를 더해줌
	}
}

/*
int main()
{
	int array1[ROWS][COLS] = { {2,3,0}, {8,9,1}, {7,0,5} };
	int array2[ROWS][COLS] = { {1,0,0}, {1,0,0}, {1,0,0} };
	int array3[ROWS][COLS];

	sparse_matrix_add1(array1, array2, array3);

	for (int i = 0; i < ROWS; i++)
	{
		printf("\n");
		for (int j = 0; j < COLS; j++)
		{
			printf("%d ", array3[i][j]);
		}
	}
	return 0;
}
*/