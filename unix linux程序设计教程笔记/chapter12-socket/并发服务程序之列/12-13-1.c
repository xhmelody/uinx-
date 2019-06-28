#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>


void doit(int);
int make_socket(int type, unsigned short int port);

int main(void)
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in client_address;
    server_sockfd = make_socket(SOCK_STREAM, 2003);
    /*   创建连接队列，忽略子进程终止信号，为了防止僵尸进程   */
    listen(server_sockfd, 5);
    signal(SIGCHLD, SIG_IGN);   /*   为了防止僵尸进程  */
    while (1)
    {
        printf("server waiting\n");
        /*   接收连接  */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        /*   为这个客户创建一个子进程   */
        if (fork() == 0)  /*子进程*/
        {
            close(server_sockfd);//关闭帧听套接字
            doit(client_sockfd);//处理程序请求
            close(client_sockfd);//关闭连接套接字
            exit(0);
        } else {
            close(client_sockfd);
        }
    }
}

void doit(int client_sockfd)
{
    char buf[256];
    int n;
    /*  接收并回应客户的消息  */
    n = read(client_sockfd, buf, sizeof(buf));
    buf[n] = 0;
    sleep(1);   /*  模拟服务工作时间  */
    write(client_sockfd, buf, n);
}

int make_socket(int type, unsigned short int port)
{
    int sock;
    struct sockaddr_in name;
    /*  创建套接字  */
    if ((sock = socket(AF_INET, type, 0)) < 0)
    {
        perror("socket failed!");
        exit(1);
    }
    /*  命名该套接字  */
    name.sin_family = AF_INET;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);  //任意的合法地址
    if (bind(sock, (struct sockaddr *)&name, (socklen_t)sizeof(name)) < 0)
    {
        perror("bind failed!");
        exit(1);
    }
    return sock;
    
}
