一.系统标准的异常库类 加上头文件#include<stdexcept>

class Person
{
public:
	Person(int age)
	{
		if (age > 150 || age < 0) throw std::out_of_range("年龄不在范围内");
		else this->age = age;
	}
public:
	int age;
};
void test()
{
	try
	{
		Person p(200);
	}
	catch (std::out_of_range& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

----------------------------------------------------------------------------------------------------

二.标准的输入流
/*
cin.get() 一次只能读取一个字符
cin.get(一个参数) 读一个字符
cin.get(两个参数) 可以读字符串
cin.getline() //取一行,换行符丢弃
cin.ignore() //忽略字符,可以填参数N 代表忽略前N个字符
cin.peek()   //偷窥第一个字符 但不拿取缓冲区的字符
cin.putback() //放回字符到缓冲区
*/
void test()
{
	char s[1024];
	std::cin.get(s, 1024); //读取缓冲区时,换行符不拿走
	std::cout << s << std::endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------

三.标准的输出流
/*
setw() 设置宽度
setfill() 填充
setiosflags(ios::left) 打印在左边
setprecision(N) 打印小数点后N位
*/

-------------------------------------------------------------------------------------

四.文件读写
1.写文件步骤

#include<fstream>  //1.引入头文件
void test()
{
	std::ofstream ofs; //2.定义流对象
                                    //按位或运算符
	ofs.open("test.txt", std::ios::out | std::ios::trunc); //3.打开文件,以写的方式打开,如果没有文件就创建
	if (!ofs.is_open()) std::cout << "打开失败" << std::endl;//4.判断文件是否打开
	ofs << "Name:迎难而上" << std::endl;
	ofs << "NickName:mcbwxg" << std::endl;
	ofs << "Hobby:Gregtech" << std::endl; //5.写信息
	ofs.close(); //6.关闭文件
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.读文件步骤
#include<fstream>  //1.引入头文件
void test() //第一种方式,一行一行读
{
	std::ifstream ifs; //2.定义流对象
	ifs.open("test.txt", std::ios::in); //3.打开文件,以读的方式打开
	if (!ifs.is_open()) std::cout << "打开失败" << std::endl;//4.判断文件是否打开
	char s[1024];
    //第一种方式,一行一行读
	while (ifs >> s) std::cout << s << std::endl; //5.读文件  

    //第二种方式
    while (!ifs.eof())
    {
	    ifs.getline(s, sizeof(s));
	    std::cout << s << std::endl;
    }

    //第三种方式,单个字符读取
    char c;
    while ((c = ifs.get()) != EOF) std::cout << c;

	ifs.close();//6.关闭文件
}

------------------------------------------------------------------------------------------------

五.二进制文件读写
class Person
{
public:
	Person() {}
	Person(const char* name,int age)
	{
		this->age = age;
		strcpy(this->name,name);
	}
public:
	char name[64];
	int age;
};
void test01() //二进制写文件
{
	Person p1("迎难而上", 114514);
	Person p2("mcbwxg", 1919810);  //实例化对象
	std::ofstream ofs;		//打开          //创建				//二进制文件
	ofs.open("test.txt", std::ios::out | std::ios::trunc | std::ios::binary);
	ofs.write((const char*)&p1, sizeof(Person));
	ofs.write((const char*)&p2, sizeof(Person)); //将实例化的对象写入文件中
	ofs.close(); //关闭文件
}

void test02() //二进制读文件
{
	Person p1, p2; //实例化对象
	std::ifstream ifs;
	ifs.open("test.txt", std::ios::in);//打开文件
	ifs.read((char*)&p1, sizeof(Person));
	ifs.read((char*)&p2, sizeof(Person)); //将文件内容存入对象中
	std::cout << "name:" << p1.name << " age:" << p1.age << std::endl;
	std::cout << "name:" << p2.name << " age:" << p2.age << std::endl;
	ifs.close();//关闭文件
}
int main()
{
	test01();
	test02();
	return EXIT_SUCCESS;
}

-------------------------------------------------------------------------------------------

六.文件读写时有成员变量是string类型时的问题

注意:当文件读写时,类中的成员变量不要用string类型
class Person
{
public:
	Person() {}
	Person(std::string name,int age)
	{
		this->age = age;
		this->name = name;
	}
public:
	string name;//成员变量是string类型

    //string类有一个成员指针char* ,该指针指向存储字符串的空间
    //当我们把string类的数据存到文件中,再读出来时,不能保证指针有效,因此在调用析构时会报错
    //string 开辟的空间如果大于16字节就在堆区,小于就在栈区
	
    int age;
};
void test01()
{
	Person p1("迎难而上", 114514);
	Person p2("mcbwxg", 1919810);  
	std::ofstream ofs;		
	ofs.open("test.txt", std::ios::out | std::ios::trunc | std::ios::binary);
	ofs.write((const char*)&p1, sizeof(Person));
	ofs.write((const char*)&p2, sizeof(Person)); 
	ofs.close(); 
}
void test02() 
{
	Person p1, p2; 
	std::ifstream ifs;
	ifs.open("test.txt", std::ios::in);
	ifs.read((char*)&p1, sizeof(Person));
	ifs.read((char*)&p2, sizeof(Person));
	std::cout << "name:" << p1.name << " age:" << p1.age << std::endl;
	std::cout << "name:" << p2.name << " age:" << p2.age << std::endl;
	ifs.close();
}
int main()
{
	test01();
	test02();
	return EXIT_SUCCESS;
}
