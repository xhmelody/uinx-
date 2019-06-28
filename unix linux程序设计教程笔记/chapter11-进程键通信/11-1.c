//父进程通过管道向子进程发送数据

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    pid_t pid;
    int n, mypipe[2];
    char buffer[BUFSIZ + 1], some_data[] = "Hello, world!";
    if (pipe(mypipe))
    {
        perror("Pipe failed.\n");
        exit(0);
    }
    //派生子进程
    if ((pid = fork()) == (pid_t)0)
    {
        close(mypipe[1]);  //子进程关闭管道输出端
        n = read(mypipe[0], buffer, BUFSIZ);
        printf("child %d: read %d bytes: %s\n", getpid(), n, buffer);
    } else {
        close(mypipe[0]);   // 父进程关闭管道输入端
        n = write(mypipe[1], some_data, strlen(some_data));
        printf("parent %d: write %d bytes: %s\n", getpid(), n, some_data);
    }
    exit(1);
}
