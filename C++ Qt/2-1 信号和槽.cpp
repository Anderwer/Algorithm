一.信号和槽的机制
    信号:各种事件.
    槽: 响应信号的动作.

    当某个事件发生后,如某个按钮被点击了一下,它就会发出一个被点击的信号(signal)
    某个对象接收到这个信号之后,就会做一些相关的处理动作称为槽(slot)

    但是 Qt对象不会无故收到某个信号,要想让一个对象收到另一个对象发出的信号,这时候需要建立连接(connect)

    可以将其抽象为:
        信号发送者
        信号
        信号接收者
        槽:信号的处理动作
        默认情况下,它们四者没有关系,通过connect建立四者关系
        connect(信号发送者, 信号, 信号接收者, 槽);

    例如制作一个关闭按钮:
        QPushButton *btn = new QPushButton("关闭按钮",this);
        connect(btn,&QPushButton::clicked,this,&HelloWidget::close); 其中 connect 函数的四个参数都是指针

-----------------------------------------------------------------------------------------------------

二.自定义信号和槽
1.构建方法

    自定义信号:
        1.函数声明在信号发送者的类的头文件中 signals 类下面
        2.void 类型的函数,没有返回值
        3.可以有参数,也可以重载
        4.只有声明,没有实现定义
        5.触发信号 emit obj->sign(参数...)
    
    自定义槽:
        1.函数声明在类的头文件中 slots 类下面 (qt5 可以声明在类的任何位置)
        2.void 类型的函数,没有返回值
        3.可以有参数,也可以重载
        4.不仅有声明,还得有实现定义

    #include "widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pStudent = new Student(this);
    pTeacher = new Teacher(this);//将两个对象添加到对象树中
    //无参传递
    //connect(pTeacher,&Teacher::isHungry,pStudent,&Student::studentTreatTeacher);

    //有参传递时,isHungry 和 studentTreatTeacher 需要添加参数,此时发生函数重载,难免产生函数二义性问题
    //使用函数指针赋值 或者 static_cast 强转

    //使用 函数指针赋值
    void (Teacher::*teacher_qString)(QString) = &Teacher::isHungry; //强行调用有参函数
    void (Student::*student_qString)(QString) = &Student::studentTreatTeacher;
    connect(pTeacher,teacher_qString,pStudent,student_qString);

    //使用 static_cast 强转
    connect(pTeacher,
            static_cast<void (Teacher::*)(QString)>(&Teacher::isHungry),
            pStudent,
            static_cast<void (Student::*)(QString)>(&Student::studentTreatTeacher)
            );

    this->classOver();//传入signal
}

Widget::~Widget() {}

void Widget::classOver()
{
    emit pTeacher->isHungry();//发出信号 无参

    emit pTeacher->isHungry("黄焖鸡"); //发出信号 有参
}

2.信号和槽的扩展
    1.一个信号可以连接多个槽
        一个信号建立了多个connect 那么当信号发射的时候,槽函数的调用顺序随机
    
    2.一个槽可以连接多个信号

    3.信号可以连接信号

    4.信号可以断开连接
        connect 参数怎么填 disconnect 参数就怎么填

    5.信号和槽的参数关系,必须满足以下两点:
        1.信号和槽函数的参数类型必须对应
        2.信号和槽函数的参数个数不需要一致, 信号函数参数个数 >= 槽函数参数个数
        如:
        isHungry(QString)   ->   treat()      ok
        isHungry(QString)   ->   treat(int)   编译出错
        isHungry(QString,int) -> treat(QString) ok
        isHungry(QString,int) -> treat(int)   编译出错

3. Qt4 的信号和槽

    使用两个宏 SIGNAL 和 SLOT
    connect使用不一样,但是信号和槽函数声明差不多
    connect(信号发送者, SIGNAL(函数原型), 信号接收者, SLOT(函数原型)) 

    connect(pTeacher,SIGNAL(isHungry(QString)),pStudent,SLOT(studentTreatTeacher(QString)));

    好处:没有重载二义性问题

    坏处:写错了函数原型,编译期间不报错

4.qDebug 输出转义问题 (即输出字符串时会带上""等)

解决方法:
    1. 将QString 转成 char*:
        void Student::studentTreatTeacher(QString what)
        {
            qDebug()<< "Student treat teacher with "<< what.toUtf8().data();
        }

    2.使用qDebug().noquote()
         void Student::studentTreatTeacher(QString what)
        {
            qDebug().noquote()<< "Student treat teacher with "<< what;
        }

-------------------------------------------------------------------------------------------------------

三.Lambda表达式
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //lambda表达式
    //     [capture](parameters) opt ->retType
    //     {
    //     ...
    //     }

    //调用lambda的方式,使用函数指针
        void (*p)() =
        []()
        {
            qDebug() << "Hello Lambda";
        };
    p();

    //局部变量捕获
    //在[]内填变量名即可捕获,捕获分为值传递和引用传递
    //在[]填 = -> [=] 就是将局部变量全部用值传递方式传进来     [&]是全部用引用传递进来


    //信号和槽使用lambda
    int a = 10, b = 20;
    QPushButton *btn = new QPushButton("输出a和b",this);
    
    //以后都使用[=](){}的形式
    connect(btn,&QPushButton::clicked,[=](){
        qDebug()<< a << b;
    });

}

