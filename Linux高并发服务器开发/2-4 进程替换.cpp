概述:

在 Windows 平台下,我们可以通过双击运行可执行程序,让这个可执行程序成为一个进程;而在 Linux 平台
我们可以通过./运行,让一个可执行程序成为一个进程.

但是,如果我们本来就运行着一个程序(进程),我们如何在这个进程内部启动一个外部程序,由内核将这个
外部程序读入内存,使其执行起来成为一个进程呢?这里我们通过 exec 函数族实现.

exec函数族,顾名思义,就是一簇函数,在 Linux 中,并不存在 exec()函数,exec指的是一组函数,一共有6个:

#include<unistd.h>
extern char** environ;

int execl(const char* path, const char* arg, .../* (char*) NULL */)

int execlp(const char* file, const char* arg, .../* (char*) NULL */)

int execle(const char* path, const char* arg, .../* (char*) NULL, char* const envp[] */)

int execv(const char* path, char* const argv[])

int execvp(const char* file, char* const argv[])

int execvpe(const char* file, char* const argv[], char* const envp[])

int execve(const char* filename, char* const argv[], char* const envp[])

其中只有execve()是真正意义上的系统调用,其他都是在此基础上经过包装的库函数

exec 函数族的作用是根据指定的文件名或日录名找到可执行文件,并用它来取代调用进程的内容,
换句话就是在调用进程内部执行一个可执行文件.

进程调用一种 exec 函数时,该进程完全由新程序替换,而新程序则从其 main 函数开始执行.
因为调用 exec并不创建新进程,所以前后的进程ID(当然还有父进程号、进程组号、当前工作目录.)并未改变.
exec 只是用另一个新程序替换了当前进程的正文,数据,堆和栈段(进程替换).