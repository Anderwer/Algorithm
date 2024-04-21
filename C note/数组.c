练习：冒泡排序
如果数组中有10个元素，则需要9趟冒泡排序
#include<stdio.h>
void bubble_sort(int arr[],int size)
{
	int i;
	for (i = 1; i <= size - 1; i++)//规定要排序的次数
	{
		int j = 0;
		for (j = 0; j <= size - 1; j++)//每次排序对数组内进行排序
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}
int main()
{
	int k = 0;
	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
	int size = sizeof(arr) / sizeof(arr[0]);
	bubble_sort(arr,size);
	for (k = 0; k <= size - 1; k++)//遍历输出数组内容
		printf("%d ", arr[k]);
	return 0;
}

优化算法：
void bubble_sort(int arr[],int size)
{
	int i;
	for (i = 1; i <= size - 1; i++)
	{
		int j = 0,n=0;
		for (j = 0; j <= size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				n = 1;
			}
		}
		if (n == 0)
		{
			break;
		}
	}
}
注释：先定义n来确定本趟排序是有序的，若为不完全有序则n == 1;若完全有序则n == 0,此时跳出循环，说明数组已经排序完成。