
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *stream;
    char buf[80];
    printf("open and create test_file\n");
    if ((stream = fopen("test_file","w")) == NULL)
        exit(0);
    printf("write string to test_file\n");
    
    fputs("hello xiang hang", stream);
    if ((stream = freopen("test_file", "r", stream)) == NULL)
        exit(0);
    printf("read string from test_file\n");
    fgets(buf, sizeof(buf),stream);
    printf("the string is \"%s\"\n", buf);
    
    fclose(stream);
    
    return 0;
}
