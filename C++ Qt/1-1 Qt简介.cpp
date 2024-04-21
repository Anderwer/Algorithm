一.创建项目时的三个类
QWidget : 最基础的窗口类,qt里能看到的东西的基类
QMainWindow : 具有菜单栏,工具栏,状态栏
QDialog : 对话框,没有最大化窗口

其中, QWidget 是 QMainWindow 和 QDialog 的基类

二.main.cpp详解

#include "hellowidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //创建一个应用程序对象
    //维护qt应用程序生命的一个对象,每个qt有且仅有一个的对象
    QApplication a(argc, argv);
    
    //创建一个窗口类的对象
    HelloWidget w;
    
    //把窗口显示出来
    w.show();
    
    a.exec();
    /*
     * 死循环让程序一直运行,生命循环,消息循环
     * while(1)
     * {
     *      if(点击x按钮)
     *          break;
     *      if(点击最小化按钮)
     *          最小化动作;
     *      ...
     * }
     */
    return 0;
}

三.头文件详解

#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H

#include <QWidget>

class HelloWidget : public QWidget
{
    //宏,引入qt信号和槽的一个宏
    Q_OBJECT

public:
    //parent窗口指针,父窗口对象的指针
    //如果parent为nullptr,表示当前窗口对象是个顶层窗口
    //顶层窗口就是可以在任务栏找到的窗口
    HelloWidget(QWidget *parent = nullptr);
    ~HelloWidget();
};
#endif // HELLOWIDGET_H

