#include<stdio.h>
int main()
{
    int a = 10;
    int *p = &a; //*p是指针变量
    return 0;
}


指针类型：和原类型相同
#include<stdio.h>
int main()
{
    int a = 0x11223344;
    int *p = &a;
    *p = 0;
    printf("%d",a);
    return 0;
}
结果打印a---->0
若指针类型和原类型不同
#include<stdio.h>
int main()
{
    int a = 0x11223344;
    char *p = &a;
    *p = 0;
    printf("%d",a);
    return 0;
}
则解引用时只会改变四个字节中的一个字节(char类型只有一个字节)  则改变后的a为0x11223300  
因此：指针类型决定了指针进行解引用操作时能够访问的空间的大小


避免野指针

1.指针初始化
int a = 10;
int* p = &a;//指针初始化

2.定义空指针
int* p = NULL;

3.小心指针越界

指针运算

1.指针加减整数运算
  p++   p--

2.指针减指针运算
int a[10] ={0,1,2,3,4,5,6,7,8,9}
printf("%d",&a[9]-&a[0]);   //结果打印9
说明指针相减能得到两指针中间的元素个数

实用：利用指针减指针运算写一个strlen函数
解：
#include<stdio.h>
int my_strlen(char* str)
{
	char* start = str;
	char* end = str;
	while (*end != '\0')
		end++;
	return end - start;
}
int main()
{
	char a[] = "hello";
	printf("%d",my_strlen(a));
	return 0;
}
3.指针的关系运算
即指针之间的比较大小

指针和数组
#include<stdio.h>
int main()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = arr;
	return 0;
}
指针可以访问数组

二级指针
#include<stdio.h>
int main()
{
	int a = 10;
	int* pa = &a;//一级指针
	int** ppa = &pa;//二级指针
	return 0;
}
















