#include "window2.h"
#include<QPushButton>
Window2::Window2(QWidget *parent)
    : QWidget{parent}
{
    this->setGeometry(600,600,400,300); //设置窗口1
    this->setWindowTitle("窗口1");
    QPushButton *btn2 = new QPushButton("切换窗口1",this);
    btn2->move(200,150);
}
