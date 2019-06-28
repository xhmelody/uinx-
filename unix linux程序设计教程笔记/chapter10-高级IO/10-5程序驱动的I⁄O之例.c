/*在终端的输入情况下，每一个键入的字符都会产生一个SIGIO信号。
 * 因此我们设置标准输入为非加工的输入模式,并且每次都会生成一个字符接收输入的工作由
 * SIGIO信号句柄函数来完成。它将收到的完整的一行输入到tstfile中，
 * 当输入行的首字符为'q'时，终止程序的运行
 */

//看不懂效果

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>  //这是控制终端的头文件
#include <signal.h>
#include <stdlib.h>

void input_ready(int signo);
FILE *file;

int main(void)
{
    int flags;
    char buffer[20];
    struct termios newsettings, oldsettings;
    file = fopen("tstfile", "w");
    signal(SIGIO, input_ready);
    //设置标准输入为每次读入一个字符的非加工方式
    tcgetattr(STDIN_FILENO, &oldsettings);
    newsettings = oldsettings;
    newsettings.c_lflag &= (~ICANON);
    newsettings.c_cc[VTIME] = 0;
    newsettings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &newsettings);
    //设置标准输入为无阻塞SIGIO信号驱动I/O方式
    fcntl(STDIN_FILENO, F_SETOWN, getpid());
    flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    flags = flags | O_ASYNC;
    fcntl(STDIN_FILENO, F_SETFL, flags);
    while (1)
        sleep(1);
    
    
}

void input_ready(int signo)
{
    char c, input[24];
    int n;
    static int i = 0;
    if (read(STDIN_FILENO, &c, 1) > 0)
    {
        if (c != '\n')
            input[i++] = c;
        else
        {
            input[i++] = '\0';
            fprintf(file, "received %d SIGIOs, and Input line is: %s\n", i, input);
            i = 0;
            if (input[0] == 'q')
            {
                fclose(file);
                exit(0);
            }
        }
    }
}




