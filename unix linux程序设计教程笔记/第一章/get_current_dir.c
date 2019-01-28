#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

char *get_current_dir()
{
	char *buffer;
	char *value;
	int size = 0;
	/*确定当前工作路径名的最大长度为size，当PATH_MAX不确定的时候，size为-1*/
	#ifdef PATH_MAX
	    size = PATH_MAX;
	#else
		errno = 0;
	    if ((size = pathconf("./", _PC_PATH_MAX)) < 0)
			if (errno != 0)
			{
				printf("pathconf errno for _PC_PATH_MAX\n");
				exit(-1);
			}
	#endif
	/* PATH_MAX有定义，可以保证分配的空间足以存在路径名*/
	if (size > 0)
	{
		buffer = (char*)malloc(size + 1);
		value = getcwd(buffer, size);
	}
	else/*PATH_MAX没有定义，必须试探性地分配足够的空间来存放路径名*/
	{
		size = _POSIX_PATH_MAX;
		buffer = (char *)malloc(size);
		while (1)
		{
			value = getcwd(buffer, size);
			if (value == 0 && errno == ERANGE)//buffer太小，从新分配
			{
				size = size * 2;
				free(buffer);
				buffer = (char *)malloc(size);
			}
		}
	}
	return buffer;

}

int main()
{
	char *s = get_current_dir();
	printf("%s\n", s);
}









