#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#define SIZE 256

void fill_arr_with_zero(char *arr, int N);


int main(int argc, char const *argv[])
{
	DIR *dir;
	char path[SIZE] = {0};
	struct stat st;
	struct dirent *struct_dir;
	if(argc != 2)
	{
		perror("Input data ERROR!");
		return 1;
	}
	dir = opendir(argv[1]);
	while(struct_dir = readdir(dir))
	{
		realpath(argv[1], path);
		strcat(path, "/");
		strcat(path, struct_dir->d_name);
		//puts(path);
		lstat(path, &st);
		if(S_ISREG(st.st_mode))
	 		printf("Type of file: r-->>Name of file: %s\n", struct_dir->d_name);
	 	else if(S_ISDIR(st.st_mode))
	 		printf("Type of file: d-->>Name of file: %s\n", struct_dir->d_name);
	 	else if(S_ISLNK(st.st_mode))
	 		printf("Type of file: l-->>Name of file: %s\n", struct_dir->d_name);
	 	else
	 		printf("Type of file: other-->>Name of file: %s\n", struct_dir->d_name);
		fill_arr_with_zero(path, SIZE);
	}
	closedir(dir);

	return 0;
}


void fill_arr_with_zero(char *arr, int N)
{
	int i;
	for( i = 0; i < N; i++)
		arr[i] = 0;
	return;
}

