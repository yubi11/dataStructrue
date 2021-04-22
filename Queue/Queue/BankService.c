#include <stdio.h>
#include <Stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef struct elementB
{
	int id;
	int arrival_time;
	int service_time;

}elementB;

typedef struct QueueTypeB
{
	elementB data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueTypeB;

void errorB(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queueB(QueueTypeB* q)
{
	q->front = q->rear = 0;				//환형 큐는 선형 큐와 달리 0부터 시작함, 초기에 인덱스 0부분은 비워진상태로 큐가 채워짐, 즉 배열사이즈 -1 만큼 저장가능
}

int is_emptyB(QueueTypeB* q)
{
	return (q->front == q->rear);		// 선형큐와 마찬가지로 front와 rear가 같으면 공백상태임
}

int is_fullB(QueueTypeB* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);		// 큐의 마지막인덱스+1 을 큐사이즈로 나누고, 그 나머지 값을 front와 비교 
}

void enqueueB(QueueTypeB* q, elementB item)
{
	if (is_fullB(q))
		errorB("큐가 포화상태.\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;				// rear는 +1 하고 큐 사이즈로 나눈 나머지값이 된다.
	q->data[q->rear] = item;								// 그리고 그 인덱스에 값을 넣게 됨, 요소를 넣기 전에 인덱스를 1올리고, 값을 일정범위로 유지하는 셈
}

elementB dequeueB(QueueTypeB* q)
{
	if (is_emptyB(q))
		errorC("큐가 공백\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;				// dequeue 할 시, 바로 해당 인덱스를 pop하는 것이아니라,
	return q->data[q->front];								// front에 1을 올리고 큐 사이즈로 나눈 나머지값을 채택 한 후, 그 인덱스 값을 반환한다.
}

int main(void)
{
	int minutes = 60;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	QueueTypeB queue;
	init_queueB(&queue);

	srand(time(NULL));
	for (int clock = 0; clock < minutes; clock++)
	{
		printf("현재시각 =%d\n", clock);
		if( ( rand()%10) < 3)
		{
			elementB customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueueB(&queue, customer);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n", customer.id, customer.arrival_time, customer.service_time);
		}
		if(service_time>0)
		{
			printf("고객 %d 업무처리중입니다.\n", service_customer);
			service_time--;
		}
		else
		{
			if (!is_emptyB(&queue))
			{
				elementB customer = dequeueB(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);	
			}

		}
	
	}
	printf("전체 대기 시간= %d분\n", total_wait);
	return 0;
}