
一.类名 :1.单词首字母大写,单词和单词之间直接连接,无需连接字符
            如: MyClass , QPushBotton , class MainWindow 

        2.Qt中内置的类型,头文件和类命名同名
            如: #include<Qstring>
                Qstring str;

                #include<QWidget>
                QWidget w;

        3.函数名字,变量名:首字母小写,之后每个单词的首字母大写,单词和单词之间直接连接,无需连接字符
            如: void connectTheSignal();

        4.类的成员变量设置函数使用 set + 成员变量名,获取成员变量的函数直接用成员变量名(如果是bool类型可能会用一些表示状态的术语,如isVisiable,hasFocus)
            如: //普通成员变量的设置和获取
                void setText(Qstring text);
                Qstring text() const;

                //bool类型的成员变量设置和获取
                void setEnabled(bool enabled);
                bool isEnabled() const;

二.Ot Creator常用快捷键

    运行    Ctrl + R
    编译    Ctrl + B
    帮助文档    F1  ,  点击F1两次跳到帮助页面
    跳到符号定义    F2  或者    Ctrl + 鼠标左键
    注释    Ctrl + /
    字体缩放    Ctrl + 鼠标滚轮
    整行移动代码    Ctrl + Shift + ↑ 或 ↓
    自动对齐    Ctrl + i
    同名文件的.h 和 .cpp 文件跳转   F4
    