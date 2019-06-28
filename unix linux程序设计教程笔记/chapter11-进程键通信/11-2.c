//连接标准输出的管道

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define PIPE_BUF 256

int main(void)
{
    int pid, fd[2], len;
    char buffer[PIPE_BUF];
    char some_data[PIPE_BUF];
    FILE *stream;
    if (pipe(fd) != 0)
    {
        perror("pipe creation failed\n");
        exit(1);
    }
    if ((pid = fork()) == 0)
    {
        close(fd[1]);   //不使用管道的输出端   子进程关闭管道的输出端
        dup2(fd[0], 0);  //关闭stdin，重定向管道的输入端至stdin
        close(fd[0]);  //关闭这个不再有用的描述字
        
        read(fd[0], some_data, strlen(some_data));
        
        printf("%s\n", some_data);
        
        /*
        //子进程执行cat命令来显示文件
        if (execl("/bin/cat", "cat", NULL, NULL) == -1)
        {
            perror("Unable to run cat\n");
            exit(0);
        }
        */
    } else {
        close(fd[0]);  //不使用管道的输入端
        printf("you can type a line and the line will echoed:\n");
        dup2(fd[1], 1);  //关闭stdout，重定向管道的输出端至stdout
        close(fd[1]);
        while (gets(buffer) != NULL)
            puts(buffer);   //被重定向了   所有这里操作的是管道
    }
    
}
