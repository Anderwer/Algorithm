结构体：结构体是一些值的集合，这些值称为成员变量。结构体的每个成员可以是不同类型的变量。

结构体的声明：以学生为例

//struct - 结构体关键字    Stu - 结构体标签    struct Stu - 结构体类型
struct Stu
{
    char name[20];//名字
    short age;//年龄
    char sex[5];//性别
    char id[20];//学号
};//分号不能去

int main()
{
    struct Stu s;//创建结构体类型为struct Stu的s变量
    return 0;
}

声明的另一种方法
typedef struct Stu //重定义类型
{
    char name[20];//名字
    short age;//年龄
    char sex[5];//性别
    char id[20];//学号
}Stu;//重定义后的类型名
int main()
{
    Stu s;//经过重定义的类型为 Stu
    return 0;
}

结构体的初始化

typedef struct Stu 
{
    char name[20];
    short age;
    char sex[5];
    char id[20];
}Stu;
int main()
{
    Stu s={"张三",20,"男","12345678"};//结构体初始化
    return 0;
}

结构体成员的访问：通过点操作符(.)来访问 如：
typedef struct Stu 
{
    char name[20];
    short age;
    char sex[5];
    char id[20];
}Stu;
int main()
{
    Stu s={"张三",20,"男","12345678"};//结构体初始化
    printf("%d",s.id);//打印s中的id
    return 0;
}

结构体传参 

typedef struct Stu 
{
    char name[20];
    short age;
    char sex[5];
    char id[20];
}Stu;

void Print1(Stu tmp)
{
    printf("%s\n",tmp.name);
    printf("%d\n",tmp.age);
    printf("%s\n",tmp.sex);
    printf("%s\n",tmp.id);
}

void Print2(Stu* tmp)
{
    printf("%s\n",tmp->name);
    printf("%d\n",tmp->age);
    printf("%s\n",tmp->sex);
    printf("%s\n",tmp->id);
}

int main()
{
    Stu s={"张三",20,"男","12345678"};
    Print1(s);//直接传参
    Print2(&s);//利用指针传参
    return 0;
}
//两种传参结果都相同，但是用指针传参在时间和空间的占用都更小
//因此使用Print2的方式传参更好

















