// author: melody   data: 2019 01 29

//这是一个形成文件访问权限字符串的函数，类似与实现 ls -l的前面答应部分


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

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

