/*
solution 1:使用归并排序:多路归并。  （数据量大的时候，还是需要耗费一定的时间）
关键字：外部排序(内存容量无法支撑数据容量) /磁盘排序 (外部排序还是会利用到内部排序)。  外部排序：内部排序 + 使用归并：多路归并。
当数据量大到不适合在内存中排序时，利用磁盘进行排序的多路归并算法。
文件指针指向磁盘的文件，并不是整个文件都load到内存了，只有读取存储到内存上才是load内存。
比如我们每次从文件指针中读取一个值存到变量，那么这个值才是load到内存(那个变量)。 每次读取，都是从硬盘到内存(文件中的数据到变量上)。


模拟数据：N <= 10^7。最多有N条数据。每条数据<=N。 内存1MB。每个数据用int存储(4Byte) int 的max为2^32 > 10^7。
所以内存能存储最多为 COUNT = 1M*8/4*8=2^18 = 262144条数据。  最多需要做 10^7 / 262144 = 39次。



1.从原始文件中每次读取COUNT条数据。 排序。 输出到文件1。(共39个文件)
2.构造int data[39] , 从39文件中各自读取一个数据到data。
3.从data中读取最小数据 存入 输出文件。 并从该数据关联的file中读入一个数据补充。 再回到2。 知道data中没有值了。

1-3瓶颈在于排序。 数据量大的时候，快排和选择排序差的不是一点半点。

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "../commonAlg/mysort.h"

int fileCount = 0;

void divData2File()
{
	//1MB 内存。每个数据int。 每次总共count条数据。 
	int	count = MEMORY / sizeof(int); 

	int *sortArr = (int*)malloc(count*sizeof(int));

	FILE* fp = fopen(DATAFILE,"r");
	while(!feof(fp))
	{
		fileCount++;
		int i = 0;
		while( !feof(fp)  && i < count)
		{
			fscanf(fp,"%d",&sortArr[i]);
			i++;
		}
        //两者速度也差太多了吧。
		//selectSort(sortArr, i);
        quickSort(sortArr, 0, i -1);
        
        //char tempFileName[10] = "data";
		//strcat(tempFileName,'0' + fileCount); 
		char tempFileName[20];
		sprintf(tempFileName,"test/data_%d.txt",fileCount);
		FILE * fout = fopen(tempFileName,"w+");
		for(int j = 0; j < i; j++)
		{
			fprintf(fout, "%d ", sortArr[j]);
		}
		fclose(fout);
	}

	fclose(fp);

	if(sortArr)
	{
		free(sortArr);
		sortArr = NULL;
    }
}

int main()
{

    
    time_t start, end;
    start = time(NULL);
	//大文件拆分小文件。 小文件是拍完序的。
	divData2File();
    end = time(NULL);
    
    printf("divData2File cost %ld s\n",end - start);
    start = end;
    
	FILE ** fileArr = (FILE**)malloc(sizeof(FILE*) * fileCount);

    for (int i = 0; i < fileCount; i++)
    {
        char fileName[20];
        sprintf(fileName, "test/data_%d.txt",i+1);
        fileArr[i] = fopen(fileName, "r");
        
    }
    
	//数组。存储每个文件中的第一数据.
	int *firstData = (int *)malloc(sizeof(int)* fileCount);

	for(int i = 0; i < fileCount; i++)
	{
		fscanf(fileArr[i], "%d",&firstData[i]);
	}

	//多路归并
	FILE * fout = fopen(RESULTFILE, "w+");
	while(1)
	{
		int minIdx = 0;
		for(int i = 0; i < fileCount; i++)
		{
			if(firstData[minIdx] > firstData[i])
				minIdx = i;
		}
		if(firstData[minIdx] == MAX + 1)
			break;

		fprintf(fout, "%d ", firstData[minIdx]);
		firstData[minIdx] = MAX + 1;
		if(!feof(fileArr[minIdx]))
			fscanf(fileArr[minIdx],"%d",&firstData[minIdx]);
	}

	if(firstData)
	{
		free(firstData);
		firstData = NULL;
	}

	for(int i = 0; i < fileCount; i++)
	{
		fclose(fileArr[i]);
	}

	if(fileArr)
	{
		free(fileArr);
		fileArr = NULL;
	}
	
    end = time(NULL);
    printf("多路归并 cost %ld s\n",end - start);

    
	return 0;
}