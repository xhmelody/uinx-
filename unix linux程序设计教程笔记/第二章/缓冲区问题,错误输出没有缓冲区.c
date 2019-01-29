#include <stdio.h>
#include <stdlib.h>

int Y(const char *question)
{
	fputs(question, stdout);
	while (1)
	{
		int c, answer;
		fputc(' ', stdout);
		c = tolower(fgetc(stdin));
		answer = c;
		while (c != '\n' && c != EOF)
			c = fgetc(stdin);
		if (answer == 'y' || answer == 'Y')
			return 1;
		if (answer == 'n' || answer == 'N')
			return 0;
		fputs("please answer y or n:", stdout);
	}
}

int main()
{
	int answer;
	printf("1: This is a buffer test program:\n ");
	//fflush(stdout);
	fprintf(stderr, "2:--test message\n");//错误输出没有缓冲区，就直接输出啦
	answer = Y("3: Hello, Are you a student?");
	if (answer == 1)
		printf("4: Hope you have high score.\n");
	else
		printf("4: Hope you have good salary.\n");
	//fflush(stdout);
	fprintf(stderr, "5: bye!\n");//错误输出没有缓冲区，就直接输出啦
	return 0;
}















