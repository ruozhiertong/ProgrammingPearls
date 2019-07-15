#include "mysort.h"

//太慢了
void selectSort(int *arr, int size)
{
	for(int i = 0; i < size; i++)
	{
		int minIdx = i;
		for(int j = i +1; j < size; j++)
		{
			if(arr[j] < arr[minIdx])
                minIdx = j;
		}
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
	}
}

void swap(int *x , int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int * arr, int low, int high)
{
    if(low >= high)
        return low;
    
    int tmp = arr[low];
    while(low < high)
    {
        while(arr[low] < tmp)
            low++;
        while(arr[high] > tmp )
            high--;
        if(low < high)
        {
            swap(&arr[low], &arr[high]);
            low++;
        }
    }
    
    return low;
}

//快排
void quickSort(int * arr, int low, int high)
{
    if(low >= high)
        return;
    
    int mid = partition(arr, low, high);
    
    quickSort(arr, low, mid -1); //注意
    
    quickSort(arr, mid + 1,high);
    
}