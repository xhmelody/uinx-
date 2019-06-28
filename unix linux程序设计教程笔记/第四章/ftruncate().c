#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    long int length;
    int fd;
    char *cp;
    if (argc != 3)
    {
        printf("usage: a.out <filename> <file size>\n");
        exit(1);
    }
    
    //读取参数并打开文件   这个函数用于把字符串按照后面给出的进制转化
    length = strtol(argv[2], &cp, 10);
    if (cp == argv[2])//第二个参数非数字
    {
        printf("usage: a.out <filename> <file size> and"
            "<file size> must be a integer\n"
        );
        exit(1);
    }
    
    if ((fd = open(argv[1], O_RDWR)) < 0)
        perror("open() call failed");
    //按照第二个参数来截断文件
    printf("truncate %s to %d characaters\n", argv[1], length);
    if (ftruncate(fd, length) < 0)
        perror("truncate() call failed");
    printf("truncate() call successful\n");
    lessk(fd, (long)0, SEEK_END);
    write(fd, "@T", 2);
    close(fd);
    
    
    return 0;
}


