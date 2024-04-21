#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void Init(QWidget* window,int opt)
    {
        if(opt == 1){
            window->setGeometry(200,200,400,300); //设置窗口1
            window->setWindowTitle("窗口1");
            btn1 = new QPushButton("切换窗口2",window);
            btn1->move(200,150);
        }
        if(opt == 2){
            //window->hide();
            window->setGeometry(600,600,400,300); //设置窗口1
            window->setWindowTitle("窗口2");
            btn2 = new QPushButton("切换窗口1",window);
            btn2->move(200,150);
        }
    }

public:
    QPushButton* btn1;
    QPushButton* btn2;
};
#endif // WIDGET_H
