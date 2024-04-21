#include<iostream>
#include<string>

class Animal//创建抽象类
{
public:
	virtual void speak() = 0;
	virtual int getnum() = 0;
};

//鸭子
class Duck :public Animal
{
public:
	Duck(std::string t, int n)
	{
		type = t;
		num = n;
	}
	virtual void speak()
	{
		std::cout << "类型:" << type << " 数量:" << num << std::endl;
	}
	virtual int getnum()
	{
		return num;
	}
public:
	std::string type;//动物类型
	int num;//动物数量
};

//老虎
class Tiger :public Animal
{
public:
	Tiger(std::string t, int n)
	{
		type = t;
		num = n;
	}
	virtual void speak()
	{
		std::cout << "类型:" << type << " 数量:" << num << std::endl;
	}
	virtual int getnum()
	{
		return num;
	}
public:
	std::string type;//动物类型
	int num;//动物数量
};

//狗
class Dog :public Animal
{
public:
	Dog(std::string t, int n)
	{
		type = t;
		num = n;
	}
	virtual void speak()
	{
		std::cout << "类型:" << type << " 数量:" << num << std::endl;
	}
	virtual int getnum()
	{
		return num;
	}
public:
	std::string type;//动物类型
	int num;//动物数量
};

class Zoo //创建基类
{
public:
	Zoo()
	{
		mCapacity = 1024;
		mSize = 0;
		p = new Animal*[mCapacity];
	}
	~Zoo()
	{
		for (int i = 0; i < mCapacity; i++)//释放
		{
			if (p[i]) {
				delete p[i];
				p[i] = nullptr;
			}
		}
		delete[] p;
		p = nullptr;
	}
	int AddAnimal(Animal* animal)
	{
		if (mCapacity == mSize) return -1;
		p[mSize++] = animal;
		return 0;
	}
	void Speak()
	{
		for (int i = 0; i < mSize; i++)
		{
			p[i]->speak();
		}
	}
	void getNum()
	{
		int sum = 0;
		for (int i = 0; i < mSize; i++)
		{
			sum += p[i]->getnum();
		}
		std::cout << "动物总数:" << sum << std::endl;
	}
private:
	int mCapacity;
	int mSize;
	Animal** p;//指针数组
};
void test()
{
	Zoo* zoo = new Zoo;
	zoo->AddAnimal(new Dog("Dog", 24));
	zoo->AddAnimal(new Duck("Duck", 35));
	zoo->AddAnimal(new Tiger("Tiger", 10));
	zoo->Speak();
	zoo->getNum();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}