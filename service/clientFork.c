#include "head.h"

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("参数有误, ./client addr port\n");
		return -1;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}
	
	int ret = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret < 0){
		perror("connect");
		return ;
	}

	pid_t pid;
	char buf[BUFSIZE];
	if ((pid = fork()) < 0){
		perror("fork");
		close(sockfd);
		return -1;
	}else if (pid == 0){
		//child
		while (1){
			memset(&buf, 0, sizeof(buf));
			fgets(buf, sizeof(buf), stdin);
			ret = write(sockfd, buf, sizeof(buf));
			if (ret < 0){
				perror("write");
				close (sockfd);
				return -1;
			}
			printf("to server : %s\n", buf);
		}
	}else {
		//perant
		while (1){
			memset(&buf, 0, sizeof(buf));
			ret = read(sockfd, buf, sizeof(buf));
			if (ret < 0){
				perror("read");
				close(sockfd);
				return -1;
			}
			printf("from server : %s\n", buf);
		}
	}
	close(sockfd);
	return 0;
}
