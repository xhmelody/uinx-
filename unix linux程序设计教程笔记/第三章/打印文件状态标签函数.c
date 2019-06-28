#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int display_file_status_flages(int fd)
{
	int accmode, val;
	//获取文件状态标签
	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		exit(0);
	//截取文件访问方式标志
	accmode = val & O_ACCMODE;
	if (accmode == O_RDONLY)
		printf("read only");
	else if (accmode = O_WRONLY)
		printf("write only");
	else if (accmode = O_RDWR)
		printf("read write");
	else
	{
		printf("unknown access mode\n");
		exit(1);
	}
	if (val & O_APPEND)
		printf(" , append");
	if (val & O_NONBLOCK)
		printf(" , nonblocking");
	#if !define(POSIX_SOURCE) && define(O_SYNC)
	    if (val&O_SYNC)
            printf(", synchronous writes");
    #endif
	    putchar('\n');
		exit(0);
}