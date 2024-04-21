一.  vector库
创建数组:
int x,y,i;
vector<int> arr1;
for (i = 0; i < 7; i++)
{
    cin >> x >> y;
    arr1.push_back(x + y);
}//name.push_back(int)向数组中存入int类型值

max_element(arr1.begin(),arr1.end()) - arr1.begin()
//求数组中最大值所在下标

*max_element(arr1.begin(),arr1.end())
//求数组中最大值的数值

vertor<vector<int>> arr2(5,vector<int>(6,x))
//定义一个二维数组5行6列且初始化为x

arr.push_back(n)
//在数组尾端增加一个值为n的元素

arr.pop_back()
//在数组尾端删除一个元素

arr.size()
//查看数组长度

arr.back()
//输出数组中最后一个元素

arr.clear()
//一次性清空数组中的所有元素

arr.empty()
//判断数组是否是空的，空则返回1，非空返回0

arr.resize(length,x)
//修改数组长度,  length代表修改后数组的长度，若长度增加，x表示增加的值都被赋为x，不写默认为0

//此外，vector数组存储的值在堆空间中，不会栈溢出

注意事项：1.如果数组长度已经确定，应提前指定长度
例如://优化前:522ms
      vector<int> a;
      for(i=1;i<1e8;i++)
         a.push_back(i);
     
     //优化后:259ms
      vector<int> a(1e8);
      for(i=0;i<a.size(),i++)
         a.push_back(i);


2.注意size_t溢出
   
   arr.size()的返回值类型是size_t,通常范围为[0,2^32)

   vector<int> a(65536);
   long long a = a.size() * a.size()//此时已经爆了，输出0


二.    栈  stack  (先进后出)

stack<double> stk;//创建一个栈
stk.push(1.0)
stk.push(1.4)//向栈内放置元素

cout<<stk.top();//输出栈顶，结果为1.4,因为栈是先进后出

stk.size()//查看栈的大小

stk.pop()//出栈，从栈顶开始

stk.empty()//判断栈是否为空


三.  队列  queue   (先进先出)

queue<int> que;
que.push(x)
//向队列输入x

que.pop()
//向队列取出（取第一个）

que.front()
//输出队首

que.back()
//输出队尾

//其他用法与stack用法一样


四.  优先队列  priority_queue  (提供常数时间的最大元素查找，对数时间的插入与提取，底层原理是二叉堆)

priority_queue<int> pque;//默认为大顶堆，pop和top时都取最大值
pque.push(1);
pque.push(3);
pque.push(9);
pque.push(7);
cout<<pque.top();//输出队列里的最大值，此结果为9

pque.pop();//将队里的最大元素弹出，弹出后队列最大为7

如果想变成小顶堆，则换种方法书写
priority_queue<int,vector<int>,greater<int>> pque;//此时改为小顶堆


五.  集合  set (提供对数时间的插入，删除，查找的集合数据结构，底层原理是红黑树)

set:具有确定性(一个元素要么在集合中，要么不在)，互异性(一个元素仅可在集合中出现一次)，有序性(从小到大排序)

multiset:具有确定性(一个元素要么在集合中，要么不在),(一个元素仅可在集合中出现多次)，有序性(从小到大排序)

unordered_set:具有确定性(一个元素要么在集合中，要么不在)，互异性(一个元素仅可在集合中出现一次)，无序性(没有顺序)

set<int> st;

st.insert(x);
//插入元素x

st.erase(x);
//删除元素x

st.find(x);
//查找元素x,返回迭代器，如果找不到则返回st.end()

st.count(x);
//返回元素x的个数，可用于查找是否含有x元素，比st.find()方便

st.size();
//查看集合大小

st.clear();
//清空集合

st.empty();
//判断集合是否为空

遍历：
for(auto &ele : st)
   cout<< ele <<endl;

适用情形：
1.元素去重    {1,2,2,4,4,5,6} --->   {1,2,4,5,6}

2.维护顺序    {1,5,3,7,9}  --->   {1,3,5,7,9}

3.元素是否存在  set<int> st;
                 //向集合中插入元素
               if(st.count(x))//判断x是否存在
                 {
                    //操作
                 }


注意事项:1.不存在下标索引(像数组一样)

        2.元素只读

        3.不可用迭代器计算下标



 六.  映射  map  (提供对数时间的有序键值对结构，底层原理是红黑树) 增删查找时间为logn
            unordered_map (常数时间的键值对结构,底层原理是哈希表) 查找时间为O(1) 

七.  字符串  string  头文件#include<string>

string s;
s = "awa";

s[0] = 'b';//修改字符串中下标为0的字符

string s1 ="123"  string s2 = "123"

if(s1 == s2) //判断字符串相等

string s = "123456789";
s.substr(3);//输出从下标为3开始到结束的字符串，输出456789

s.substr(3,4);//输出从下标为3开始，字符串长度为4的字符串456，输出7

s.find("456");//输出子字符串"456"的下标,结果为3

if(s.find("456") != string::npos)
    //操作

s.find() 当找不到时会输出string::npos这个规定的值

int x = stoi(s);//将字符串内容输出为整型，结果为123456789

int x = 66662;
string s = to_string(x);//将整型转为字符串

//在字符串中寻找所有为"..."的子串的下标
while((pos = t.s.find("...",pos)) != string::npos){
    //找到第pos下标
    pos++;
}

八.  二元组  pair    头文件#include<utility>

pair<int,int> p = {1,2} // 赋值

p.first;//访问第一个元素

p.second;//访问第二个元素


九. 排列函数 next_permutation 头文件#include<algorithm>

 #include <algorithm>

     bool next_permutation(iterator start,iterator end)

下面举例对数组{1,2,3}进行全排列

#include <iostream>  
#include <algorithm>  
using namespace std;  
int main()  
{  
    int num[3]={1,2,3};  
    do  
    {  
        cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<endl;  
    }while(next_permutation(num,num+3));  
    return 0;  
}  
结果输出: 1 2 3 ; 1 3 2; 2 1 3; 2 3 1; 3 1 2; 3 2 1;

