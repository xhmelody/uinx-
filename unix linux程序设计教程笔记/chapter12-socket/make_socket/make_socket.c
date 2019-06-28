

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
