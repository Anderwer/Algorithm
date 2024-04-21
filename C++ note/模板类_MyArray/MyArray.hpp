#include<iostream>

template<class T>
class MyArray
{
public:
	//无参构造
	MyArray() {};
	//有参构造
	MyArray(int capacity)
	{
		this->mCapacity = capacity;
		this->mSize = 0;
		this->pArray = new T[this->mCapacity];
	}
	//拷贝构造
	MyArray(const MyArray& arr)
	{
		pArray = new T[arr.mCapacity];
		this->mCapacity = arr.mCapacity;
		this->mSize = arr.mSize;
		for (size_t i = 0; i < this->mCapacity; i++) this->pArray[i] = arr.pArray[i];
	}
	//尾插
	void push_back(const T& val)
	{
		if (this->mSize == this->mCapacity) return;
		this->pArray[mSize++] = val;
	}
	//尾删
	void pop_back()
	{
		if (!this->mSize) return;
		mSize--;
	}
	//获取大小
	size_t size()
	{
		return this->mSize;
	}
	//重载[]
	T& operator[](int index)
	{
		return this->pArray[index];
	}
	//重载=
	MyArray operator=(const MyArray& arr)
	{
		if (this->pArray != nullptr)
		{
			delete[] this->pArray;
			this->pArray = nullptr;
		}
		this->mCapacity = arr.mCapacity;
		this->mSize = arr.mSize;
		this->pArray = new T[arr.mCapacity];
		for (size_t i = 0; i < arr.mCapacity; i++) this->pArray[i] = arr.pArray[i];
		return *this;
	}
	//析构
	~MyArray()
	{
		if (this->pArray != nullptr)
		{
			delete[] this->pArray;
			this->pArray = nullptr;
		}
	}
public:
	T* pArray;
	size_t mCapacity;
	size_t mSize;
};