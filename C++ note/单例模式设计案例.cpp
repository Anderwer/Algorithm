#include<iostream>
#include<string>
using namespace std;

class Printer
{
public:
	static Printer* getptr() {
		if (p == nullptr) p = new Printer;
		return p;
	}
	void countPrinter(string name) {
		cout << name << "部门:打印" << endl;
		count++;
	}
	int getCount() {
		return count;
	}
private:
	Printer()
	{
		count = 0;
	}
	Printer(const Printer &P) {}
	~Printer() {}
	static Printer* p;
	int count;
};
Printer* Printer::p = nullptr;//初始化

void test()
{
	Printer* p1 = Printer::getptr();
	for (int i = 1; i <= 4; i++) p1->countPrinter("公关部");
	Printer* p2 = Printer::getptr();
	for (int i = 1; i <= 5; i++) p1->countPrinter("销售部");
	Printer* p3 = Printer::getptr();
	for (int i = 1; i <= 8; i++) p1->countPrinter("技术部");
	Printer* p4 = Printer::getptr();
	cout << p4->getCount() << endl;
}

int main()
{
	test();
	return EXIT_SUCCESS;
}