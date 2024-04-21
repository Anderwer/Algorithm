errno 是记录系统的最后一次错误代码.代码是一个int类型,在errno.h中定义,查看错误代码errno是调试中的一个重要方法

当Linux C api函数发生异常时,一般会将errno全局变量赋一个整数值,不同的值有不同的含义,可以通过查看该值推断错误原因

测试程序:

  1 #include<stdio.h>
  2 #include<errno.h>
  3 #include<string.h>
  4 
  5 int main()                                                                                                                                                                                           
  6 {
  7         FILE* fp = fopen("xxxx","r");
  8         if(NULL == fp)
  9         {
 10                 printf("%d\n",errno);
 11                 printf("%s\n",strerror(errno));
 12                 perror("fopen err");
 13         }
 14         return 0;
 15 }

