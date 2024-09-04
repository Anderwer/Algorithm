一. 创建管道

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

//通过mkfifo函数创建一个管道文件
int main(void)
{
    int ret = -1;

    //创建一个有名管道,名为fifo
    ret = mkfifo("fifo", 0644);
    if(-1 == ret)
    {
        perror("mkfifo");
        return 1;
    }
    printf("创建一个有名管道ok...\n");
    return 0;
}

//注意 :有名管道fifo是队列，先进先出

二. 写管道

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 128

int main(void)
{
    int fd = -1;
    //1.以只写的方式打开一个管道文件
    fd = open("fifo", O_WRONLY);
    if(-1 == fd)
    {
        perror("open");
        return 1;
    }
    printf("打开管道文件ok...\n");

    //2.写管道
    char buf[SIZE];
    int i = 0;
    int ret = -1;
    while(1)
    {
        memset(buf, 0, SIZE);
        sprintf(buf, "读入第%d行", i++);
        ret = write(fd, buf, strlen(buf));
        if(ret <= 0)
        {
            perror("write");
            break;
        }
        printf("write fifo:%d\n",ret);
        sleep(1);
    }

    //3.关闭管道文件
    close(fd);

    return 0;
}


三. 读管道

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 128

int main(void)
{
    //1.以只读的方式打开一个管道文件
    int fd = -1;
    fd = open("fifo", O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        return 1;
    }

    //2.循环读管道
    int ret = -1;
    char buf[SIZE];
    while(1)
    {
        memset(buf, 0, SIZE);
        ret = read(fd, buf, SIZE);
        if(ret <= 0)
        {
            perror("read");
            break;
        }
        printf("buf:%s\n", buf);
    }

    //3.关闭管道文件
    close(fd);

    return 0;
}

四. 用Makefile 编译

vim Makefile

    all: read write

    read: fifo_read.c
        gcc $< -o $@

    write: fifo_write.c
        gcc $< -o $@

    .PHONY:clean

    clean:
        rm -rf read write

