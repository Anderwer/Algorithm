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
