#include <stdio.h>

// 다항식 구조체 하나가 특정 차수와 그 계수를 가지고 있고, 이를 배열로 여러개 나타낸 것
// 메모리 공간의 효율적인 이용이 가능하지만, 연산이 복잡함

#define MAX_TERMS 101

typedef struct {				//구조체 내부에는 배열이 없고, 구조체를 배열로 만들것이다.
	float coef;
	int expon;
} terms;


char compare(int a, int b)			// a,b를 비교해서 그 결과에 맞는 부호 출력
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void attach(terms* poly, int* avai, float coef, int expon)		// 다항식 배열에 새로운 차수, 계수 입력
{
	int* avail = avai;

	if (*(avail) > MAX_TERMS)
	{
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms* ply = poly;

	ply[*avail].coef = coef;
	ply[(*avail)++].expon = expon;

}

void poly_add2(terms* poly, int* avai, int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
	terms* a = poly;
	int* avail = avai;
	float tempcoef;
	*Cs = *avail;
	while ((As <= Ae) && (Bs <= Be))
	{
		switch (compare(a[As].expon, a[Bs].expon))
		{
		case '>':
			attach(a, avail, a[As].coef, a[As].expon);
			As++;
			break;

		case '=':
			tempcoef = a[As].coef + a[Bs].coef;
			if (tempcoef)
				attach(a, avail, tempcoef, a[As].expon);
			As++;
			Bs++;
			break;
		case '<':
			attach(a, avail, a[Bs].coef, a[Bs].expon);
			Bs++;
			break;
		}
	}
	for (; As <= Ae; As++)
	{
		attach(a, avail, a[As].coef, a[As].expon);
	}
	for (; Bs <= Be; Bs++)
	{
		attach(a, avail, a[Bs].coef, a[Bs].expon);
	}
	*Ce = *(avail)-1;
}

/*
int main()
{
	terms a[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };
	int avail = 6;

	int Cs, Ce;
	poly_add2(a, &avail, 0, 2, 3, 5, &Cs, &Ce);

	printf("%d,%d\n", Cs, Ce);
	for (int i = Cs; i <= Ce; i++)
		printf("%d차수:%.0f ", a[i].expon, a[i].coef);
	return 0;
}
*/
