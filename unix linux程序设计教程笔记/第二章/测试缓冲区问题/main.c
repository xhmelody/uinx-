
// author: melody          data: 2019 01 26
//这是一个测试缓冲区的程序，在没有使用刷新缓冲区的时候，结果会与我们的预期有所差距
//因为标准错误流是无缓冲的，这使得它的输出将先于printf的输出而出现在终端上

#include <stdio.h>

#include "y_or_n_ques.h"


int main()
{
    int answer;
    printf("1: This is a buffer test program.");
    //fflush(stdout);
    fprintf(stderr,"2: --test message\n" );
    answer = y_or_n_ques("3: Hello, Are you a student?");
    if (answer == 1)
        printf("4: Hope you have high score.");
    else
        printf("4: Hope you have good salary.");
    //fflush(stdout);
    fprintf(stderr, "5: bye!\n");
    
}

