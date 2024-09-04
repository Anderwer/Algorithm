一. kill 函数

#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);

功能 : 给指定进程发送指定信号(不一定杀死)

参数 : 
        pid : 取值有 4 种情况
        pid > 0 : 将信号传给进程ID为pid的进程
        pid = 0 : 将信号传给当前进程所在的进程组中的所有进程
        pid = -1 : 将信号传给系统内所有进程
        pid < -1 : 将信号传给指定进程组的所有进程,这个进程组号等于pid的绝对值

        sig : 信号的编号,可以填数字编号,也可以填信号的宏定义 (推荐填宏定义)

返回值 :
        成功 : 0
        失败 : -1


二. raise函数

#include <signal.h>

int raise(int sig);

功能 : 给当前进程发送指定信号(自己给自己发), 等价于 kill(getpid(), sig);

参数 : 
        sig : 信号编号

返回值 : 
        成功 : 0
        失败 : 非0的值


三. abort函数

#include <stdlib.h>

void abort(void);

功能 : 给自己发送异常终止信号 SIGABRT, 并产生core文件,等价于 kill(getpid(), SIGABRT);

参数 : 无

返回值 : 无



四. alarm函数(闹钟)

 #include <unistd.h>

 unsigned int alarm(unsigned int seconds);

 功能 : 设置定时器,在指定seconds后,内核给当前进程发送 SIGALRM信号. 进程收到该信号,默认动作终止.每个进程都有且只有一个定时器.
        取消定时器 alarm(0), 返回旧闹钟余下的秒数

参数 :
        seconds : 指定的时间,以秒为单位

返回值 :
        返回0或者剩余的秒数



五. setitimer函数(定时器)

#include <sys/time.h>

int setitimer(int which, const struct itimerval* new_value, struct itimerval* old_value);

功能 : 设置定时器, 可以代替alarm函数, 精度微妙us, 可以实现周期定时

参数 :
        which : 指定定时方式
                (1). 自然定时 : ITIMER_REAL -> SIGALRM 计算自然时间
                (2). 虚拟空间计时(用户空间) : ITIMER_VIRTUAL -> SIGVTALRM 只计算进程占用cpu时间
                (3). 运行时计时(用户 + 内核) : ITIMER_PROF -> SIGPROF 计算占用cpu及执行系统调用的时间

        new_value : struct itimerval, 负责设定timeout时间;
                struct itimerval {
                        struct timerval it_interval; //闹钟触发周期
                        struct timerval it_value;    //闹钟触发时间
                };

                struct timeval {
                        long tv_sec;   //秒
                        long tv_usec;  //微秒
                };

                itimerval.it_value : 设定第一次执行function所延迟的秒数
                itimerval.it_interval : 设定以后每几秒执行function

        old_value : 存放旧的timeout值,一般指定为NULL

返回值 :
        成功 : 0
        失败 : -1


代码示例 :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int main(void)
{
    int ret = -1;
    struct itimerval tmo;

    //第一次触发时间
    tmo.it_value.tv_sec = 3;
    tmo.it_value.tv_usec = 0;

    //触发周期
    tmo.it_interval.tv_sec = 2;
    tmo.it_interval.tv_usec = 0;

    //设置定时器
    ret = setitimer(ITIMER_REAL, &tmo, NULL);
    if(-1 == ret)
    {
        perror("setitimer");
        return 1;
    }

    //进程收到闹钟超时之后就会终止进程
    printf("按下任意键继续...\n");
    getchar();

    return 0;
}