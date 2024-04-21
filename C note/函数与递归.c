递归

最简单的递归
 #include<stdio.h>
int main()
{
	printf("hello world\n");
	main();
	return 0;
}

注意：该程序会发生栈溢出，递归容易栈溢出
解释

栈区存有：局部变量，函数形参

堆区存有：动态开辟的内存，malloc,calloc

静态区存有：全局变量，static修饰的变量

当程序递归时，不断占用栈区空间，直到stack overflow报错


练习：接受一个整形值(无符号)，按照它的顺序打印它的每一位。例如：输入1234，输出1 2 3 4
解：
#include<stdio.h>
void one_print(int x)
{
	if (x > 9)
	{
		one_print(x / 10);
	}
	printf("%d ", x % 10);
}
int main()
{
	unsigned int a;
	scanf_s("%d", &a);
	one_print(a);
	return 0;
}

由此得出：运用递归的条件
1.存在限制条件，当满足这个限制条件的时候，递归便不再继续
2.每次递归调用之后越来越接近这个限制条件.


练习：不创建临时变量，计算字符串长度(不使用strlen函数)

方法1：自己编写strlen函数(创建临时变量)
解:
#include<stdio.h>
int my_strlen(char* arr)
{
	int count = 0;
	while(*arr != '\0')
	{
		count++;
		arr++;
	}
	return count;
}
int main()
{
	char arr[] = "hello world";
	int length = my_strlen(arr);
	printf("length = %d", length);
	return 0;
}

方法2：利用递归且不创建临时变量实现strlen函数
解：
#include<stdio.h>
int my_strlen(char* arr)
{
	if (*arr != '\0')
		return 1 + my_strlen(arr + 1);
	else
		return 0;
}
int main()
{
	char arr[] = "hello world";
	printf("length = %d", my_strlen(arr));
	return 0;
}

练习：使用递归计算第n个斐波那契数
#include<stdio.h>
int Fib(int x)
{
	if (x > 2)
		return Fib(x - 1) + Fib(x - 2);
	else
		return 1;
}
int main()
{
	int input = 0;
	scanf_s("%d", &input);
	printf("%d\n",Fib(input));
	return 0;
}

练习：使用迭代计算第n个斐波那契数

#include<stdio.h>
int Fib(int x)
{
	int a = 1;
	int b = 1;
	int c = 1;
	while (x > 2)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}
int main()
{
	int input = 0;
	scanf_s("%d", &input);
	printf("%d\n",Fib(input));
	return 0;
}












































