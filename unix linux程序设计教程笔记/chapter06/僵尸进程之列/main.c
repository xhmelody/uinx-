#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    pid_t pid;
    char *message;
    int n;
    printf("fork program start\n");
    pid = fork();
    switch(pid)
    {
        case -1:
            exit(1);
        case 0:
            message = "This is child";
            n = 1;
            break;
        default:
            message = "This is parent";
            n = 10;
            break;
    }
    
    puts(message);
    sleep(n-1);
    exit(0);
    
}
