
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTENQ 5
#define MAXLINE 512

int make_socket(int type, unsigned short int port);


int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    time_t ticks;
    /*   创建并命名套接字，5013为服务端口   */
    listenfd = make_socket(SOCK_STREAM, 5013);
    listen(listenfd, LISTENQ);   /*   创建帧听队列   */
    /*   连接处理   */
    for ( ; ; )
    {
        len = sizeof(cliaddr);
        /*   接收连接   */
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
        /*   打印出连接客户的ip地址    */
        printf("connect from %s, port %d\n", inet_ntoa((struct in_addr)cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        /*    向客户报告时间   */
        ticks = time(NULL);
        sprintf(buff,"%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);    /*   关闭连接套接字   */
    }
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
