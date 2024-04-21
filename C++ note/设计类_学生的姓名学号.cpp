#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Students
{
public:
	void setName(string Name)
	{
		name = Name;
	}
	void setID(int ID)
	{
		id = ID;
	}
	void myprint()
	{
		cout << "姓名:" << name << "\n学号:" << id << endl;
	}
private:
	string name;
	int id;
};

void test()
{
	Students s;
	s.setName("mcbwxg");
	s.setID(1);
	s.myprint();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}