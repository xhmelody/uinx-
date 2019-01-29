#include <stdio.h>
#define BUFSIZ 20

int main(int argc, char *argv[])
{
	int n;
	FILE *from, *to;
	char buf[BUFSIZ];
	if (argc != 3)
	{
		fprintf(stderr, "Usage : %s from-file to-file\n", *argv);
		exit(1);
	}
	if ((from = fopen(argv[1], "r")) == NULL)
		perror("error");
	if ((to = fopen(argv[2], "a")) == NULL)
		exit(0);
	while ((n = fread(buf, sizeof(char), BUFSIZ, from)) > 0)
		fwrite(buf, sizeof(char), n, to);
	fclose(from);
	fclose(to);
	exit(0);
}