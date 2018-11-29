#include "apue.h"
#include <sys/wait.h>

void sig_int(int signo)
{
	printf("interrupt\n%% ");
}
int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR){
		err_sys("sig_err");
	}

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL){
		//键盘输入，将最后输入的'\n'转换成为'\0'
		if (buf[strlen(buf) - 1] == '\n'){
			buf[strlen(buf) - 1] = '\0';
		}
		if ((pid = fork()) < 0){
			err_sys("fork err");
		}else if (pid == 0){	//child
			execlp(buf, buf, (char*)0);
			err_ret("count not execute : %s", buf);
			exit(127);
		}

		//parent
		if ((pid = waitpid(pid, &status, 0)) < 0){
			err_sys("waitpid err");
		}
		printf("%% ");
	}

	return 0;
}
