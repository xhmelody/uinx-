
//这是一个创建和命名文件名套接字的函数   即UNIX通信域

#include <stdio.h>

int make_un_socket(int type, const char *fileName)
{
    struct sockaddr_un name;
    int sock;
    socket_t size;
    /*  创建套接字  */
    scok = socket(AF_UNIX, type, 0);
    if (sock < 0)
    {
        perror("socket failed!");
        exit(1);
    }
    /* 命名套接字 */
    name.sun_family = AF_UNIX;
    strcpy(name.sun_path, fileName);
    /*  地址的大小是文件名开始的偏移与其长度之和加1(用终止的空字节)   */
    size = sizeof(struct sockaddr_un) + 1;
    if (bind(sock, (struct socketaddr *)&name, size) < 0)
    {
        perror("bind failed!");
        exit(2);
    }
    return sock;
}
