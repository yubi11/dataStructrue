// 거듭제곱은 순환적인 방법이 더 효율적이다
#include <stdio.h>

double SlowPower(double x, int n)
{
	int i;
	double res = 1.0;
	for (int i = 0; i < n; i++)
	{
		res *= x;
	}
	return res;
}
// for문으로 구현하므로 O(n)의 시간복잡도를 가짐

double FastPower(double x, int n)
{
	if (n == 0)
		return 1;

	if (n % 2 == 0)
		return FastPower(x*x,n/2);
	else
		return x*FastPower(x*x,(n-1)/2);
	
}
// 횟수가 반씩 줄어들기 때문에 O(logn)의 시간복잡도를 가지게됨


/*
int main()
{
	printf("%f\n", SlowPower(5,3));
	printf("%f\n", FastPower(5, 3));
	return 0;
}
*/