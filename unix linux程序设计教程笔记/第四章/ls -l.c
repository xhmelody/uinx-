
//author: melody    data: 2019 01 29
//这是一个实现查看文件权限的程序   也只是实现  ls -l的前面部分的程序  

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <string.h>


char *get_perms(struct stat *sbuf, char *perms)
{
    //每一种访问权限权限许可值对应的字符串
    static char *modes[] = {
        "---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"
    };
    int i, j;
    *perms = '\0';
    
    //分别获得三组的访问权限，用该值作为数组modes的下标，以便获得相应的字符串拼入perms
    for (i = 2; i >=0; i--)
    {
        j = (sbuf->st_mode >> (i*3)) & 07;//07 是一串0，后面1
        strcat(perms, modes[j]);
    }
    
    //处理调整ID位和sticky位
    if ((sbuf->st_mode & S_ISUID) != 0)
        perms[2] = 's';
    if ((sbuf->st_mode & S_ISGID) != 0)
        perms[5] = 's';
    if ((sbuf->st_mode & S_ISUID) != 0)
        perms[8] = 't';
    return perms;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage : %s is test file's ", argv[0]);
        exit(1);
    }
    
    struct stat buf;
    char s[30];
    for (int i = 1; i < argc; i++)
    {
        if (lstat(argv[i], &buf) < 0)
        {    
            perror(argv[i]);
            continue;
        }
        get_perms(&buf, s);
        printf("file: %s is %s\n", argv[i], s);
    }
    
    return 0;
}

