#include "unp.h"

int main(int argc, char *argv[])
{
	time_t ticks;

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(13);
	serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}

	int ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0){
		perror("bind");
		return -1;
	}
	
	ret = listen(sockfd, MAXLISTEN);
	if (ret < 0){
		perror("listen");
		return -1;
	}

	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));
	int clientFd;
	socklen_t clientLen = sizeof(clientAddr);
	char buf[BUFSIZE];
	while (1){
		clientFd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientLen);
		if (clientFd < 0){
			perror("clientFd");
			return -1;
		}

		memset(&buf, 0, sizeof(buf));
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

		ret = write(clientFd, buf, sizeof(buf));
		if (ret < 0){
			perror("write");
			close(clientFd);
			close(sockfd);
			return -1;
		}
	}
	close(sockfd);
	return 0;
}
