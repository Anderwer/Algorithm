一. signal 函数

#include <signal.h>

typedef void(*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

功能 : 注册信号处理函数(不可用于 SIGKILL SIGSTOP 信号), 即确定收到信号后处理函数的入口地址. 此函数不会阻塞

参数 :
    signum : 信号的编号,这里可以填信号的数字编号,也可以填信号的宏定义

    handler : 取值有3种情况
            (1). SIG_IGN : 忽略该信号
            (2). SIG_DFL : 执行系统默认动作
            (3). 自定义信号处理函数, 如: func
                回调函数定义如下:
                void func(int signo)
                {
                    //signo 为触发的信号,为 signal()第一个参数的值
                }

返回值 : 
    成功 : 第一次返回NULL, 下一次返回此信号上一次注册的信号处理函数的地址, 如果需要使用此函数,必须在前面先声明此函数指针的类型
    失败 : 返回 SIG_ERR



二. sigaction 函数 (更常使用);

#include <signal.h>

int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);

功能 : 检查或修改指定信号的设置(或同时执行这两种操作)

参数 :  
    signum : 要操作的信号
    act : 要设置的对信号的新处理方式(传入参数)
    oldact : 原来对信号的处理方式(传出参数)

    如果 act 指针非空,则要改变指定信号的处理方式(设置), 如果 oldact 指针非空,则系统将此前指定信号的处理方式存入 oldact

返回值 : 
    成功 : 0
    失败 : -1

struct sigaction 结构体;
    struct sigaction {
        void (*sa_handler)(int); //旧的信号处理函数指针
        void (*sa_sigaction)(int, siginfo_t *, void *); //新的信号处理函数指针
        sigset_t sa_mask; //信号阻塞集
        int sa_flags; //信号处理的方式
        void (*sa_restorer)(void); //已弃用
    }

    (1). sa_handler, sa_sigaction : 信号处理函数指针, 和signal()里的函数指针用法相同,应根据情况给sa_sigaction, sa_handler两者之一赋值
    (2). sa_mask : 信号阻塞集, 在信号处理函数执行过程中,临时屏蔽指定的信号
    (3). sa_flags : 用于指定信号处理的行为, 通常设置为0, 表使用默认属性. 


使用示例 : (实现捕捉Ctrl + C 而执行自定义动作)

#include <stdio.h>
#include <signal.h>

//旧的信号处理函数
void func(int signum)
{
    printf("捕捉到信号: %d\n", signum);
}
//新的信号处理函数
void func_1(int signum, siginfo_t* info, void* context)
{
    printf("捕捉到信号: %d\n", signum);
}

int main(void)
{
    int ret = -1;

#if 0    // 旧函数
    struct sigaction act;
    //使用旧的信号处理函数指针
    act.sa_handler = func;
    //标志为默认  默认使用旧的信号处理函数指针
    act.sa_flags = 0;

#else    // 新函数
    struct sigaction act;
    //使用新的信号处理函数指针
    act.sa_sigaction = func_1;
    //标志为默认  默认使用新的信号处理函数指针
    act.sa_flags = SA_SIGINFO;

#endif
    //信号注册
    ret = sigaction(SIGINT, &act, NULL);
    if(-1 == ret)
    {
        perror("sigaction");
        return 1;
    }

    while(1)
    {
        getchar();
    }

    return 0;
}