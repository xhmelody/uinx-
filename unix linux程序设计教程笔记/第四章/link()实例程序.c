#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	int link_value;
	const char *path1 = "testfile1";
	const char *path2 = "testfile2";
	struct stat orig_buf, new_buf;
	printf("creat testfile\n");
	creat(path1, S_IRWXU|S_IRWXG|S_IRWXO);
	stat(path1, &orig_buf);//获取文件状态
	printf("testfile status: orig_buf.st_nlink = %d\n", orig_buf.st_nlink);
	printf("testfile1 link from %s to %s\n", path1, path2);
	if (link(path1, path2))//建立新的链接，失败返回0
		exit(0);
	printf("link() call successful\n");
	stat(path1, &new_buf);
	printf("new_buf.st_nlink=%d\n", new_buf.st_nlink);
	return (EXIT_SUCCESS);
}