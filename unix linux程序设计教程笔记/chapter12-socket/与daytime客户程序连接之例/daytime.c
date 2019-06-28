#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define MAXBUFFSIZE 256

//只有本机是ipv4的协议才能初始化，不然就会是无法识别的协议
void init_sockaddr(struct sockaddr_in *name, const char *hostname, const char *serv);

int socket_connect(char *hostname, char *serv_port);


int main(int argc, char **argv)
{
    
    int sockfd, n;
    char recvbuff[MAXBUFFSIZE], *host;
    struct sockaddr_in servaddr;
    if (argc < 2)
        host = NULL;
    else
        host = argv[1];
    socket_connect(host, "13");
    /*   读取该服务的回答并且显示   */
    while ((n = read(sockfd, recvbuff, MAXBUFFSIZE)) > 0)
    {
        recvbuff[n] = 0;  //填入终止符
        fputs(recvbuff, stdout);
    }
    if (n < 0)
    {
        perror("read error!");
        exit(1);
    }
    
    exit(0);
}


//只有本机是ipv4的协议才能初始化，不然就会是无法识别的协议
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

int socket_connect(char *hostname, char *serv_port)
{
    int sockfd;
    struct sockaddr_in saddr;
    struct hostent *hp;
    char *host, myname[104];
    /*   初始化服务器的ip地址和端口   */
    init_sockaddr(&saddr, hostname, serv_port);
    /*   创建套接字   */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error!");
        exit(1);
    }
    
    //与本机建立连接    saddr里面初始化的都是本机的信息   本机的ip协议和本机的地址长度
    if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("connect error!");
        exit(1);
    }
    return (sockfd);
}




