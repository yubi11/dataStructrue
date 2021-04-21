#include <stdio.h>
#include <stdlib.h>

struct Example {
	int number;
	char name[10];
};

/*
int main()
{
	struct Example* p;
	
	p = (struct Example *) malloc (2*sizeof(struct Example));
	if(p==NULL)
	{
		fprintf(stderr,"메모리 할당 실패");
		exit(1);
	}

	p->number = 1;
	strcpy(p->name,"Park");
	(p+1)->number = 2;
	strcpy((p+1)->name,"Kim");
	
	for (int i = 0; i < 2; i++)
	{
		printf("이름:%s 성적:%d\n",(p+i)->name,(p+i)->number);
	}
	free(p);

	return 0;
}
*/