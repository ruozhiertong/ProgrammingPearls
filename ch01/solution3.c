/*
利用bitmap/位图进行处理。

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"


//int  4字节。 每个int表示32位。
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F

int a[MAX/BITSPERWORD + 1];

void setBit(int i)
{
	a[i >> SHIFT] |= 1 << (i & MASK);
}

void clsBit(int i)
{
	a[i >> SHIFT] &= ~(1 << (i & MASK));
}

void clearAllBit()
{
	for(int i = 0 ; i <= MAX; i++)
		clsBit(i);
}

int testBit(int i)
{
	return a[i >>SHIFT] & (1 << (i & MASK)) == 0? 0:1;
}

//注意由于 10^7 大于 1M*8 的bit位数。 所有要2趟算法。读两次文件。
/*
不过很快，我们就将意识到，用此位图方法，严格说来还是不太行，空间消耗10^7/8还是大于1M（1M=1024*1024空间，小于10^7/8）。

既然如果用位图方案的话，我们需要约1.25MB（若每条记录是8位的正整数的话，则10000000/(1024*1024*8) ~= 1.2M）的空间，而现在只有1MB的可用存储空间，那么究竟该作何处理呢？可以多次使用位图进行排序。

假如严格限制为1MB，可以采用的策略：两次遍历或者除去第一位为0或1的整数。
解释：考虑到没有以数字0或1开头的电话号码，可以省略对这些数的操作。
两次遍历：对 1 ---4999 999之间的数排序，需要存储空间为：5000 000/8 =625 000 字节（8为一个字节中的位数）
　　　　   对 5000 000 -10000 000 之间的数排序。
如果需要采用k趟算法，方法类似。

*/

int main()
{

	time_t start ,end;

	start = time(NULL);

	FILE * fp = fopen(DATAFILE, "r");

	FILE * fpout = fopen(RESULTFILE, "w+");

	int times = 2;

	int MAX_ONE = MAX /times;


	int data;

	for(int i = 1; i <= times; i++)
	{
		fseek(fp, 0, SEEK_SET);    

		clearAllBit();
		while(!feof(fp))
		{
			fscanf(fp,"%d",&data);
			if(data > (i-1)*MAX_ONE && data <= MAX_ONE *i) // [1,MAX_ONE]
			{
				setBit(data - MAX_ONE * (i-1));
			}
		}

		for(int j = 1 ; j <= MAX_ONE; j++)
		{
			if(testBit(j))
			{
				fprintf(fpout, "%d ", j + MAX_ONE*(i-1));
			}
		}
	}

	fclose(fp);
	fclose(fpout);


	end = time(NULL);

	printf("const %ld s\n", end - start);

	return 0;
}