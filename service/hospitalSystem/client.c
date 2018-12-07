#include "head.h"

void *handler(void *arg)
{
	int *p = (int *)arg;
	int fd = *p;
}

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("argument error: ./client address port\n");
		return -1;	
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return -1;
	}

	int ret;
	if ((ret = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) < 0){
		perror("connect");
		return -1;
	}
	printf("connect to server %s\n", argv[1]);

	pthread_t pid;
	if ((ret = pthread_create(&pid, 0, handler, &sockfd)) < 0){
		perror("pthread_create");
		return -1;
	}

	char buf[BUFSIZE];
	while (1){
		printf_menu_main();	
	}

	close(sockfd);
	pthread_join(pid, NULL);
	return 0;
}
