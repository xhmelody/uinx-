// author: melody      data: 2019 01 29

//这是一个使用access函数的程序，这里只用于测试了文件的读权限
//还有W_OK测试写权限       X_OK执行权限      F_OK文件是否存在

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: a.out < filename>\n");
        exit(1);
    }
    
    if (access(argv[1], R_OK) < 0)
    {
        printf("access error for %s.", argv[1]);
        if (errno == EACCES)
            printf("you are not the owner of this file!\n");
    }
    else
        printf("read access OK\n");
    if (open(argv[1], O_RDONLY) < 0)
        printf("open error for %s\n", argv[1]);
    else
        printf("open for reading OK\n");
    
    exit(0);
}
