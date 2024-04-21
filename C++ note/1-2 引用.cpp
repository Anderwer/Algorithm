一.引用
1.引用的用法
void func(int &a)
{
    a = 200;
}
void test()
{
    int a = 10;
    func(a);
    cout << "a = " << a << endl;//结果打印200
}
//引用和指针类似，比指针更方便简洁

 引用的注意:
 注意1:int &b = a;这里的&不是取地址操作符,而是引用的标记作用
 注意2:引用创建时必须要初始化
 注意3:引用一旦初始化不能改变它的指向
 注意4:引用必须引用一块合法的空间

2.数组的引用
int main()
{
    int arr[] = {1,2,3,4,5};
    //第一种方法
    //1.定义数组类型
    typedef int(MY_ARR)[5];//数组类型
    //2.建立引用
    MY_ARR &arref = arr;//建立引用

    //第二种方法(最常用)
    //直接定义引用
    int(&arref)[5] = arr;

    //第三种方法
    typedef int(MY_ARR)[5];//建立引用数组类型
    MY_ARR arref = arr;

    return EXIT_SUCCESS;
}

3.指针的引用
指针的引用相当于给指针变量这块空间取别名
void test01()
{
	char* p = "翠花";//类似于  int a = 10;
	char*& p1 = p;   //       int &b = a;
	cout << p1 << endl;//     cout << b << endl;
}
int main()
{
	test01();
	return EXIT_SUCCESS;
}


void func(char* &tmp)
{
	char* s = nullptr;
	s = (char*)malloc(64);
	memset(s, 0, 64);
	strcpy(s, "小花");
	tmp = s;
}
void test02()
{
	char* p = nullptr;
	func(p);
	cout << p << endl;
}
int main()
{
	test02();
	return EXIT_SUCCESS;
}

二.内联函数
1.什么是内联函数
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

inline int Add(int x, int y)//在普通函数前面加上inline是向编译器申请成为内联函数,效率更高
{                           //注意:加了inline可能成为内联函数,也可能不成为
	return x + y;
}
void test01()
{
	int ref = Add(10, 20) * 2;
	cout << ref << endl;
}
int main()
{
	test01();
	return EXIT_SUCCESS;
}

2.什么情况不会成为内联函数
(1).存在过多的条件判断语句
(2).存在任意循环语句
(3).函数体过大
(4).对函数进行取址操作

3.内联函数的好处
(1).有宏函数的效率,没有宏函数的缺点
(2).类的成员函数默认加上inline

--------------------------------------------------------------------------------------------

三.函数的默认参数
1.函数的默认参数就是给函数的形参赋值

int func(int a, int b = 0)//int b = 0;这就是默认参数
{
	return a + b;
}
void test01()
{
	cout << func(10, 0) << endl;
	cout << func(10) << endl;//可以增加函数的灵活性
}
int main()
{
	test01();
	return EXIT_SUCCESS;
}

2.函数的默认参数的注意事项
注意1:函数的默认参数后面的参数必须都是默认参数
int func(int a,int b = 0,int c = 1,int d = 2)
{
    return a + b + c + d;
}

注意2:函数的声明和实现不能同时有函数的默认参数
void func(int a,int b = 0);//声明
void func(int a,int b = 0)//定义
{

}//这样写会报错:重定义默认参数
需要把声明改成void func(int a,int b);

------------------------------------------------------------------------------------------------

四.函数重载
1.函数重载的目的是为了方便的使用函数名,允许函数名相同

int add(int a,int b) {return a + b;}

int add(double a,double b) {return a + b;}

2.实现函数重载的条件
(1).同一个作用域
(2).参数的个数不同
(3).参数的类型不同
(4).参数顺序不同

3.调用重载函数的注意: 严格的类型匹配,如果类型不匹配,那么将尝试类型转换,转换成功就调用,转换失败就报错

------------------------------------------------------------------------------------------------

五.C++如何调用C语言
在头文件中要这样写:
#pragma once

#include<stdio.h>
//这是告诉C++编译器,找下面的函数,要以C语言的方式去找
#ifdef __cplusplus
extern "C"
{
#endif
    void func();//C语言的函数声明


#ifdef __cplusplus
}
#endif

----------------------------------------------------------------------------------------------