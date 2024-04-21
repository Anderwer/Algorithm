#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Maker
{
public:
	void Init()
	{
		name.clear();
		age = 0;
	}
	void setName(string Name)
	{
		name = Name;
	}
	string getName()
	{
		return name;
	}
	void setAge(int Age)
	{
		if(Age > 0 && Age < 120) age = Age;
	}
	int getAge()
	{
		return age;
	}
	void printName()
	{
		cout << "姓名:" << name << endl;
	}
	void printAge()
	{
		cout << "年龄:" << age << endl;
	}
private:
	string name;
	int age;
};

void test()
{
	Maker m;
	m.Init();
	m.setName("mcbwxg");
	m.setAge(21);
	m.printName();
	m.printAge();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}