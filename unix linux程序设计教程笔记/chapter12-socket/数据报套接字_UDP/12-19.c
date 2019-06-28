#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXMSG 512

void init_sockaddr(struct sockaddr_in *name, const char *hostname, const char *serv);

int main(int argc, char **argv)
{
    int sock, n;
    struct sockaddr_in name;
    struct hostent *hp;
    
    //得到本主机的名字并打印
    char hostName[512];
    gethostname(hostName, sizeof(hostName));
    printf("hostName is %s\n", hostName);
    
    char sndmsg[MAXMSG], recvmsg[MAXMSG];
    if (argc < 3)
    {
        fprintf(stderr, "Usage: a.out <hostname> <port>\n");
        exit(1);
    }
    //创建数据报套接字
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("opening datagram socket error\n");
        exit(1);
    }
    //形成发送目的套接字地址
    init_sockaddr(&name, argv[1], argv[2]);
    while (1)
    {
        printf("please enter any string: ");
        fgets(sndmsg, MAXMSG, stdin);
        if (sndmsg[0] == '\n')
            break;
        //发送信息  信息由终端输入
        if (sendto(sock, sndmsg, sizeof(sndmsg), 0, (struct sockaddr*)&name, sizeof(name)) < 0)
        {
            perror("(client) sending error\n");
            exit(1);
        }
        //接收并显示服务返回的回答
        if ((n = recvfrom(sock, recvmsg, MAXMSG, 0, NULL, NULL)) < 0)
        {
            perror("(client) receive error\n");
            exit(1);
        }
        recvmsg[n] = 0;
        printf("I recrived echo: %s", recvmsg);
    }
    close(sock);
    exit(0);
}


void init_sockaddr(struct sockaddr_in *name, const char *hostname, const char *serv)
{
    struct hostent *hp;
    char *host, myname[255];
    if (hostname == NULL)  //如果传入的主机名为空，那么就获取本主机名
    {
        gethostname(myname, sizeof(myname));
        host = myname;
    }
    else
        host = hostname;
    if ((hp = gethostbyname(host)) == NULL)  //通过主机名得到本主机的信息
    {
        printf("Unknown host: %s\n", host);
        exit(-1);
    }
    /*   初始化地址  填入服务器的IP地址和端口   */
    bzero(name, sizeof(struct sockaddr));
    if (hp->h_addrtype == AF_INET)      //只认识ipv4协议
    {
        name->sin_family = AF_INET;
        bcopy(hp->h_addr_list[0], &name->sin_addr, hp->h_length);
        if (serv == NULL)   //传入的端口为空
            name->sin_port = htons(0);  //由系统选择一个适当的端口   由本机字节序转换成网络字节序
        else
            name->sin_port = htons(atoi(serv));   //先转整形，再转网络字节序
    } else {
    
        printf("Unknown address type\n");
        exit(1);
    }
}
 
