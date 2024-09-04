一. 分析思路

    对于进程TalkA 和进程TalkB ,需要两个管道fifo1 和fifo2连接
    1.先创建2个管道 mkfifo fifo1 fifo2

    2.编写2个代码文件, TalkA.c TalkB.c ,每一个进程都有一个读写接口
      TalkA 先读后写
      TalkB 先写后读

    3.使用 makefile编译

二. 代码实现 :

TalkA.c 代码:


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128

//TalkA 进程先读后写, fifo1读, fifo2写
int main(void)
{
    //1.打开两个管道
    int fd_read = -1;
    int fd_write = -1;
    fd_read = open("fifo1", O_RDONLY);
    if(-1 == fd_read)
    {
        perror("open");
        return 1;
    }
    fd_write = open("fifo2", O_WRONLY);
    if(-1 == fd_write)
    {
        perror("open");
        return 1;
    }

    int ret = -1;
    char buf[SIZE];
    while(1)
    {
        //2.读管道
        memset(buf, 0, SIZE);
    sret = read(fd_read, buf, SIZE);
        if(ret <= 0)
        {
            perror("read");
            break;
        }
        printf("TalkB:%s\n", buf);

        //3.写管道
        memset(buf, 0, SIZE);
        fgets(buf, SIZE, stdin);
        if('\n' == buf[strlen(buf) - 1]) buf[strlen(buf) - 1] = '\0';
        ret = write(fd_write, buf, strlen(buf));
        if(ret <= 0)
        {
            perror("read");
            break;
        }
        printf("TalkB:%s\n", buf);

        //3.写管道
        memset(buf, 0, SIZE);
        fgets(buf, SIZE, stdin);
        if('\n' == buf[strlen(buf) - 1]) buf[strlen(buf) - 1] = '\0';
        ret = write(fd_write, buf, strlen(buf));
        if(ret <= 0)
        {
            perror("write");
            break;
        }

    }

    //4.关闭读写管道
    close(fd_read);
    close(fd_write);
    return 0;
}

TalkB.c 代码:

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 128

//TalkB 进程, 先写后读, fifo1写, fifo2读
int main(void)
{
    //1.打开读写管道
    int fd_read = -1;
    int fd_write = -1;
    fd_write = open("fifo1", O_WRONLY);//注意顺序，先写后读
    fd_read = open("fifo2", O_RDONLY);
    if(-1 == fd_read || -1 == fd_write)
    {
        perror("open");
        return 0;
    }


    int ret = -1;
    char buf[SIZE];
    while(1)
    {
        //2.写管道
        memset(buf, 0, SIZE);
        fgets(buf, SIZE, stdin);
        if('\n' == buf[strlen(buf) - 1]) buf[strlen(buf) - 1] = '\0';
        ret = write(fd_write, buf, strlen(buf));
        if(ret <= 0)
        {
            perror("write");
            break;
        }

        //3.读管道
        memset(buf, 0, SIZE);
        ret = read(fd_read, buf, SIZE);
        if(ret <= 0)
        {
            perror("read");
            break;
        }
        printf("TalkA:%s\n", buf);
    }

    //4.关闭读写管道
    close(fd_read);
    close(fd_write);

    return 0;
}


三. 联编

all: TalkA TalkB

TalkA: TalkA.c
    gcc $< -o $@

TalkB: TalkB.c
    gcc $< -o $@

.PHONY:clean

clean:
    rm -rf TalkA TalkB

