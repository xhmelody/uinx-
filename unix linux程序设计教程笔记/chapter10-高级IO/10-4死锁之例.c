#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>   //strerror函数

#define SET_LOCK(DF, TYPE, OFFSET, WHENCE, LEN)\
set_lock(DF, TYPE, OFFSET, WHENCE, LEN, 0)

#define SET_LOCKW(DF, TYPE, OFFSET, WHENCE, LEN)\
set_lock(DF, TYPE, OFFSET, WHENCE, LEN, 1)

/* w为非0的时候，表示请求指定的锁，并等待直至请求完成  会阻塞的*/

int set_lock(int fd, int type, off_t offset, int whence, off_t len, int w)
{
    struct flock lock;
    if (type != F_RDLCK && type != F_WRLCK)
    {
        fprintf(stderr, "illegal lock type\n");
        return -1;
    }
    lock.l_type = type;
    lock.l_whence = whence;
    lock.l_start = offset;
    lock.l_len = len;
    lock.l_pid = -1;
    if (w)    //请求指定的锁并等待直至请求成功
    {
        return (fcntl(fd, F_SETLKW, &lock));
    }
    if (fcntl(fd, F_GETLK, &lock) < 0)
    {
        perror("F_GETLK failed\n");
        exit(0);
    }
    if (lock.l_type == F_UNLCK)
    {
        lock.l_type = type;
        return (fcntl(fd, F_SETLK, &lock));
    }
    return -1;
}

//释放指定的区域中自己曾经设置过的锁
int un_lock(int fd, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = whence;
    lock.l_start = offset;
    lock.l_len = len;
    return (fcntl(fd, F_SETLK, &lock));
}


static void lockabyte(const char *, int, off_t);

int main(void)
{
    int fd;
    pid_t pid;
    if ((fd = creat("templock", 0666)) < 0)
    {
        perror("create error\n");
        exit(1);
    }
    write(fd, "ab", 2);
    if ((pid = fork()) == 0)
    {
        lockabyte("child", fd, 1);
        sleep(2);
        lockabyte("parent", fd, 2);
    }
    else
    {
        lockabyte("parent", fd, 2);
        sleep(2);
        lockabyte("child", fd, 1);
    }
    exit(1);
}

static void lockabyte(const char *name, int fd, off_t offset)
{
    if (SET_LOCKW(fd, F_WRLCK, offset, SEEK_SET, 1) < 0)
    {
        printf("%s: unable to set clock on byte %d, %s\n", name, (int)offset, strerror(errno));
        exit(1);
    }
    printf("%s: set lock on byte %d success\n", name, (int)offset);
}
