#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[])
{
	char str[256] = {0};
	char path[256] = { 0 };
	int fd1, fd2, size;
	struct stat st1, st2;
	if (argc != 3)
	{
		perror("Args error!");
		return 1;
	}
	fd1 = open(argv[1], O_RDONLY);
	lstat(argv[1], &st1);	// fill struct st1 the information about fd1
	lstat(argv[2], &st2);   // fill struct st2 the information about argv[2]
	if(S_ISREG(st1.st_mode))
	{
		if(S_ISDIR(st2.st_mode))
		{
			realpath(argv[2], path);   // how to copy the file from old_dir to new_dir?
			strcat(path, "/new_file");    // подставлять имя argv[1] и вынести в отдельную функцию.
			puts(path);
			fd2 = open(path, O_CREAT | O_WRONLY, st1.st_mode);
			while(size = read(fd1, str, sizeof(st1.st_size)))
				write(fd2, str, sizeof(st1.st_size));
		}
		else
		{
			fd2 = open (argv[2], O_CREAT | O_WRONLY, st1.st_mode);
			while(size = read(fd1, str, sizeof(str)))
				write(fd2, str, sizeof(str));
		}
	}
	else if(S_ISLNK(st1.st_mode))
	{
		size = readlink(argv[1], str, sizeof(str));
		str[size] = 0;
		printf("%s\n", str);
		symlink(str, argv[2]);
	}
	else
	{
		perror("File is not reular or symlink!");
		return 2;
	}
	close(fd1);
	close(fd2);

	return 0;
}