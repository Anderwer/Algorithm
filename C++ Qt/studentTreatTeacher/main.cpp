#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

//场景1:下课了，老师饿了，学生请吃饭
//创建2个类: Student Teacher
//信号发送者:Teacher
//信号: hungry
//信号接受者:Student
//槽: Student treat teacher

//场景2:下课了，老师饿了，并且想吃黄焖鸡,学生请吃黄焖鸡
//创建2个类: Student Teacher
//信号发送者:Teacher
//信号: hungry 带有参数
//信号接受者:Student
//槽: Student treat teacher 带有参数
