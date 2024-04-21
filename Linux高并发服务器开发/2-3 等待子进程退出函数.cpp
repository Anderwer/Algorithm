
在每个进程退出的时候,内核释放该进程所有的资源,包括打开的文件,占用的内存等.但是仍然为其保留定的信息,
这些信息主要主要指进程控制块PCB的信息(包括进程号、退出状态、运行时间等).

父进程可以通过调用wait或waitpid得到它的退出状态同时彻底清除掉这个进程.

wait() 和 waitpid()函数的功能一样,区别在于wait()函数会阻塞,waitpid()可以设置不阻塞,
waitpid()还可以指定等待哪个子进程结束.

注意: 一次wait或waitpid调用只能清理一个子进程,清理多个子进程应使用循环.

--------------------------------------------------------------------------------------------
1. wait 函数

#include<sys/types.h>
#include<sys/wait.h>

pid_t wait(int* status)

功能: 等待任意一个子进程结束,如果任意一个子进程结束了,该函数会回收子进程资源

参数: 
    status : 进程退出时的状态信息

返回值: 
    成功 : 已经结束子进程的进程号
    失败 : -1


调用 wait()函数的进程会挂起(阻塞),直到它的一个子进程退出或
收到一个不能被忽视的信号时才被唤醒(相当于继续往下执行).

若调用进程没有子进程,该函数立即返回;若它的子进程已经结束,
该函数同样会立即返回,并且会回收那个早已结束进程的资源.

所以,wait()函数的主要功能为回收已经结束子进程的资源.

如果参数 status 的值不是 NULL,wait()就会把子进程退出时的状态取出并存入其中,这是一个整数值(int),
指出了子进程是正常退出还是被非正常结束的.

这个退出信息在一个int 中包含了多个字段,直接使用这个值是没有意义的,
我们需要用宏定义取出其中的每个字段.

宏可分为以下三组:
1. WIFEXITED(status) : 为非0 -> 进程正常结束
   WEXITSTATUS(status) : 如果上宏为真,使用此宏 -> 获取进程退出状态(exit的参数)

2. WIFSIGNALED(status) : 为非0 -> 进程异常终止
   WTERMSIG(status) : 如果上宏为真,使用此宏 -> 取得使进程终止的那个信号的编号

3. WIFSTOPPED(status) : 为非0 -> 进程处于暂停状态
   WSTOPSIG(status) : 如果上宏为真,使用此宏 -> 取得使进程暂停的那个信号的编号
   WIFCONTINUED(status) : 如果为真,使用此宏 -> 进程暂停后已继续运行

--------------------------------------------------------------------------------------------
2. waitpid 函数

#include<sys/types.h>
#include<sys/wait.h>

pid_t waitpid(pid_t pid, int* status, int options)

功能: 等待子进程终止,如果子进程终止了,此函数会回收子进程的资源

参数:   
    pid : 参数pid有以下几种类型
    pid > 0 : 等待进程ID等于pid的子进程
    pid = 0 : 等待同一进程组中的任意子进程,如果子进程已经加入到其他进程组,waitpid()不会等待它
    pid = -1 : 等待任意子进程,此时waitpid() 和 wait()一样
    pid < -1 : 等待指定进程组中的任意子进程,这个进程组的PGID 等于 pid 的绝对值

    status : 进程退出时的状态信息,和wait()用法一样

    options : options 提供了一些额外的选项来控制waitpid()
        0 : 同 wait() ,阻塞父进程,等待子进程退出
        WNOHANG : 没有任何已经结束的子进程,则立即返回
        WUNTRACED : 如果子进程暂停了则此函数立即返回,并且不予理会子进程的结束状态

返回值:
    waitpid()的返回值比wait()稍微复杂一些,一共有3种情况:
    1. 当正常返回时,waitpid() 返回收集到的已经回收子进程的进程号
    2. 如果设置了选项WNOHANG, 而调用中waitpid()发现没有已退出的子进程可等待,则返回0
    3. 如果调用中出错,则返回-1

-------------------------------------------------------------------------------------------

等待子进程退出 示例:

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pid = -1;
    int status = -1;
    int ret = -1;
    pid = fork();
    if(-1 == pid) //设置子进程失败
    {
        perror("fork");
        return 1;
    }

    if(0 == pid) //当前处于子进程
    {
        for(int i = 0; i < 15; i++)
        {
            printf("当前进程号为:%d         执行编号:%d\n", getpid(), i + 1);
            sleep(1);
        }
        exit(10); //传出一个 status = 10
    }
    
    ret = wait(&status);

    if(-1 == ret)
    {
        perror("wait");
        return 1;
    }
    
    printf("父进程回收了子进程\n");

    if(WIFEXITED(status)) //子进程正常退出
    {
        printf("子进程退出状态码:%d\n", WEXITSTATUS(status));
    }
    
    else if(WIFSIGNALED(status))
    {
        printf("子进程被信号%d杀死\n", WTERMSIG(status));
    }

    else if(WIFSTOPPED(status))
    {
        printf("子进程被信号%d暂停\n", WSTOPSIG(status));
    }

    return 0;
}

