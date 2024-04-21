
1. open 函数

  #include<sys/types.h>
  #include<sys/stat.h>
  #include<fcntl.h>
   
  int open(const char *pathname, int flags);
  int open(const char *pathname, int flags, mode_t mode);
  功能:
    打开文件,如果文件不存在则可以选择创建

  参数:
    pathname : 文件路径及文件名
    flags : 打开文件的行为标志, 必选项 O_RDONLY, O_WRONLY, O_RDWR;
    mode : 这个参数,只有在文件不存在时才有效,用于新建文件时指定文件的权限

  返回值:
    成功 : 返回打开文件的文件描述符
    失败 : 返回-1

  flags详细说明 :
  必选项:

  O_RDONLY   以只读的方式打开
  O_WRONLY   以只写的方式打开
  O_RDWR     以可读可写的方式打开

  可选项: 和必选项按位或

  O_CREAT    文件不存在则创建文件,使用此选项时需要使用mode说明文件的权限
  O_EXCL     如果同时指定了O_CREAT,且文件已经存在,则报错
  O_TRUNC    如果文件存在,则清空文件内容
  O_APPEND   写文件时,数据添加到文件末尾
  O_NONBLOCK 对于设备文件,以O_NONBLOCK打开可以做非阻塞I/O


2.close 函数
  #include<unistd.h>

  int close(int fd);
  功能:
    关闭已打开的文件

  参数:
    fd : 文件描述符/ open()的返回值

  返回值:
    成功 : 0
    失败 : -1, 并设置errno

  需要说明的是,当一个进程终止时,内核对该进程所有未被关闭的文件描述符调用close关闭,所以即使
  程序不调用close,在终止时内核也会自动关闭它打开的文件

  但是对于一个常年运行的程序(如服务器),打开的文件描述符一定记得要关闭,否则随着打开的文件越来
  越多,会占用大量文件描述符和系统资源


open 和 close 示例:

  #include<stdio.h>
  #include<string.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include<unistd.h>
  7 
  8 int main()
  9 {
 10         int fd = -1;
 11 
 12 //      1. 以只读的方式打开文件,如果文件不存在则报错
 13 //      fd = open("txt", O_RDONLY);
 14 
 15 
 16 //      2. 以只写的方式打开文件,如果文件存在就打开,文件不存在就新建
 17 //      fd = open("txt", O_WRONLY | O_CREAT , 0644);
 18 
 19 //      3. 以只写的方式打开文件,如果文件存在就报错,文件不存在就新建
 20 //      fd = open("txt", O_WRONLY | O_EXCL | O_CREAT , 0644);
 21 
 22 //      4. 以读写的方式打开文件,如果文件存在就打开,文件不存在就新建
 23 //      fd = open("txt", O_RDWR | O_CREAT , 0644);
 24 
 25 //      5. O_TRUNC 清空文件内容
 26 //      如果文件不存在就新建文件,如果文件存在就打开后清空
 27 //      fd = open("txt", O_WRONLY | O_CREAT | O_TRUNC , 0644);
 28 
 29 //      6. O_APPEND 追加的方式
 30 //      以只写的方式和追加的方式打开文件,如果文件不存在则报错
 31         fd = open("txt", O_WRONLY | O_APPEND);
 32 
 33         if(-1 == fd)
 34         {
 35                 perror("open");
 36                 return 1;
 37         }
 38                                                                                      
 39         printf("fd = %d\n", fd);
 40         
 41         close(fd);
 42         return 0;
 43 }

3.write 函数

  #include<unistd.h>
  ssize_t write(int fd, const void* buf, size_t len)
  功能 :
    把指定数目的数据写到文件(fd)

  参数 :
    fd : 文件描述符
    buf : 数据首地址
    len : 写入数据的长度(字节)

  返回值 :
    成功 : 实际写入数据的字节个数
    失败 : -1


write 示例 :

  1 #include<stdio.h>
  2 #include<string.h>
  3 #include <sys/types.h>
  4 #include <sys/stat.h>
  5 #include <fcntl.h>
  6 #include<unistd.h>
  7 
  8 int main()
  9 {
 10         int fd = -1;
 11         int ret = -1;
 12         char* str = "hello world";
 13         //1.只写打开文件
 14         fd = open("txt", O_WRONLY | O_CREAT, 0644);
 15 
 16         if(-1 == fd)
 17         {
 18                 perror("open");
 19                 return 1;
 20         }
 21 
 22         //2.写入文件
 23         ret = write(fd, str, strlen(str));
 24 
 25         if(-1 == ret)
 26         {
 27                 perror("write");
 28                 return 1;
 29         }
 30         
 31         printf("%d\n", ret);
 32         //3.关闭文件
 33         close(fd);
 34 
 35 } 


4.read 函数
  
  #include<unistd.h>
  
  ssize_t read(int fd, void* buf, size_t len)

  功能 :
    把指定数目的数据读到内存(缓冲区)

  参数 :
    fd : 文件描述符
    buf : 内存首地址
    len : 读取的字节个数

  返回值 :
    成功 : 实际读取到的字节个数
    失败 : -1

read 示例 :

  1 #include<stdio.h>
  2 #include<string.h>
  3 #include <sys/types.h>
  4 #include <sys/stat.h>
  5 #include <fcntl.h>
  6 #include<unistd.h>
  7 #define SIZE 128
  8 
  9 int main()
 10 {
 11         int fd = -1;
 12         int ret = -1;
 13         char buf[SIZE];
 14         //1.只读打开文件
 15         fd = open("txt", O_RDONLY);
 16 
 17         if(-1 == fd)
 18         {
 19                 perror("open");
 20                 return 1;
 21         }
 22 
 23         //2.读文件
 24 
 25         memset(buf, 0, SIZE);
 26         ret = read(fd, buf, SIZE);
 27 
 28         if(-1 == ret)
 29         {
 30                 perror("write");
 31                 return 1;
 32         }
 33 
 34         printf("read len = %d\n", ret);
 35         printf("%s\n", buf);
 36 
 37         //3.关闭文件
 38         close(fd);
 39 
 40 } 


 5.lseek 函数

  #include<sys/types.h>
  #include<unistd.h>

  off_t lseek(int fd, off_t offset, int whence);

  功能 :
    改变文件的偏移量

  参数 :
    fd : 文件描述符
    offset : 根据whence来移动的位移数(偏移量),可以是正数,也可以是负数,
    如果正数,则相对于whence向右移动,如果是负数,则向左移动.如果向前移动
    的字节数超过了文件开头则出错返回,如果向后移动的字节数超过文件末尾,
    再次写入时将增大文件尺寸.

    whence : 其取值如下
      SEEK_SET : 从文件开头移动offset个字节
      SEEK_CUR : 从当前位置移动offset个字节
      SEEK_END : 从文件末尾移动offset个字节

    返回值 :
      若lseek成功执行,则返回新的偏移量
      如果失败,返回-1

  
lseek 示例 :

  1 #include<stdio.h>
  2 #include<string.h>
  3 #include<stdlib.h>
  4 #include<sys/types.h>
  5 #include<sys/stat.h>
  6 #include<fcntl.h>
  7 #include<unistd.h>
  8 #define SIZE 128
  9 
 10 int main()
 11 {
 12 
 13         int fd = -1;
 14         int ret = -1;
 15         char str[SIZE];
 16 
 17         //1.打开文件
 18 
 19         fd = open("txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
 20 
 21         if(-1 == fd)
 22         {
 23                 perror("open");
 24                 return 1;
 25         }
 26 
 27         write(fd, "ABCDEFG", 7);
 28         //2.lseek操作
 29 
 30         ret = lseek(fd, 32, SEEK_SET);
 31 
 32         if(-1 == ret)
 33         {
 34                 perror("lseek");
 35                 return 1;
 36         }
 37 
 38         write(fd, "123456789", 9);
 39 
 40         memset(str, 0, SIZE);                                                        
 41 
 42         //将文件位置指针置于开头
 43         lseek(fd, 0, SEEK_SET);
 44         ret = read(fd, str, SIZE);
 45 
 46         printf("read len = %d\n", ret);
 47 
 48         printf("read = %s\n", str);
 49         //3.关闭文件
 50 
 51         close(fd);
 52 
 53         return 0;
 54 }

