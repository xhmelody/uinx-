int get_line(char *buf, int bufsize, FILE *fd)
{
    if (fgets(buf, bufsize, fd) == EOF)
    {
        if (feof(fd))
        {
            printf("We meet end of line\n");
            return EOF;
        }
        else
        {
            perror("fgets failed");
            return -1;
        }
    }
    printf("call fgets: %s", buf);
    return 1;
} 
