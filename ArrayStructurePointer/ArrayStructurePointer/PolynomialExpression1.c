#include <stdio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))		// 크기가 더 큰 변수 고르기
#define MAX_DEGREE 101						// 최고 차항 101


// 다항식 구조체가 최고차수 변수와 각 차수의 계수를 배열로 가지고 있는 식
// 다항식의 연산이 간단하나, 대부분의 항의 계수가 0이면 공간 낭비가 심함

typedef struct 
{
	int degree;						// 다항식의 최고차수
	float coef[MAX_DEGREE];			// 각 차수마다 들어갈 계수들
} polynomial;


polynomial poly_add1(polynomial A, polynomial B)
{
	polynomial C;						// 다항식 C선언
	int Apos = 0, Bpos = 0, Cpos = 0;	// 더해줄 A,B 다항식의 iterator 지정
	int degree_a = A.degree;			// A의 최고차수
	int degree_b = B.degree;			// B의 최고차수
	C.degree = MAX(A.degree, B.degree);	// A,B 둘 중 최고차수가 높은 것을 C의 최고차수로 지정
	while (Apos <= A.degree && Bpos <= B.degree)	// 각 다항식의 iterator가 최고차수가 될 때까지 진행됨
	{
		if (degree_a > degree_b)				// 현재 a의 최고차수가 b보다 높다면
		{
			C.coef[Cpos++] = A.coef[Apos++];	// C의 iterator로 해당 차수의 계수에 A의 계수 삽입
			degree_a--;							// A의 차수 1개는 이미 처리를 했으므로 마이너스
		}
		else if (degree_a == degree_b)			// 현재 A와 B의 차수가 동일 하다면
		{
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];	// C의 iterator로 해당 차수에 접근하여 A와 B의 계수를 더해줌
			degree_a--;											// A의 차수는 하나 줄어야됨
			degree_b--;											// B 또한 마찬가지
		}
		else
		{											// 현재 B가 A의 차수보다 높은 경우
			C.coef[Cpos++] = B.coef[Bpos++];		// C의 iteartor로 해당 차수에 접근하여 B의 계수를 더해줌
			degree_b--;								// B의 차수를 줄여야 됨
		}
	}
	return C;
}


/*
int main()
{
	polynomial a = { 5,{3,6,0,0,0,10} };
	polynomial b = { 4,{7,0,5,0,1} };
	polynomial c;
	c = poly_add1(a, b);
	printf("최고차수 :%d\n", c.degree);
	for (int i = 0; i <= c.degree; i++)
	{
		if(i!=c.degree && c.coef[i]!=0)
			printf("%.0fx^%d + ", c.coef[i],c.degree-i);
		else if(c.coef[i] !=0)
			printf("%.0f", c.coef[i]);
	}
}
*/