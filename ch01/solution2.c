/*
solution 2:利用不数据不重复这个特性。

模拟数据：N <= 10^7。最多有N条数据。每条数据<=N。 内存1MB。每个数据用int存储(4Byte)。
所以内存能存储最多为 COUNT = 1M*8/4*8=2^18 = 262144条数据。  最多需要做 10^7 / 262144 = 39次。

利用数据都不重复特性。 需要做39次。 
1.每次读取数据文件，将数据范围在COUNT*(i -1) ~ COUNT* i load到内存。
2.排序，输出到目标文件。再次读取数据文件，返回1。 次数达到39次结束算法。


缺点是： 要多次读取文件。
多次读取大文件，也耗费很多时间。

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"

int main()
{

	time_t start, end;

	start = time(NULL);

	//1MB 内存。每个数据int。 每次总共count条数据。 
	int	count = MEMORY / sizeof(int);
    
    printf("count %d\n",count); //262144

	int *sortArr = (int*)malloc(count*sizeof(int));


	int fileTimes = MAX / count + 1;
	
	printf("fileTimes %d\n",fileTimes);
	FILE * fp = fopen(DATAFILE, "r");
	FILE * fpout = fopen(RESULTFILE, "w+");

	int data;
	int arrNum;
	for(int i = 0; i < fileTimes; i++)
	{
		fseek(fp, 0 , SEEK_SET);
		arrNum = 0;
		while(!feof(fp))
		{
			fscanf(fp, "%d",&data);
			if(data> i*count && data <= (i+1)*count)
				sortArr[arrNum++] = data;
		}
		printf("arrNum %d\n", arrNum);
		quickSort(sortArr, 0, arrNum -1);


		for(int j = 0; j < arrNum; j++)
		{
			fprintf(fpout, "%d ", sortArr[j]);
		}
	}

	fclose(fp);
	fclose(fpout);

	if(sortArr)
	{
		free(sortArr);
		sortArr = NULL;
	}

	end = time(NULL);

	printf("%ld\n",end - start);

	return 0;
}