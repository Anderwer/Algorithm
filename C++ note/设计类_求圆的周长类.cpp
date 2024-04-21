#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//设置圆的类
class Circle
{
public:
	void setR(double r)
	{
		mR = r;
	}
	double getL()
	{
		return 2 * 3.14 * mR;
	}
public://公有权限
	double mR;//成员变量，成员属性
};

void test()
{
	//数据类型定义变量
	//类实例化对象
	Circle c;
	c.setR(100);
	cout << "圆的周长:" << c.getL() << endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}