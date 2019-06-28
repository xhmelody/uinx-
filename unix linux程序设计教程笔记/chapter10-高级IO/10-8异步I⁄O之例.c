//author: xhmelody    data: 2019 05 21

#include <stdio.h> 
#include <aio.h>
#include <stdlib.h>
#include <signal.h>

#define NBUFFERS 2                //缓冲区的个数
#define BUFFERSIZE 2048          //缓冲区的大小
#define BLOCKSIZE 1024            //每次读入的数据块的大小
#define SIG_AIO_WRITE (SIGRTMIN+5)
typedef enum { BUFFER_FREE=1. BUFFER_FILLING, BUFFER_WRITING } BUFFLAG;
typedef struct {
    BUFFLAG state;               //缓冲区的状态
    int fillpt;                  //缓冲区中最后一个数据位置
    struct aiocb acb;            //异步输出控制块
    char buffer[BUFFERSIZE];     //数据缓冲区
} buffer_t;

static buffer_t buf_list[NBUFFERS];
static sigset_t aio_completion_signal;
static volatile int sigcnt = 0, total = 0;
static off_t seek_ptr;
/*   异步输出完成信号句柄   */

void aio_ok(int signo, siginfo_t *info, void *ignored)
{
    buffer_t *donebuf;
    ssize_t rval;
    if ((signo != SIG_AIO_WRITE) || info->si_code != SI_ASYNCIO)
        return;   //非AIO完成
    else
        printf("AIO write completed\n");
    //根据info获得异步I/O相关的信息
    donebuf = (buffer_t *)info->si_value.sival_ptr;
    if ((aio_error((struct aiocb *) &donebuf->acb) != EINPROGRESS))
        rval = aio_return((struct aiocb *) &donebuf->acb);
    //累计写入的字节数和信号发生的次数，并标记缓冲区已清空
    total += rval;
    sigcnt++;
    donebuf->state = BUFFER_FREE;
    donebuf->fillpt = 0;
    return;
}

buffer_t *find_free_buf(void) //获得一个空闲的缓冲区
{
    int i;
    sigset_t prevmask;
    sigprocmask(SIG_BLOCK, &aio_completion_signal, &prevmask);
    while (1)
    {
        for (i = 0; i < NBUFFERS; i++)
        {
            if (buf_list[i].state == BUFFER_FREE)
                break;
        }
        if (i == NBUFFERS)
            sigsuspend(&prevmask);  //没有空闲缓冲区，等待某个异步输出完成后再试
        else
            break;
    }
    buf_list[i].state = BUFFER_FILLING; //找到了空闲缓冲区，标志它正被使用
    buf_list[i].fillpt = 0;
    sigprocmask(SIG_SETMASK, &prevmask, BULL);
    return (&buf_list[i]);
}




