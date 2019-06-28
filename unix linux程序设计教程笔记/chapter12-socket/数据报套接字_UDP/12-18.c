#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXMSG 1024

int make_socket(int type, unsigned short int port);


int main(void)
{
    int sock, size, nbytes;
    struct sockaddr_in name;
    char message[MAXMSG];
    //创建数据报套接字
    sock = make_socket(SOCK_DGRAM, 0);
    //查出并打印系统赋给的端口值
    size = sizeof(name);
    
    //获取本地套接字
    if (getsockname(sock, (struct sockaddr *)&name, (socklen_t *)&size))
    {
        perror("getting sock name\n");
        exit(1);
    }
    else {
        printf("getting sock name failed!\n");
    }
    printf("Socket has port #%d\n", ntohs(name.sin_port));
    while(1)
    {
        //从套接字读数据
        size = sizeof(name);
        nbytes = recvfrom(sock, message, MAXMSG, 0, (struct sockaddr*)&name, (socklen_t *)&size);
        if (nbytes < 0)
        {
            perror("recfrom (server) failed!\n");
            exit(1);
        }
        //打印出收到的消息
        printf("Server got message: %s\n", message);
        //将消息返回给发送者
        nbytes = sendto(sock, message, nbytes, 0, (struct sockaddr*)&name, size);
        if (nbytes < 0)
        {
            perror("sendto (server) failed!\n");
            exit(1);
        }
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
