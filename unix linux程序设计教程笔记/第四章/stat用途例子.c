read_specs(char *filename)
{
	int desc;
	struct stat statbuf;
	char *buffer;
	desc = open(filename, O_RDONLY, 0);
	if (desc < 0)
		exit(0);
	if (stat(filename, &statbuf) < 0)
		exit(0);
	buffer = (char *)malloc((unsigned)statbuf.st_size + 1);
	read(desc, buffer, (unsigned)statbuf.st_size);
	buffer[statbuf.st_size] = 0;
	close(desc);
}