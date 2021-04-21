#include <stdio.h>

int bc(int n, int k) 
{
	if (k > n)
		return -1;
	if (k == 0) 
		return 1;
	if (k == n) 
		return 1;

	return bc(n - 1, k - 1) + bc(n - 1, k);
}
// 시간복잡도 O(2^n)


int main()
{
	printf("%d", bc(5,3));


}


//순환 계산 시, 재귀 호출 1번만 사용이 되고, 인수가 등비로 감소할 때는 O(log n)
//순환 계산 시, 재귀 호출 1번만 사용이 되고, 인수가 등차로 감소할 떄는 O(n)
//순환 계산 시, 재귀호출 2회 이상 사용이 되고, 인수가 등비로 감소할 때는 O(n logy x) y = 등비, x = 호출 수, 호출 수와 등비가 같다면 선형 복잡도 가짐
//순환 계산 시, 재귀호출 2회 이상 사용이 되고, 인수가 등차로 감소할 때는 O(2^n)