#include "widget.h"
#include"window2.h"
#include<QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Window2* w2 = new Window2;//设置窗口2

    Init(this,1);
    Init(w2,2);

    connect(btn1,&QPushButton::clicked,[=](){
       this->hide();
       w2->show();
    });

    connect(btn2,&QPushButton::clicked,[=](){
       w2->hide();
       this->show();
    });
}
Widget::~Widget() {}
