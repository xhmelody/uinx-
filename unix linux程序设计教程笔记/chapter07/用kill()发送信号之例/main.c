#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


volatile sig_atomic_t usr_interrupt = 0;

void sig_usr(int sig)
{
    usr_interrupt = 1;
}

void child_function(void)
{
    printf("I'm here! My pid is %d.\n", (int)getpid());
    //sleep(1);
    kill(getppid(), SIGUSR1);
    
    puts("Bye, now......");
    exit(1);
}

int main(void)
{
    pid_t child_id;
    signal (SIGUSR1, sig_usr);  //建立句柄
    child_id = fork();
    if (child_id == 0)
        child_function();
    while (!usr_interrupt)
        printf("子进程不返回\n");
    puts ("That's all!");
    return 0;
}
