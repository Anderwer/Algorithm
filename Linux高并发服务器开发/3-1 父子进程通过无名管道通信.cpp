#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#define SIZE 128

int main()
{   
        perror("pipe");
        return 1;
    }
    
    fd = fork();
    if(-1 == fd)
    {
        perror("fork");
        return 1;
    }
    
    if(0 == fd) //子进程 读管道
    {
        close(fds[1]); //关闭写端
        memset(buf, 0, SIZE);
        ret = read(fds[0], buf, SIZE);
        if(ret < 0)
        {
            perror("read");
            exit(-1);
        }
        printf("child process read: %s\n", buf);
        close(fds[0]); //关闭读端
        exit(0);       
    }

    close(fds[0]); //关闭读端
    ret = write(fds[1], "ABCDEFGHIJ", 10);
    if(ret < 0)
    {
        perror("write");
        return 1;
    }
    printf("parent process write len: %d\n", ret);
    close(fds[1]); //关闭写端
    return 0;
}

注意 : 由于无名管道特性,读端如果未接收则会一直堵塞,所以不用担心子进程先读而父进程后写

管道读写特性:
    读管道:
        管道中有数据 : read 返回实际读到的字节数
        管道中无数据 : 1. 管道写端被全部关闭,read 返回 0 (相当于读到文件结尾)
                      2. 写端没有被全部关闭,read 阻塞等待(之后可能会有数据抵达,此时会让出CPU)

    写管道:
        管道读端全部被关闭,进程异常终止 (也可以使用捕捉SIGPIPE信号,使进程终止)
        管道读端没有全部关闭 : 1. 管道已满, write阻塞
                             2. 管道未满, write将数据写入,并返回实际写入的字节数.


设置管道为非阻塞:

//获取原来的flags
int flags = fcntl(fds[0], F_GETFL);
//设置新的flags
flags |= O_NONBLOCK;
//添加到fds[0]中
fcntl(fds[0], F_SETFL, flags);
