#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <error.h>

#define err_exit(MESSAGE)(\
	perror(MESSAGE),\
	exit(1)\
)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char* argv[])
{
    int fd;
    if ((fd = open("file.hole", O_WRONLY|O_CREAT, 0644)) < 0)
        err_exit("create error");
    if (write(fd, buf1, 10) != 10)
        err_exit("buf1 write error");
    if (lseek(fd, 40, SEEK_SET) == -1)
        err_exit("lseek error");
    if (write(fd, buf2, 10) != 10)
        err_exit("lseek error");

    exit(0);
}

 
