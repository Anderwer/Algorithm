练习：写一个函数能交换两个整型变量的内容(含指针变量赋值)
解：
#include<stdio.h>
void swap(int* px, int* py)
{
	int tmp = 0;
	tmp = *px;
	*px = *py;
	*py = tmp;
}
int main()
{
	int a = 10;
	int b = 20;
	printf("a=%d b=%d\n", a, b);
	swap(&a, &b);
	printf("a=%d b=%d\n", a, b);
	return 0;
}

注意：实参和形参分别占有不同的内存块，对形参的修改不会改变形参
          所以在交换时的本质是先把实参的内存地址传给函数，函数对内存地址进行交换操作

练习：用函数判断100-200之间的素数
解：
#include<stdio.h>
#include<math.h>
int is_prime(int x)
{
	int n = 0;
	for (n = 2; n <= sqrt(x); n++)
	{
		if (x % n == 0)
			return 0;
	}
	return 1;
}
int main()
{
	int i = 0;
	for (i = 100; i <= 200; i++)
	{
		is_prime(i);
		if (1 == is_prime(i))
			printf("%d ", i);
	}
}


练习：用函数打印1000-2000年的闰年
解：

#include<stdio.h>
int is_leap_year(int x)
{
	if (x % 4 == 0 && x % 100 != 0 || x % 400 == 0)
		return 1;
	else
		return 0;
}
int main()
{
	int year = 0;
	for (year = 1000; year <= 2000; year++)
	{
		if (1 == is_leap_year(year))
		{
			printf("%d ", year);
		}
	}
	return 0;
}


练习：写一个函数实现整形有序数组的二分查找
解：
#include<stdio.h>
int search(int arr[], int x, int size)
{
	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (x < arr[mid])
			right = mid - 1;
		else if (x > arr[mid])
			left = mid + 1;
		else
		{
			return mid;
			break;
		}
	}
}
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
	int k;
	int size = sizeof(arr) / sizeof(arr[0]);
	printf("请输入要查找的数>:");
	scanf_s("%d", &k);
	printf("元素所在数组下标为%d", search(arr,k,size));
	return 0;
}

