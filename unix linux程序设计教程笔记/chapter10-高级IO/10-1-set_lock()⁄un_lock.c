#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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
