#include "head.h"
void *handler(void *arg)
{
	int *p = (int *)arg;
	int fd = *p;
	char buf[BUFSIZE];
	while (1){
		memset(&buf, 0, sizeof(buf));
		int ret = read(fd, buf, sizeof(buf));
		if (ret < 0){
			perror("read");
			return;
		}
		printf("from server: %s\n", buf);
	}
}
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

	pthread_t pid;
	pthread_create(&pid, NULL, handler, &sockfd);
	char buf[BUFSIZE];
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
	pthread_join(pid, NULL);
	close(sockfd);
	return 0;
}
