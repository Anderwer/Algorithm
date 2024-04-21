#include"MyArray.hpp"
#include<string>
class Person
{
public:
	Person() {}
	Person(std::string name, int age)
	{
		this->name = name;
		this->age = age;
	}
	~Person() {}
	//打印内容
	void print()
	{
		std::cout << "name:" << name << " age:" << age << std::endl;
	}
public:
	std::string name;
	int age;
};

int main()
{
	MyArray<Person> arr(10);
	Person p1("person1", 18);
	Person p2("person2", 20);
	arr.push_back(p1);
	arr.push_back(p2);
	for (size_t i = 0; i < arr.size(); i++)
	{
		arr[i].print();
	}
	MyArray<Person> arr2(arr);
	for (size_t i = 0; i < arr2.size(); i++)
	{
		arr2[i].print();
	}
	return EXIT_SUCCESS;
}