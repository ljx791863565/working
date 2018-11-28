#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	if ((pid = fork()) < 0){
		perror("fork");
		return -1;
	}else if(pid == 0){
		while (1){
			printf("this is child : %d\n", getpid());
			sleep(1);
		}
	}else{
		while (1){
			printf("this is parent :%d\n", pid);
			sleep(2);
		}
	}

	return 0;
}
