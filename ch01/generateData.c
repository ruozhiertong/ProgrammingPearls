/**
生产DATANUM个数据。DATANUM <= MAX。
每个数据值<= MAX， 且不重复。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"


//int存储就可以。 10^7 < 2^32
int data[MAX + 1];


int main()
{
	printf("%d %d\n", MAX,DATANUM);

	//种子
	srand((unsigned)time(NULL));

	FILE * fp = fopen(DATAFILE,"w+");
	if(fp == NULL)
	{
		printf("file Erro\n");
		exit(-1);
	}

	int a;
	int count  = 0;
	while(count < DATANUM)
	{
		a = rand()%MAX + 1; //[1,MAX]
		if(data[a] == 0) //不重复
		{
			fprintf(fp, "%d ", a);
			data[a] = 1;
			count++;
		}
	}
	fclose(fp);
	return 0;
}