#include <stdio.h>
#include <stdlib.h>

typedef char elementM[100];

typedef struct DlistNodeM
{
	elementM data;
	struct DlistNodeM* next;
	struct DlistNodeM* prev;
}DlistNodeM;


typedef struct DLHeader
{
	struct DlistNodeM* head;
	int size;
}DLHeader;


DLHeader* initM()
{
	DLHeader* header = (DLHeader*)malloc(sizeof(DLHeader));
	header->size = 0;
	header->head = NULL;
	return header;
}


DLHeader* insert_firstM(DLHeader* header, elementM data)
{
	DlistNodeM* input = (DlistNodeM*)malloc(sizeof(DlistNodeM));
	strcpy(input->data,data);
	if (header->head == NULL)
	{
		input->next = input;
		input->prev = input;
	}
	else
	{
		input->next = header->head;
		input->prev = header->head->prev;
		header->head->prev->next = input;
		header->head->prev = input;
	}
	header->head = input;
	header->size++;
	return header;
}

DLHeader* insert_lastM(DLHeader* header, elementM data)
{
	DlistNodeM* input = (DlistNodeM*)malloc(sizeof(DlistNodeM));
	strcpy(input->data, data);

	if (header == NULL)
	{
		input->next = input;
		input->prev = input;
	}
	else
	{
		input->next = header->head;
		input->prev = header->head->prev;
		header->head->prev->next = input;
		header->head->prev = input;
	}

	header->size++;
	return header;
}

DLHeader* insert_middleM(DLHeader* header, int pos, elementM data)
{
	if (!(pos >= 0 || pos <= header->size))
		return header;
	if (pos == 0)
	{
		DLHeader* res = insert_firstM(header, data);
		return res;
	}
	else if (pos == header->size)
	{
		DLHeader* res = insert_lastM(header, data);
		return res;
	}
	DlistNodeM* input = (DlistNodeM*)malloc(sizeof(DlistNodeM));
	if (input == NULL)
		fprintf(stderr, "메모리 할당 실패");
	strcpy(input->data, data);

	DlistNodeM* p = header->head;
	for (int i = 0; i < pos - 1; i++)
	{
		p = p->next;
	}
	DlistNodeM* q = p->next;
	p->next = input;
	q->prev = input;
	input->prev = p;
	input->next = q;

	header->size++;
}

DlistNodeM deleteFirstM(DLHeader* header)
{
	DlistNodeM dat = { header->head->data,NULL,NULL };
	DlistNodeM* p = header->head;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	header->head = p->next;
	free(p);
	header->size--;
	return dat;
}

DlistNodeM deleteLastM(DLHeader* header)
{
	DlistNodeM dat = { header->head->prev->data,NULL,NULL };
	DlistNodeM* p = header->head->prev;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	header->size--;
	return dat;
}

DlistNodeM deleteMiddleM(DLHeader* header, int pos)
{
	if (!(pos >= 0 || pos < header->size))
		return;
	if (pos == 0)
		return deleteFirstM(header);
	else if (pos == header->size - 1)
		return deleteLastM(header);

	DlistNodeM* p = header->head;
	for (int i = 0; i < pos; i++)
	{
		p = header->head->next;
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

DlistNodeM* current;


void print_listM(DLHeader* header)
{
	DlistNodeM* p = header->head;
	if (header->size ==0)
		return;
	for (; p != header->head->prev; p = p->next)
	{
		if( p == current)
			printf("#%s #|", p->data);
		else
			printf("%s |", p->data);
	}
	if(current==p)
		printf("#%s #|", p->data);
	else
		printf("%s |", p->data);
	printf("\n");
}

void freeAllM(DLHeader* header)
{
	DlistNodeM* p = header->head;
	DlistNodeM* q;
	DlistNodeM* r= header->head->prev;
	while (p != r)
	{
		if (header->size == 0)
			break;
		q = p;
		p = p->next;
		free(q);
	}
	free(header);
}

/*
int main()
{
	DLHeader* header = initM();
														//간단한 플레이 목록 인터페이스 구현
	insert_firstM(header, "Mamamia");
	insert_firstM(header, "Dancing Queen");
	insert_firstM(header, "Fernando");
	current = header->head;

	print_listM(header);
	
	char ch;
	do
	{
		printf("\n 명령어를 입력하시오 (<,>,q):");
		ch = getchar();
		if (ch == '<')
		{
			current = current->prev;
		}
		else if (ch == '>')
		{
			current = current->next;
		}
		print_listM(header);
		
		getchar();
	} 	while (ch != 'q');

	
	printf("추가 단계\n");
	for (int i = 0; i < 5; i++)
	{
		insert_firstM(header,i);
		print_listM(header);
	}
	printf("\n 삭제 단계\n");
	for (int i = 0; i < 5; i++)
	{
		deleteFirstM(header);
		print_listM(header);
	}
	
	
	freeAllM(header);
	
	return 0;
}
*/