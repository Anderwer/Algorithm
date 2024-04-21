
1. getcwd 函数

#include<unistd.h>

char* getcwd(char* buf, size_t size)

功能: 获取当前进程的工作目录

参数: 
    buf : 缓冲区,存储当前的工作目录
    size : 缓冲区大小

返回值:
    成功 : buf中保存当前进程工作目录的位置
    失败 : NULL

-------------------------------------------------------------------------
2. chdir 函数

#include<unistd.h>

int chdir(const char* path)

功能: 修改当前进程(应用程序)的路径

参数: 
    path : 切换的路径

返回值:
    成功 : 0
    失败 : -1

-----------------------------------------------------------------------------
3. opendir 函数

#include<sys/types.h>
#include<dirent.h>

DIR* opendir(const char* name)

功能: 打开一个目录

参数: 
    name : 目录名

返回值:
    成功 : 返回指向该目录结构体指针
    失败 : NULL

--------------------------------------------------------------------------------
4. closedir 函数

#include<sys/types.h>
#include<dirent.h>

int closedir(DIR* dirp)

功能: 关闭目录

参数:
    dirp : opendir 返回的指针

返回值:
    成功 : 0
    失败 : -1

-----------------------------------------------------------------------------------
5. readdir 函数

#include<dirent.h>

struct dirent* readdir(DIR* dirp)

功能: 读取目录

参数:
    dirp : opendir 返回的指针

返回值:
    成功 : 目录结构体指针
    失败 : NULL

相关结构体说明:
struct dirent
{
    ino_t d_ino; //此目录进入点的inode
    off_t d_off; //目录文件开头至此目录进入点的位移
    signed short int d_reclen; //d_name 的长度,不包含NULL字符
    unsigned char d_type; //d_type 所指的文件类型
    char d_name[256]; //文件名
}

d_type 文件类型说明:

DT_BLK    块设备
DT_CHR    字符设备
DT_DIR    目录
DT_LNK    软链接
DT_FIFO   管道
DT_REG    普通文件
DT_SOCK   套接字
DT_UNKNOWN 未知

-------------------------------------------------------------------------------
特定目录下查询该目录包含哪些文件及文件类型 示例:

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

int main(int argc, char** argv)
{
    DIR* d = NULL;
    struct dirent* st = NULL;
    if(2 != argc)
    {
        printf("usage ./a.out dirname\n");
        return 1;
    }

    d = opendir(argv[1]);
    if(d == NULL)
    {
        perror("opendir");
        return 1;
    }

    while((st = readdir(d)) && st != NULL)
    {
        switch(st->d_type)
        {
            case DT_BLK:
                printf("block device        ");
                break;
            case DT_CHR:
                printf("character device        ");
                break;
            case DT_DIR:
                printf("directory        ");
                break;
            case DT_FIFO:
                printf("named pipe        ");
                break;
            case DT_LNK:
                printf("symbolic link       ");
                break;
            case DT_REG:
                printf("regular file        ");
                break;
            case DT_SOCK:
                printf("UNIX domain sock        ");
                break;
            default: printf("Unknown        ");
        }
        printf("%s\n", st->d_name);
    }
    return 0;
}
