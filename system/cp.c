#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("user error\n");
		return 0;
	}

	int fd_rd, fd_wr;
	if ((fd_rd = open(argv[1], O_RDONLY)) < 0){
		perror("open");
		return -1;
	}

	char buf[1024];
	memset(&buf, 0, sizeof(buf));

	int ret = read(fd_rd, buf, 1024);
	if (ret < 0){
		perror("read");
		return -1;
	}

	if ((fd_wr = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0){
		perror("open");
		return -1;
	}

	ret = write(fd_wr, buf, ret);
	if (ret < 0){
		perror("write");
		return -1;
	}

	close(fd_wr);
	close(fd_rd);
	return -1;
}
