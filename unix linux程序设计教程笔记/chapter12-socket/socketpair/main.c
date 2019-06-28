#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

#define DATA1 "Fine,thanks." 
#define DATA2 "Hello,how are you?"

int main(void)
{
    int sockets[2], child;
    char buf[1024];
    //创建套接字偶对
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0)
        exit(0);
    //创建子进程
    if ((child = fork()) == -1)
        exit(0);
    if (child != 0)//fu
    {
        close(sockets[0]);//关闭子进程的套接字
        if (read(sockets[1], buf, sizeof(buf)) < 0)
            exit(0);
        printf("parent %d received request: %s\n", getpid(), buf);
        //向子进程写消息
        //if (write(sockets[1], DATA1, sizeof(DATA1)) < 0)
            //exit(0);
        close(sockets[1]);     //通信结束
    } else {
    
        close(sockets[1]);//关闭父进程的套接字
        if (write(sockets[0], DATA2, sizeof(DATA2)) < 0)
            exit(0);
        //读取来自父进程的消息
        if (read(sockets[0], buf, sizeof(buf)) < 0)
            exit(0);
        printf("child process %d received answer: %s\n", getpid(), buf);
        close(sockets[0]);//通信结束
    }
}
