 一.菜单栏

    //菜单栏,获取当前窗口的菜单栏,如果没有则会自动创建一个
    QMenuBar* mb = this->menuBar();
    //添加菜单
    QMenu* menuFile = mb->addMenu("文件");
    QMenu* menuEdit = mb->addMenu("编辑");
    //往菜单里添加菜单项
    menuFile->addAction("新建");
    menuFile->addAction("打开");

    //添加分隔符
    menuFile->addSeparator();

    //添加二级菜单
    QMenu* menuRecent = menuFile->addMenu("最近打开的文件");
    menuRecent->addAction("1.txt");

    等等...

二.工具栏
    //添加工具栏,可以有多个
    QToolBar* toolBar = this->addToolBar("");
    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);

    //默认停靠在左边
    this->addToolBar(Qt::LeftToolBarArea,toolBar);

    //只允许停靠在左边或右边
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    //设置工具栏不可以浮动
    toolBar->setFloatable(false);

    //设置工具栏不可以拖动
    toolBar->setMovable(false);

    等等...

三.状态栏
    //添加状态栏,只有一个
     QStatusBar* stBar = this->statusBar();

    //往状态栏添加信息
    //添加左侧信息
    QLabel* labelLeft = new QLabel("左侧信息",this);
    stBar->addWidget(labelLeft);

    //添加右侧信息
    QLabel* labelRight = new QLabel("右侧信息",this);
    stBar->addPermanentWidget(labelRight);

四.停靠部件和核心部件
    //停靠部件,可以有多个
    QDockWidget* dockWidget = new QDockWidget("停靠部件",this);
    //默认情况下没有核心部件作为参照物,停靠部件会占满整个窗口
    this->addDockWidget(Qt::BottomDockWidgetArea,dockWidget);

    //添加核心部件
    QTextEdit* textEdit = new QTextEdit(this);
    this->setCentralWidget(textEdit);

五.ui文件的使用
    创建项目的时候保留ui文件
    setupUI函数,就是关联UI文件的代码到窗口
    
    要使用ui里的对象
    就直接 ui->对象名 来获取窗口对象指针

    例如,往状态栏里添加左侧信息
    ui->statusBar->addWidget(new QLabel("左侧信息",this));

六.资源文件的使用
    
    //使用图片资源
    //1.使用绝对路径
    ui->actionNew->setIcon(QIcon("图片路径"));

    //2.使用资源文件
    //使用资源文件的步骤
    // 冒号 + 前缀 + 目录文件名
    ui->action->setIcon(QIcon(":/Resource/1.png"));

七:模态对话框和非模态对话框 (没有最大化和最小化的窗口)

模态对话框:对话框还没关闭前不能操作同一个进程的其他窗口

非模态对话框:对话框还没关闭前也能操作同一个进程的其他窗口

创建模态和非模态对话框:
    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        connect(ui->actionModal,&QAction::triggered,[=](){
          //创建模态对话框
          QDialog modalWidget(this);//因为有exec阻塞,所有可以用局部变量
           modalWidget.exec();
     });

     connect(ui->actionNonModal,&QAction::triggered,[=](){
        //创建非模态对话框
        QDialog* nonModalWidget = new QDialog(this);
        nonModalWidget->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口时自动释放内存
        nonModalWidget->show();//show不能阻塞进程,因此需要用全局维持生命周期
     });
    }
    注意:当创建非模态对话框时,由于申请了全局变量但是this一直未被释放,会造成内存泄漏
        需要用setAttribute(Qt::WA_DeleteOnClose)防止内存泄漏

八.Qt中内置对话框的使用
    ●QMessageBox:   模态对话框，用于显示信息、询问问题等;   (常用)
    ●QColorDialog:   选择颜色;
    ●QFontDialog:   选择字体;
    ●QFileDialog:   选择文件或者目录;   (常用)
    ●QInputDialog:  允许用户输入一个值，并将其值返回;
    ●QPageSetupDialog:  为打印机提供纸张相关的选项;
    ●QPrintDialog:  打印机配置;
    ●QPrintPreviewDialog: 打印预览;
    ●QProgressDialog:   显示操作过程;

●QMessageBox 对话框的使用(用于显示消息提示,我们一般会使用其提供的几个static函数)
    //引入<QMessageBox>库
    void MainWindow::on_actionCritical_triggered()
    {
        QMessageBox::critical(this,"错误","critical");
    }


    void MainWindow::on_actionWarning_triggered()
    {
         QMessageBox::warning(this,"警告","warning");
    }


    void MainWindow::on_actionInfo_triggered()
    {
         QMessageBox::information(this,"信息","info");
    }


    void MainWindow::on_actionQuestion_triggered()
    {
        if(QMessageBox::Ok == QMessageBox::question(this,"问题","question",
                                                     QMessageBox::Ok | QMessageBox::Cancel))
        {
             qDebug() << "点击了OK";
        }
        else
        {
            qDebug() << "点击了Cancel";
        }
    }

●QFileDialog的使用:
    void MainWindow::on_actionOpenFile_triggered()
{
    QFileDialog::getOpenFileName(this,"打开一个文件","D:\\Qt test\\02_ui\\Resource",
    "PNG (*.png) ;; JPG (*.jpg) ;; all (*.*)");
    //第三个参数是默认打开的路径
    //第四个参数是可以选择的文件类型
    //该函数的返回值是QString,返回打开文件的路径
}

