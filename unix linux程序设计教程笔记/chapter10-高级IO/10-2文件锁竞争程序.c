#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "filelock.h"

const char *test_file="/tmp/test_lock";

int main(void)
{
    char *strw = "set write lock on region", *strr = "set read lock on region";
    int fd, bytes_count;
    fd = open(test_file, O_RDWR|O_CREAT, 0666);
    if (fd < 0)
    {
        perror("Unable, to open file\n");
        exit(0);
    }
    for (bytes_count = 0; bytes_count < 100; bytes_count++)
        write(fd, "A", 1);
}
