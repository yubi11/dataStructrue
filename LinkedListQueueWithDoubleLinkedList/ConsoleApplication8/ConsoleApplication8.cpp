#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMOFATM 3

// 201600974 무역학과 김효훈

// 기본설명: ATM 3대가 연결리스트로 만들어진 double-edged 큐를 이루고 있음, 각 ATM마다 front와 rear를 가지고 있고, 이 front와 rear는 Client 구조체를 가리킨다.
// Client구조체는 손님들의 정보를 나타내는 데이터로서, 큐의 요소이다. 또한, 이 Client구조체는 nextPerson, prevPerson이라는 이중연결리스트 노드를 가지고 있다.
// 한마디로, 이중연결리스트노드(Client)를 요소로 하는 연결리스트로 만들어진 double-edged 큐(ATM)를 의미한다.


bool isPrime(int n)
{
	for (int i = 2; i < n; i++)		//소수를 확인하는 함수, 이따가 고객이탈 이벤트를 위해 사용됨
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

typedef struct Client {	// 큐의 요소로써 작동할 타입 
	int number;			//고객의 번호, vip여부, 소요시간을 가지는 구조체
	bool vip;
	int workTime;
	Client* nextPerson;
	Client* prevPerson;
} Client;


typedef struct {		
	Client* front, * rear;	//연결리스트로 이루어진 큐, front와 rear를 가지고 있는 점에서 double edged queue 이다.
	int time;				//손님이 ATM을 다 사용하는 시간
	int sumOfWaitedTime;	//ATM을 사용하기 위해 총 기다린 시간
	int jobsDone;			//ATM이 끝낸 업무량
	int numOfClients;		//기다리고있는 손님 수
	int sumOfvisitor;		//방문자 수
} LinkedQueueType;


bool is_empty(LinkedQueueType* q)
{
	return (q->front == NULL);		// 큐가 비었나 확인하는 함수
}

void enqueueFront(LinkedQueueType* q, Client input)				//vip용도로 만든 enqueueFront함수
{
	Client* temp = (Client*)malloc(sizeof(Client));				//저장할 노드를 동적으로 할당
	temp->number = input.number; 								// 데이터 저장
	temp->vip = input.vip;
	temp->workTime = input.workTime;
	temp->nextPerson = q->front;								// 맨앞으로 인큐하는 함수이므로, 요소의 뒷 노드를 원래 큐의 front로 지정
	temp->prevPerson = NULL;									// 앞 노드는 없으므로 NULL
	if (is_empty(q))
	{
		q->front = temp;
		q->rear = temp;
	}
	else
	{
		q->front->prevPerson = temp;						// 만약 큐가 비지않았다면, 큐의 front에 해당하는 노드의 prev을 지금 만드는 노드로 주게됨
		q->front = temp;									// 그리고, front는 방금 생성한 노드로 준다.
	}
}

void enqueue(LinkedQueueType* q, Client input)
{
	Client* temp = (Client*)malloc(sizeof(Client));			//노드 동적 할당으로 생성
	temp->number = input.number; 							// 데이터 저장
	temp->vip = input.vip;
	temp->workTime = input.workTime;
	temp->nextPerson = NULL; 								// 평범한 enqueue는 뒷부분으로 들어오므로, next에 해당하는 노드가 없다.
	temp->prevPerson = q->rear;								// prev은 큐의 rear부분으로 지정해준다.
	if (is_empty(q)) { 										
		q->front = temp;											
		q->rear = temp;
	}
	else 
	{ 													// 큐가 공백이 아니면
		q->rear->nextPerson = temp;						// 원래 마지막에 위치하는 노드가 새 노드를 가리켜야하므로 next를 방금 생성한 노드에 지정
		q->rear = temp;									// 그리고 마지막 노드는 방금 생성한 노드가 된다.
	}

}

Client dequeue(LinkedQueueType* q)
{
	if (is_empty(q)) {									// 연결리스트이므로, full은 존재하지 않으나, empty는 존재함
		fprintf(stderr, "큐가 비어있음\n");				// 예외처리
	}
	Client* temp = q->front;							// 지워줄 데이터를 잠시 temp에 옮겨 둠
	Client data;										// temp에서 모든 데이터를 담아올 data객체 지역생성
	data.number = temp->number; 						// 데이터를 꺼낸다.
	data.vip = temp->vip;
	data.workTime = temp->workTime;
	q->front = q->front->nextPerson;					// dequeue니까 맨 앞을 빼야한다, 그러므로 front는 front의 next로 설정, 만약 next노드가 없으면 NULL로 설정됨
	if(q->front!=NULL)									// 지운 노드의 다음노드가 NULL이 아니면 어떤 값이 존재한다는 의미이므로, 이 노드의 전 노드를 NULL로 지정
		q->front->prevPerson = NULL;
	else  	// 공백 상태
		q->rear = NULL;									// dequeue를 했는데 NULL인 경우, 아예 공백인 상태이므로 rear는 NULL로 설정, front는 윗부분에서 알아서 NULL로 설정이 된다.
	free(temp); 										// 동적메모리 해제
	return data; 										// 임시 데이터 반환

}

void init_LinkedQueue(LinkedQueueType* q)
{
	for (int i = 0; i < NUMOFATM; i++)					//ATM기를 초기화하는 부분
	{													
		(q + i)->front = NULL;
		(q + i)->rear = NULL;
		(q + i)->jobsDone = 0;
		(q + i)->numOfClients = 0;
		(q + i)->sumOfvisitor = 0;
		(q + i)->sumOfWaitedTime = 0;
		(q + i)->time = 0;
	}

}


LinkedQueueType* GetLeastCrowdedATM(LinkedQueueType* q)
{
	int numOfPeople = 100;			//제일 적은 대기열을 세는 numOfPeople변수, 처음 100은 큰 의미 없다.
	int pos = 0;					//최종적으로 몇 번째 ATM이 가장 줄이 적은지 반환하는 pos변수
	int same = 0;					//사람 수가 같은지 확인하는 same변수

	int time[NUMOFATM] = { NULL };	//모든 ATM의 대기열이 같다면 난수로 처리하나, ATM 사용 중에는 해당 사람이 대기줄이 없는 것으로 판단되므로
									//그때는 난수가 아닌, ATM의 time이 0(사용중이지않은)인 곳으로 먼저 가게 하였다. 그 때 사용되는 변수다.

	for (int i = 0; i < NUMOFATM; i++)
	{
		time[i] = (q + i)->time;						//각 ATM의 사용잔여시간을 가져온다.
		if ((q + i)->numOfClients < numOfPeople)		//ATM기 별로 줄에 서있는 사람 수를 비교해가며, 어디가 가장 적은지 확인
		{
			numOfPeople = (q + i)->numOfClients;		// 가장 대기열이 짧은 곳
			pos = i;									// 해당 ATM 인덱스 저장
		}
		else if ((q + i)->numOfClients == numOfPeople)	//ATM기 별로 줄 서있는 사람이 모두 같을 시 same변수 올림
		{
			same++;
		}
	}
	if (same == NUMOFATM - 1)		//same변수가 2일 시, 즉 모든 ATM기에 서있는 사람 수가 동일 할 시, (맨처음 ATM기는 포함안되므로)
	{
		int c=0;
		for (int i = 0; i < NUMOFATM; i++) //하지만, ATM사용 중인 사람은 대기줄로 포함안되므로, 초반에 사람들이 ATM 사용중이라 기다려야 함에도 불구하고 대기열은 0이라 비워진 ATM을 두고, 그곳으로 갈 수 있음
		{									//비워진 ATM을 탐색 한다.
			if (time[i] == 0)
			{
				pos = i;
				c++;
			}
		}
		if (c == NUMOFATM)					//ATM이 모두 비워져 있을 시,
			pos =rand() %3;
	}
	return (q + pos);					//해당 ATM기의 주소 반환
}

void CheckWaitedTime(LinkedQueueType* q)
{
	for (int i = 0; i < NUMOFATM; i++)
	{
		(q + i)->sumOfWaitedTime += (q + i)->numOfClients;		// 한 ATM 대기열에 있는 사람이 5명일 시, 1분이 지나면, 총 기다린 시간은 5분 오르게 된다. 나중에 총 방문자 수로 나눌 예정
	}
}

//	디버그용 함수, 사용하면 매 분마다 ATM의 대기열을 시각화하여 볼 수 있음
void printQueue(LinkedQueueType* q)
{
	for (int i = 0; i < NUMOFATM; i++)
	{
		Client* current;
		current = (q + i)->front;
		printf("\n--------------------------\n%d번 ATM기 고객명단\t", i + 1);
		while(current!=NULL)
		{
			printf("| %d |",current->number);
			current = current->nextPerson;
		}
		printf("\n--------------------------\n");
	}
}


void Work(LinkedQueueType* q, int clock, int minutes)
{


	Client* temp = NULL;						// 큐에있는 요소들을 순회하기 위한 Client 구조체 포인터
	Client* temp2 = NULL;	
	for (int i = 0; i < NUMOFATM; i++)			//각 ATM은 다음과 같은 동작들을 한다.
	{
		if ((q + i)->time > 0)					// 작업완료잔여시간이 0이 아닐경우 계속 줄어들게 됨
		{
			(q + i)->time--;					
		}
		CheckWaitedTime(q);						// 기다린 시간 기록


		temp = (q + i)->front;					// 큐의 front로 접근하여, 맨 앞 Client구조체를 받아내고, next로 순회할 생각
		if (is_empty((q + i)))					// ATM이 비어있다면 해당 ATM은 생략
			continue;
		if ((minutes % 10) == 0)				//매 10분마다, 소수번호를 가진사람들은 나가게됨,
		{										
												//소수면, 해당 인덱스의 고객을 queue에서 삭제시킨다.
			int k = (q + i)->numOfClients;
			for (int j = 0; j<k; j++)
			{
				temp2 = temp->nextPerson;		//temp2는 temp1이 다음 값으로 나아가기 위해서 필요하다. temp가 삭제되면 스스로는 값을 참조하지 못하기 때문
				if (isPrime(temp->number))		// 소수 확인
				{
					printf("\n%d시 %d분 - %d번 고객 이탈함\n", clock, minutes, temp->number);		//소수 일시, 해당 시간에 소수 번째 고객이 나가게 되도록 출력
					if (temp->prevPerson && temp->nextPerson == NULL)							// 지워지는 Client구조체가 맨뒤에 있는경우,
					{
						(q+i)->rear = temp->prevPerson;
						temp->prevPerson->nextPerson = NULL;									// 마지막 전 노드만 next를 NULL로 지정하고 지울 노드를 free
						free(temp);
					}
					else if (temp->prevPerson == NULL)											// 전 노드가 NULL인경우, 즉 맨 앞에있는 노드가 지워질 노드라면
					{
						dequeue(q + i);															// dequeue로 해결
					}
					else if (temp->prevPerson && temp->nextPerson)								// 앞 노드와 뒷 노드 모두 건재한경우
					{
						temp->prevPerson->nextPerson = temp->nextPerson;		//해당번호만 연결 끊고 앞노드 뒷노드 이어주기
						temp->nextPerson->prevPerson = temp->prevPerson;
						free(temp);
					}
					(q+i)->numOfClients--;											//한 명 나갔으니 ATM의 기다리는 인원 -1해줌
				}																
					temp = temp2;												// temp가 temp2로 계속 다음 노드로 이동함
			}
		}


		if ((q + i)->time == 0 && !is_empty(q + i))			// ATM 대기줄이 비어있지않고, time이 0이라면, ATM기는 새로운 고객으로하여금 사용하게 해야한다.
		{
			Client firstClient = dequeue((q + i));					// 맨 앞에있는 고객을 대기열에서 삭제시키고 데이터를 출력해준다.
			(q+i)->numOfClients--;									// 한 명 줄었으니 ATM의 대기열 1명을 줄인다.
			printf("\n%d시 %d분 - %d번 고객(%d분 소요)이 %d번 ATM에서 서비스를 시작함 %s\n", clock, minutes, firstClient.number, firstClient.workTime, i + 1, firstClient.vip ? "vip고객" : "normal고객");
			(q + i)->time = firstClient.workTime;						// ATM기는 그 고객의 정보로부터 소요시간을 받는다.
			(q + i)->jobsDone++;										// 일 처리 수를 하나 늘려준다.1
		}
	}

}


void PrintLast(LinkedQueueType* q)
{
	int sumOfWaitedTime = 0;
	int sumOfJobsDone = 0;
	int sumOfwaitingClients = 0;
	int sumOfVisitor = 0;
	for (int i = 0; i < NUMOFATM; i++)
	{
		sumOfWaitedTime += (q + i)->sumOfWaitedTime;		//ATM별로 사람들이 대기열에서 기다린 시간을 총합한 값
		sumOfJobsDone += (q + i)->jobsDone;					//ATM별로 사람들이 업무를 마친 수를 총합한 값
		sumOfwaitingClients += (q + i)->numOfClients;		//ATM별로 기다리고있는 사람들의 수를 총합한 값
		sumOfVisitor += (q + i)->sumOfvisitor;				//ATM별로 방문한(줄에서있어도 포함)사람 수를 총합한 값 
	}

	printf("\n한명 당 평균적으로 %d분 기다림\n ", sumOfWaitedTime / sumOfVisitor); //모든 기다린시간/모든 방문한사람(이탈자도 포함) = 평균 기다린시간
	printf("%d명의 고객이 업무를 봤음\n", sumOfJobsDone);	//모든 일처리 수
	printf("10시 59분 기준 %d 명이 기다리고있음\n", sumOfwaitingClients);	// 기다리고있는 모든 사람의 수
}

void freeAll(LinkedQueueType* q)
{
	for (int i = 0; i < NUMOFATM; i++)									//ATM은 동적으로 할당되어있으며, 그 요소 또한 마찬가지이다.
	{																	//그러므로 요소를 모두 할당해제하고, ATM을 마지막으로 할당해제 해주어야 한다.
		if ((q + i) != NULL)
		{
			if (!is_empty((q + i)))
			{
				for (int j = 0; j < (q + i)->numOfClients; j++)
				{
					dequeue((q + i));
				}
			}
		}
	}
	free((q));

}


int main()
{
	LinkedQueueType* ATMQueue;
	ATMQueue = (LinkedQueueType*)malloc(sizeof(LinkedQueueType) * NUMOFATM); //설정한 ATM개수만큼 동적할당
	init_LinkedQueue(ATMQueue);												//초기화
	srand(time(NULL));														//난수 시드 설정

	bool hourElapsed = false;			//1시간이 지났는지 안지났는지 확인하는 bool변수 (문제에서는 오직 9시~10시 이므로 bool처리함)
	int minutes = 0;					//분 변수

	for (int i = 0; i < 119; i++)
	{
		minutes = (minutes + 1) % 60;	//minutes은 119번 올라감, 60분이지나면 다시 0으로
		if (minutes == 0)				//60분이지나면 hourElpased true(1)로변환
			hourElapsed = true;
		
		Client newOne = { minutes, (rand() % 10) == 5 ? true : false , (rand() % 9) + 2 , NULL };		// 랜덤 고객 데이터 (번호, vip여부, worktime ,nextnode)순서로 설정
		LinkedQueueType* chosenATM;							// 사람이 제일 적은 ATM을 찾아서 선택하기 위함
		chosenATM = GetLeastCrowdedATM(ATMQueue);			// 사람이 제일적은 줄 찾기

		if (newOne.vip == true)							// 랜덤 고객이 vip일 시, enqueueFront로넣음
			enqueueFront(chosenATM, newOne);			//선택된 ATM에 새로운 고객 앞으로 추가
		else										
			enqueue(chosenATM, newOne);					// vip가 아닐 시, 뒤로 추가
		chosenATM->sumOfvisitor++;						//추가 후, 방문자수, 대기열 증가시킴
		chosenATM->numOfClients++;
		Work(ATMQueue, 9 + hourElapsed, minutes);		//work함수로 ATM이 작동하게 만듬, (ATM, 1시간지났는지 안지났는지여부, 분) 매개변수로 입력
		//printQueue(ATMQueue);							//디버그용 함수, 사용하면 매 분마다 대기열이 어떻게 되는지 시각적으로 파악가능
	}
	PrintLast(ATMQueue);									// 문제에서 요구하는 사항들 출력
	
										
	freeAll(ATMQueue);										// 끝나고 모두 동적할당 해제

	return 0;
}