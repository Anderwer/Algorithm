#include<iostream>
#include<string>
using namespace std;

class MyArray
{
public:
    int getSize();//获取数组元素个数
    int getCapacity()const;//获取数组容量
    void Push_back(int x);//尾插
    int Pop_back();//查询尾
    int Pop_front();//查询头
    int query(int index);//查询任意index
    MyArray(int capacity,int init = 0);//有参构造
    MyArray(const MyArray& m);//拷贝构造
    MyArray operator=(MyArray& arr);//=重载函数
    int& operator[](int index);//[]重载函数
private:
    int* pArray;
    int Capacity;//容量
    int Size;//元素个数
};

void test()
{
    int Size = 20;
    MyArray arr(Size);
    for (int i = 0; i < Size; i++) arr[i] = i + 10;
    for (int i = 0; i < Size; i++) cout << arr[i] << " ";
    cout << endl;
    MyArray arr2 = arr;
    for (int i = 0; i < Size; i++) cout << arr2[i] << " ";
}
int main()
{
    test();
    return EXIT_SUCCESS;
}




int MyArray::getSize()
{
    return Size;
}

int MyArray::getCapacity()const
{
    return Capacity;
}

void MyArray::Push_back(int x)//尾插
{
    pArray[getSize()] = x;
    Size++;
}

int MyArray::Pop_back()
{
    return pArray[getSize() - 1];
}

int MyArray::Pop_front()
{
    return pArray[0];
}

int MyArray::query(int index)
{
    return pArray[index];
}

MyArray MyArray::operator=(MyArray& arr)
{
    if (!pArray)
    {
        delete[] pArray;
        pArray = nullptr;
    }
    pArray = new int[arr.getCapacity()];
    for (int i = 0; i < arr.getSize(); i++) pArray[i] = arr[i];
    return *this;
}

int& MyArray::operator[](int index)
{
    return pArray[index];
}

MyArray::MyArray(int capacity, int init)
{
    Capacity = capacity;
    pArray = new int[Capacity];
    for (int i = 0; i < Capacity; i++) pArray[i] = init;
}

MyArray::MyArray(const MyArray& m)
{
    Capacity = m.getCapacity();
    pArray = new int[Capacity];
    for (int i = 0; i < Capacity; i++) pArray[i] = m.pArray[i];
}
