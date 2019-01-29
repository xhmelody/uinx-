#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p = "have you time :";
	fputs(p, stdout);
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
	return 0;
}