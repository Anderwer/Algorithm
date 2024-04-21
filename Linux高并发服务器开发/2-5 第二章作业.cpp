1. 编写测试程序,测试fork 之前打开文件,父子进程之间是否共享文件
提示:   子进程write 父进程read

2. 多进程编程
父进程fork三个子进程
一个调用ps命令
一个调用自定义应用程序
一个调用会出现段错误的程序

父进程回收三个子进程(waitpid),并且打印三个子进程的退出状态

3. 文件操作
统计出指定目录中普通文件的个数(递归)

-----------------------------------------------------------------------------
作业 1 :

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 128
int main()
{   
    int fd = -1;
    int ret = -1;
    char buf[SIZE];
    fd = open("txt", O_RDWR | O_CREAT, 0644);
    if(-1 == fd)
    {
        perror("open");
        return 1;
    }
    memset(buf, 0, SIZE);
    ret = fork();
    if(-1 == ret)
    {
        perror("fork");
        return 1;
    }
    
    if(0 == ret)
    {
        write(fd, "ABCDE", 5);
        lseek(fd, 0, SEEK_SET);
        exit(0);
    }
    
    sleep(1);
    read(fd, buf, SIZE);
    printf("%s\n", buf);
    close(fd);
    return 0;
}  

-----------------------------------------------------------------------------
作业2 :

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 128
int main()
{
    int i = 0;
    int ret = -1;
    int status = -1;
    pid_t pid = -1;
    for(i = 0; i < 3; i++)
    {
        pid = fork();
        if(0 == pid) //进入子进程 
        {
            if(i == 0)
            {
                char* argv[] = {"ps", "-a", NULL};
                execvp("ps", argv);
                exit(getpid());
            }
            else if(i == 1)
            {
                char* argv[] = {"2_work", NULL};
                execvp("./2_work", argv);
                exit(getpid());
            }
            else if(i == 2)
            {
                char* argv[] = {"test", NULL};
                execvp("./test", argv);
                exit(getpid());
            }
        }
        else
        {
            ret = waitpid(pid, &status, 0);
            if(ret == -1)
            {
                perror("waitpid");
                return 1;
            }
            if(WIFEXITED(status)) printf("%d号进程正常结束,编号: %d\n", i, WEXITSTATUS(status));

            else if(WIFSIGNALED(status)) printf("%d号进程因为信号%d而异常终止\n", i, WTERMSIG(status));
        }
    }
    return 0;
}

------------------------------------------------------------------------------------------------------------
作业 3:

#include<dirent.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 1024

void dfs(const char* path,int* cnt)
{
    DIR* d = opendir(path);
    if(d == NULL) return;
    struct dirent* st = NULL;
    char now_path[SIZE];
    while((st = readdir(d)) && st != NULL)
    {
        if(strcmp(st->d_name, ".") == 0 || strcmp(st->d_name, "..") == 0) continue;

        snprintf(now_path, SIZE, "%s/%s", path, st->d_name);
        if(st->d_type == DT_DIR) dfs(now_path, cnt);
        else if(st->d_type == DT_REG) (*cnt)++;
    }
    closedir(d);
}

int main(int argc, char** argv)
{
    if(2 != argc)
    {
        printf("usage ./a.out dirname\n");
        return 1;
    }
    DIR* d = NULL;
    int cnt = 0;
    dfs(argv[1], &cnt);
    printf("该目录下普通文件数量:%d\n", cnt);
    return 0;
}
