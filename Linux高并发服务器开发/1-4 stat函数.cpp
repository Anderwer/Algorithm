stat 函数

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int stat(const char* path, struct stat* buf);

功能 : 获取文件状态信息

参数 : 
    path : 文件名
    buf : 保存文件信息的结构体

返回值 : 
    成功 : 0
    失败 : -1


struct stat 结构体说明 :

struct stat {
    dev_t st_dev; //文件的设备编号
    ino_t st_ino; //节点
    mode_t st_mode; //文件的类型和存取的权限
    nlink_t st_nlink; //连接到该文件的硬连接数,刚建立的文件值为1
    uid_t st_uid; //用户ID
    gid_t st_gid; //组ID
    dev_t st_rdev; //(设备类型)若此文件为设备类型,则为其设备编号
    off_t st_size; //文件字节数(文件大小)
    blksize_t st_blksize; //块大小(文件系统的I/O 缓冲区大小)
    blkcnt_t st_blocks; //块数
    time_t st_atime; //最后一次访问时间
    time_t st_mtime; //最后一次修改时间
    time_t st_ctime; //最后一次改变时间(指属性)
}

---------------------------------------------------------------------------------
stat 获取文件信息示例 :

  1 #include<stdio.h>
  2 #include<sys/stat.h>
  3 #include<sys/types.h>
  4 #include<string.h>
  5 #include<stdlib.h>
  6 #include<unistd.h>
  7 
  8 int main()
  9 {
 10 
 11         struct stat st;
 12 
 13         int ret = -1;
 14 
 15         ret = stat("txt", &st);
 16 
 17         if(-1 == ret)
 18         {
 19                 perror("stat");
 20                 return 1;
 21         }
 22 
 23         printf("st_dev = %lu\n", st.st_dev);
 24         printf("st_ino = %lu\n", st.st_ino);
 25         printf("st_mode = %u\n", st.st_mode);
 26         printf("st_nlink = %lu\n", st.st_nlink);
 27         printf("st_uid = %u\n", st.st_uid);
 28         printf("st_gid = %u\n", st.st_gid);
 29         printf("st_size = %lu\n", st.st_size);
 30         printf("st_blksize = %lu\n", st.st_blksize);
 31         printf("st_blkcnt = %lu\n", st.st_blocks);
 32         return 0;
 33 }                   

 --------------------------------------------------------------------------------------
 stat 获取文件类型 示例:

   2 #include<stdio.h>
  3 #include<sys/stat.h>
  4 #include<sys/types.h>
  5 #include<string.h>
  6 #include<stdlib.h>
  7 #include<unistd.h>
  8 
  9 //第一种写法
 10 int get_file_type_1(struct stat* st)
 11 {
 12         switch(st->st_mode & S_IFMT)
 13         {
 14                 //普通文件
 15                 case S_IFREG:
 16                         printf("The file is regular file\n");
 17                         break;
 18 
 19                 //目录
 20                 case S_IFDIR:
 21                         printf("The file is directory\n");
 22                         break;
 23 
 24                 //字符设备
 25                 case S_IFCHR:
 26                         printf("The file is character device\n");
 27                         break;
 28 
 29                 //块设备
 30                 case S_IFBLK:
 31                         printf("The file is block device\n");
 32                         break;
 33 
 34                 //套接字
 35                 case S_IFSOCK:
 36                         printf("The file is socket\n");
 37                         break;
 38 
 39                 //管道
 40                 case S_IFIFO:                                                        
 41                         printf("The file is FIFO\n");
 42                         break;
 43 
 44                 //符号链接
 45                 case S_IFLNK:
 46                         printf("The file is symbolic link\n");
 47                         break;
 48 
 49                 default:
 50                         printf("Unknown file types\n");
 51         }                                                                            
 52         return 0;
 53 }
 54 
 55 int get_file_type_2(struct stat* st)
 56 {
 57         //普通文件
 58         if(S_ISREG(st->st_mode)) printf("The file is regular file\n");
 59 
 60         //目录
 61         else if(S_ISDIR(st->st_mode)) printf("The file is directory\n");
 62 
 63         //字符设备
 64         else if(S_ISCHR(st->st_mode)) printf("The file is character device\n");
 65 
 66         //块设备
 67         else if(S_ISBLK(st->st_mode)) printf("The file is block device\n");
 68 
 69         //套接字
 70         else if(S_ISSOCK(st->st_mode)) printf("The file is socket\n");
 71 
 72         //管道
 73         else if(S_ISFIFO(st->st_mode)) printf("The file is FIFO\n");
 74 
 75         //符号链接
 76         else if(S_ISLNK(st->st_mode)) printf("The file is symbolic link\n");
 77 
 78         //未知文件类型
 79         else printf("Unknown file types\n");
 80 
 81         return 0;
 82 }
 83 int main(int argc, char** argv)
 84 {
 85         int ret = -1;
 86         struct stat st;
 87 
 88         //容错判断
 89         if(2 != argc)
 90         {
 91                 printf("usage ./a.out filename\n");
 92                 return 1;
 93         }
 94 
 95         ret = stat(argv[1], &st);
 96         if(-1 == ret)
 97         {
 98                 perror("stat");
 99                 return 1;
100         }
101 
102         get_file_type_1(&st);
103 
104         get_file_type_2(&st);
105         return 0;
106 }

-------------------------------------------------------------------------------------

stat 查询文件权限 示例:

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int get_owner_permission(struct stat* st)
{
    if(st->st_mode & S_IRUSR) printf("r");
    else printf("-");

    if(st->st_mode & S_IWUSR) printf("w");
    else printf("-");

    if(st->st_mode & S_IXUSR) printf("x");
    else printf("-");

    return 1;
}

int get_group_permission(struct stat* st)
{
    if(st->st_mode & S_IRGRP) printf("r");
    else printf("-");

    if(st->st_mode & S_IWGRP) printf("w");
    else printf("-");

    if(st->st_mode & S_IXGRP) printf("x");
    else printf("-");

    return 1;
}

int get_other_permission(struct stat* st)
{
    if(st->st_mode & S_IROTH) printf("r");
    else printf("-");

    if(st->st_mode & S_IWOTH) printf("w");
    else printf("-");

    if(st->st_mode & S_IXOTH) printf("x");
    else printf("-");

    return 1;
}

int main(int argc, char** argv)
{

    int ret = -1;
    struct stat st;

    if(2 != argc)
    {
        printf("usage: ./a.out filename\n");
        return 1;
    }

    ret = stat(argv[1], &st);

    if(-1 == ret)
    {
        perror("stat");
        return 1;
    }

    get_owner_permission(&st);
    get_group_permission(&st);
    get_other_permission(&st);
    putchar('\n');
    return 0;
}

-------------------------------------------------------------------------------------

