#include <stdio.h>

void HanoiTower(int n,char from,char temp,char to)
{
	if(n==1)
		printf("원판 1을 %c에서 %c로 옮긴다\n",from,to); //	A -> C		막을게 없으니 목표로 이동
	else
	{
		HanoiTower(n - 1, from, to, temp);	// (ACB) A에서 B로			현재 자기위에 있는 원판을 temp로 치워서 움직일 수 있게한다. 
		printf("원판 %d를 %c에서 %c로 옮긴다\n", n,from, to); // A -> C	자기 원판을 목표 위치에 이동시킨다.
		HanoiTower(n - 1, temp, from, to); // (BAC)						자기위에 있었던 원판을 자기 위에 이동 시킨다. 
	}

}
// (2^n)-1 번 실행됨


void HanoiTower4(int n, char from, char temp1, char temp2, char to)
{
	if (n == 1)
		printf("원판1을 %c에서 %c로 옮긴다.\n", from, to);			// 막을게 없으니 목표로 이동
	else if (n == 2)
	{
		printf("원판 1을 %c에서 %c로 옮긴다.\n", from, temp1);		// 원판 2 기준으로, 자기 위에 있는 원판을 temp로 이동시킨다
		printf("원판 2를 %c에서 %c로 옮긴다.\n", from, to);			// 자기는 목표로 이동한다.
		printf("원판 1을 %c에서 %c로 옮긴다.\n", temp1, to);			// 자기 위에 있던 원판을 다시 자기 위로 이동시킨다.
	}
	else
	{
		HanoiTower4(n - 2, from, temp2, to, temp1);						// 움직이려는 원판 기준으로부터 2칸 위에있는 원판을 temp1으로 움직인다.
		printf("원판 %d를 %c에서 %c로 옮긴다.\n", n - 1, from, temp2);	// 움직이려는 원판 기준으로부터 1칸 위에있는 원판을 temp2로 움직인다.
		printf("원판 %d를 %c에서 %c로 옮긴다.\n", n, from, to);			// 자기는 이동 가능하니 목표로 이동한다.
		printf("원판 %d를 %c에서 %c로 옮긴다.\n", n - 1, temp2,to);		// 바로 위에 있던 원판을 자기 위로 올린다.
		HanoiTower4(n - 2, temp1, from, temp2, to);						// 움직이려는 원판 기준으로부터 2칸 위에있던 원판을 목표로 움직인다. 
	}
}


/*
int main()
{
	HanoiTower(3, 'A', 'B', 'C');

	printf("끝\n");

	HanoiTower4(4, 'A', 'B', 'C', 'D');

	printf("끝\n");
	return 0;
}
*/