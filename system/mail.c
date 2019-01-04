#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define MAIL "/var/spool/mail/ljx"
#define SLEEP_TIME 10

int main()
{
	pid_t pid;
	if ((pid = fork()) == -1){
		printf("fork error : %s\n", strerror(errno));
		exit(1);
	}else if (pid > 0){
		while (1){
			if (kill(getppid(), SIGTERM) == -1){
				printf("kill parent error: %s\n", strerror(errno));
				exit(1);
			}
			{
				int mailfd;
				while (1){
					if ((mailfd = open(MAIL, O_RDONLY)) != -1){
						fprintf(stderr, "%s", "\007");
						close(mailfd);
					}
					sleep(SLEEP_TIME);
				}
			}
		}
	}

}

