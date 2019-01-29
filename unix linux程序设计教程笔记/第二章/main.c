
#include <stdio.h>
#include <stdlib.h>
#include "y_or_n_ques.h"

int main()
{
    printf("Please enter you question: ");
    char s[64];
    fgets(s, sizeof(s), stdin);
    int temp = y_or_n_ques(s);
    if (temp == 1)
        printf("yes");
    else
        printf("no");
    
    return 0;
}
 
