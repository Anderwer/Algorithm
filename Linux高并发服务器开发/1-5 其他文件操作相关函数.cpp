1. stat 函数 : 1-4介绍

-----------------------------------------------------------------
2. access 函数:

#include<unistd.h>

int access (const char* path, int mode)

功能: 测试指定文件是否具有某种属性

参数:
    path : 文件名
    mode : 文件权限,4种权限
        R_OK : 是否有读权限
        W_OK : 是否有写权限
        X_OK : 是否有执行权限
        F_OK : 检测文件是否存在

返回值:
    0 : 有某种权限,或者文件存在
    -1 : 没有权限,或者文件不存在

-------------------------------------------------------------------
3. chmod 函数:

#include<sys/stat.h>

int chmod(const char* path, mode_t mode)

功能: 修改文件权限

参数: 
    path : 文件名
    mode : 权限(8进制)

返回值:
    成功 : 0
    失败 : -1

------------------------------------------------------------------------
4. chown 函数

#include<unistd.h>

int chown(const char* path, uid_t owner, gid_t group)

功能: 修改文件所有者和所属组

参数: 
    path : 文件名
    owner : 文件所有者id, 通过查看 /etc/passwd 得到所有者id
    group : 文件所属组id, 通过查看 /etc/group 得到用户组id

返回值:
    成功 : 0
    失败 : -1

-------------------------------------------------------------------------
5. truncate 函数

#include<unistd.h>
#include<sys/types.h>

int truncate(const char* path, off_t length)

功能: 修改文件大小

参数:
    path : 文件名
    length : 指定的文件大小(比原来小则删掉后面部分,比原来大就向后扩展)
        
返回值:
    成功 : 0
    失败 : -1

-----------------------------------------------------------------------------
6. link 函数

#include<unistd.h>

int link(const char* oldpath, const char* newpath)

功能: 创建一个硬链接

参数:
    oldpath : 源文件名字
    newpath : 硬链接名字

返回值:
    成功 : 0
    失败 : -1

-----------------------------------------------------------------------------
7. symlink 函数

#include<unistd.h>

int symlink(const char* target, const char* linkpath)

功能: 创建一个软链接

参数: 
    target : 源文件名字
    linkpath : 软链接名字

返回值:
    成功 : 0
    失败 : -1

-------------------------------------------------------------------------------
8. readlink 函数

#include<unistd.h>

ssize_t readlink(const char* path, char* buf, size_t bufsize)

功能: 读软链接相应的文件名,不是读内容(该函数只能读软链接文件)

参数:
    path : 软链接名
    buf : 存放软链接对应的文件名
    bufsize : 缓冲区大小(第二个参数存放的最大字节数)

返回值:
    成功 : >0,读到buf中的字节数
    失败 : -1

----------------------------------------------------------------------------------
9. unlink 函数

#include<unistd.h>

int unlink(const char* path)

功能: 删除一个文件(软硬链接文件)

参数: 
    path : 删除的文件名字

返回值:
    成功 : 0
    失败 : -1

-----------------------------------------------------------------------------------
10. rename 函数

#include<stdio.h>

int rename(const char* oldpath, const char* newpath)

功能: 把oldpath 的文件名改为 newpath

参数:
    oldpath : 旧文件名
    newpath : 新文件名

返回值:
    成功 : 0
    失败 : -1

