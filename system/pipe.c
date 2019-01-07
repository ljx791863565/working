#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 256
int main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
	char buf[BUFSIZE];

	const char str[20] = "hello";
	int ret = pipe(fd);
	if (ret < 0){
		perror("pipe");
		return -1;
	}
	if ((pid = fork()) < 0){
		perror("fork");
		return -1;
	}else if(pid == 0){
		printf("this is child... \n");
		close(fd[0]);
		memset(buf, 0, sizeof(buf));
		strcpy(buf, str);
		ret = write(fd[1], buf, sizeof(buf));
		if (ret < 0){
			perror("write");
			return -1;
		}
		printf("child write to parent %s\n", buf);
		//child
	}else{
		//parent
		close(fd[1]);
		memset(buf, 0, sizeof(buf));
		ret = read(fd[0], buf, sizeof(buf));
		printf("parent read from child %s", buf);
	}
	close(fd[0]);
	close(fd[1]);
	return 0;
}
