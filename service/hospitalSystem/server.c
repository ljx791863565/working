#include "head.h"

void *handler(void *arg)
{
	int *p = (int *)arg;
	int fd = *p;
}

int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("argument error: ./client address port\n");
		return -1;	
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return -1;
	}

	int ret;
	if ((ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) < 0){
		perror("bind");
		return  -1;
	}

	if ((ret = listen(sockfd, MAXLISTEN)) < 0){
		perror("listen");
		return -1;
	}

	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));
	int clientFd;
	socklen_t len = sizeof(clientAddr);

	if ((clientFd = accept(sockfd, (struct sockaddr*)&clientAddr, &len)) < 0){
		perror("accept");
		return -1;
	}
	printf("accept a client connection %d\n", ntohs(clientAddr.sin_port));

	pthread_t pid;
	if ((ret = pthread_create(&pid, 0, handler, &clientFd)) < 0){
		perror("pthread_create");
		return -1;
	}

	char buf[BUFSIZE];
	while (1){
		
	}

	close(sockfd);
	pthread_join(pid, NULL);
	return 0;
}
