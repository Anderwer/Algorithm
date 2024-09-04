(1). mmap函数

#include <sys/mman.h>

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);

功能: 一个文件或对它对象映射进内存

参数: 
    addr : 指定映射的起始地址,通常设为NULL,由系统指定
    length : 映射到内存的文件长度
    prot : 映射区的保护方式, 通常有
           (a).只读 : PROT_READ
           (b).只写 : PROT_WRITE
           (c).读写 : PROT_READ | PROT_WRITE
    flags : 映射区的特性,可以是
            (a). MAP_SHARED : 写入映射区的数据会复制回文件,且允许其他映射该文件的进程共享
            (b). MAP_PRIVATE : 对映射区的写入操作会产生一个映射区的复制(写时拷贝),对此区域所做的修改不会写回原文件
    fd : 由open返回的文件描述符,代表要映射的文件
    offset : 以文件开始的偏移量,必须是4k的整数倍,通常为0,表示从文件头开始映射
    返回值 :
            成功 : 返回创建的映射区的首地址
            失败 : 返回 MAP_FAILED 宏
    
关于mmap的使用总结 :
    (1).第一个参数写成NULL
    (2).第二个参数要映射的文件大小 > 0
    (3).第三个参数 : PROT_READ , PROT_WRITE
    (4).第四个参数 : MAP_SHARED 或 MAP_PRIVATE
    (5).第五个参数 : 打开的文件对应的文件描述符
    (6).第六个参数 : 4k的整数倍,通常为0


(2). munmap函数

#include <sys/mman.h>

int munmap(void* addr, size_t length);

功能 : 释放内存映射区

参数 :
      addr : 使用mmap函数创建的映射区首地址
      length : 映射区的大小

返回值 : 
        成功 : 0
        失败 : -1



代码示例 : 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    //1.打开要映射的文件
    int fd = -1;
    fd = open("txt", O_RDWR);
    if(-1 == fd)
    {
        perror("open");
        return 1;
    }

    //2.映射文件
    void* addr = NULL;
    addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == addr)
    {
        perror("mmap");
        return 1;
    }

    //3.关闭文件
    close(fd);

    //4.对地址操作以读写文件
    memcpy(addr, "mcbwxg", 6);

    //5.关闭映射链接
    munmap(addr, 1024);

    return 0;
}
