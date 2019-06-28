//这个例子中len为0
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>


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


int main(void)
{
    int fd;
    off_t fdpos;
    if ((fd = open("tempfile", O_RDWR|O_CREAT, 0666)) < 0)
    {
        perror("open error\n");
        exit(0);
    }
    /* 对文件尾及其后面的扩充部分置写锁  */
    if (SET_LOCK(fd, F_WRLCK, 0, SEEK_END, 0) == -1)
        printf("%d set write lock failed\n", getpid());
    else
        printf("%d set write lock success\n", getpid());
    //定位文件位置于当前文件末尾，并写入8个字符
    fdpos = lseek(fd, 0L, SEEK_END);
    write(fd, "8 bytes.", 8);
    /* 企图释放前面设置的写锁，但实际上并未释放，因为文件尾的位置已经后移
     * 我们释放的只是相对新文件尾之后的区域，并没有释放从原文件尾置新文件尾的这一部分区域
     */
    if (un_lock(fd, 0L, SEEK_END, 0) == -1)
    {
        perror("UN_LOCK error\n");
        exit(0);
    }
    else 
    {
        printf("%d: un_lock(fd, 0, SEEK_END, 0) success\n", getpid());
    }
    //让子进程在该区域设置读锁并验证父进程是否已经正确释放其锁了
    if (vfork() == 0)
    {
        //对整个文件设置写锁，不能设置表明父进程有锁区域未释放
        if (SET_LOCK(fd, F_WRLCK, 0, SEEK_SET, 0) == -1)
            printf("%d: there are some locks on the file\n", getpid());
        else
            printf("%d: no any locks on the file\n", getpid());
        exit(0);
    }
    //父进程
    sleep(1);
    exit(0);
}
