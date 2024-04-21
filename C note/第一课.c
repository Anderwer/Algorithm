C语言标准形式
#include<stdio.h>
int main()
{
    
    return 0;
}

--------------------------------------------
打印hello world

#include<stdio.h>
int main()
{
    printf("hello world\n");
    return 0;
}

----------------------------------------------
数据类型
char      //字符数据类型
short    //短整型
int        //整形
long       //长整型
long long  //更长的整形
float      //单精度浮点数
double     //双精度浮点数


-------------------------------------------------------
 打印字符a

#include<stdio.h>
int main()
{    
     char ch='a';
     printf("%c\n",ch);     //%c----打印字符格式的数据
     return 0;
}

-----------------------------------------------------------
打印字符20

#include<stdio.h>
int main()
{
     int age=20;
     printf("%d\n",age);       //%d-----打印整形十进制数据
        return 0;
}

----------------------------------------------------------
打印字符10.2

#include<stdio.h>
int main()
{
	float num = 10.2;
	printf("%f\n", num);       //%f-------打印浮点型数据
	return 0;
}

----------------------------------------------------------------

查询各种数据类型的字节大小

#include<stdio.h>
int main()
{
	printf("%d\n", sizeof(char));
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(long));
	printf("%d\n", sizeof(long long));
	printf("%d\n", sizeof(short));
	printf("%d\n", sizeof(float));
	printf("%d\n", sizeof(double));
	return 0;
}

--------------------------------------------------------------
全局变量和局部变量

#include<stdio.h>
int a = 100;        //在main函数之前的为全局变量
int main()
{
	int a = 10;     //在main函数内的为局部变量
	printf("%d\n", a);
	return 0;
}                        //输出结果以局部变量优先


---------------------------------------------------------
两个数相加

#include<stdio.h>
int main()
{
	int num1 = 0;
	int num2 = 0;                //给变量的初始值设置为0
	int sum = 0;
	scanf_s("%d%d", &num1, &num2);           //&为取地址符号，取出num的值 --------scanf_s为输入函数
	sum = num1 + num2;
	printf("sum = %d\n", sum);
	return 0;
}

------------------------------------------------------------------



