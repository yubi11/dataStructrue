#include <stdio.h>

int factorialRec(int n)
{
	if (n <= 1)
		return 1;

	return n*factorialRec(n - 1);
}
// 시간복잡도 O(n)

int factorialFor(int n)
{
	int res=1;
	for (int i = 1; i <= n; i++) 
	{
		res *= i;
	}
	return res;
}
// 시간복잡도 O(n)

/*
int main()
{
	printf("%f\n", SlowPower(5, 3));
	printf("%f\n", FastPower(5, 3));
	return 0;
}
*/