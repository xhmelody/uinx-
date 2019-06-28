#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)  //子进程
    {
        exit(0);
    }
    else if (pid == 0)
    {
        if ((pid = fork()) < 0) //孙进程
            exit(0);
        else if (pid > 0)  //子进程(第一次派生的进程)
        {
            printf("child exit success\n");
            exit(1);
        }
        sleep(2);
        printf("grandchild's parent pid = %d\n", getppid());
        printf("grandchild exit success\n");
        exit(1);
    }
    if (waitpid(pid, NULL, 0) != pid)
        exit(0);
    printf("parent exit\n");
    exit(1);
}
