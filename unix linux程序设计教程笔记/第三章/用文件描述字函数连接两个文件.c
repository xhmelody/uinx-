#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LEN 1024

int main(int argc, char **argv)
{
	int n, to, from;
	char buffer[MAX_LEN];
	if (argc != 3)
	{
		printf("Usage : %s from-file to-file\n", argv[0]);
		exit(0);
	}
	if ((from = open(argv[1], O_RDONLY)) < 0)
		exit(0);
	//以添加的方式打开文件to，若文件不存在，open将以方式644(-rw-r--r--)创建它
	if ((to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0)
		exit(0);
	//从文件from读数据并写入至to，每次写出的字符个数是每次读入的字符个数
	while ((n = read(from, buffer, sizeof(buffer))) > 0)
		write(to, buffer, n);
	close(from);
	close(to);
}

























