#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <error.h>

#define err_exit(MESSAGE)(\
	perror(MESSAGE),\
	exit(1)\
)

int main(void)
{
    int fd;
    if ((fd = open("myoutput", O_WRONLY|O_CREAT, 0644)) == -1)
        err_exit("myoutput");
    if (dup2(fd, 1) == -1)
        err_exit("Redirect standard output failed");
    printf("this is a test program for redirect \n");
    close(fd);
    exit(0);
} 
