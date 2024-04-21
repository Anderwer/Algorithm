一.::作用域运算符
1.访问全局变量
#include<iostream>
using namespace std;
int a = 10;
int main()
{
    int a = 20;
    cout << "a = " << a << endl;//结果为 a = 20,就近原则
    cout << "::a = " << ::a << endl;//结果为 ::a = 10,加了::作用域运算符访问全局
    return EXIT_SUCCESS;
}

2.访问命名空间内的变量
#include<iostream>
using namespace std;
namespace Maker{
    int c = 10;
}
int main()
{
    cout << "c = " << Maker::c << endl;
    return EXIT_SUCCESS;
}

-------------------------------------------------------------------------------------------

二.名字控制
1.C++命名空间namespace(解决多人合作时取标识符时重命名的问题)
//命名空间
namespace A{//A是空间的名字
    int a;
    void func()
    {

    }
}

注意1:命名空间只能写在全局,不能写在函数内

注意2:命名空间可以嵌套命名空间

访问嵌套的命名空间
#include<iostream>
using namespace std;
namespace Maker{
    int c = 10;
    namespace A{
        int b = 40;
    }
}
int main()
{
    cout << "b = " << Maker::A::b << endl;
    return EXIT_SUCCESS;
}

注意3:命名空间是开放的,随时可以加入新成员,但是新成员只能在加入后使用

注意4:匿名命名空间
//类似于static int b = 40;
namespace {
    int b = 40;
}

注意5:命名空间可以取别名
namespace Maker{
    int c = 10;
}
void test()
{
    //         新名字     旧名字
    namespace NewMaker = Maker;
    cout << NewMaker::c << endl;
}
int main()
{
    test();
    return EXIT_SUCCESS;
}

注意6:分文件编写时,如果.h文件中有2个命名空间,但是里面的成员函数或成员变量相同时,在.cpp中实现函数时,需要加上命名空间
//test.h中的内容
#include<iostream>
using namespace std;
namespace MakerTest1
{
    void func();
}
namespace MakerTest2
{
    void func();
}

//test.cpp中内容
#include"test.h"
void MakerTest1::func()//即注意6
{
	cout << "func" << endl;
}

//main.cpp中的内容
#include"test.h"
int main()
{
    MakerTest1::func();
    return EXIT_SUCCESS;
}

2.using 关键字
#include<iostream>
using namespace std;
namespace Maker
{
    int c = 10;
}
void func1()
{
    cout << "c = " << Maker::c << endl;//没用using关键字
}
void func2()
{
    using Maker::c;
    cout << "c = " << c << endl;//使用using关键字
}
其中,如果想直接使用命名空间中所有的变量 可以使用 using namespace Maker;
int main()
{
    func1();
    func2();
    return EXIT_SUCCESS;
}

------------------------------------------------------------------------

三.结构体的加强
加强一:
struct Maker1
{
    char name[50];
    int age;
}
void test1()
{
    Maker1 a;//不需要加struct 就可以定义变量
}

加强二:
struct Maker2
{
    void func()
    {
        cout << "func" << endl;//结构体内部可以定义函数
    }
}
int main()
{
    Maker2 b;
    b.func();
    return EXIT_SUCCESS;
}

----------------------------------------------------------------------------

四.更加严格的类型转换检查
int main()
{
    char *p = malloc(64);//这是C语言中的写法,在cpp中报错
    //cpp要以下写法
    char *p = (char *)malloc(64);
    return EXIT_SUCCESS;
}

----------------------------------------------------------------------------

五.const修饰的变量
1.C语言中const修饰的变量具有空间
2.C语言中const修饰的变量具有外部链接属性

3.C++中const修饰的变量没有空间
const int a = 10;//类似于#define a 10 ,不占用空间,发生了常量折叠
cout << "a = " << a << endl;
//在编译阶段,编译器:cout << "a =" << 10 << endl;
因此,在间接修改a的值时cout输出还是输出原来的a (const修饰的变量在栈区时才能间接修改)
int *p = &a;
*p = 200;
cout << "a = " << a << endl;//结果还是输出10

//禁止优化
volatile const int b = 10;
int *p = &b;
*p = 200;
cout << "b = " << b << endl;//此时输出200,volatile关键字是禁止编译器优化

4.C++中const修饰的变量具有内部链接属性//但是在别的文件中定义变量时写成extern const int c = 10;则可以进行外部链接

-----------------------------------------------------------------------------------
