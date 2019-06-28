
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
