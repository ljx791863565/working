 #include "head.h"

int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("arguments error\n");
		return -1;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

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
	socklen_t len = sizeof(clientAddr);
	memset(&clientAddr, 0, len);
	int connFd;

	while (1){
		connFd = accept(sockfd, (struct sockaddr *)&clientAddr, &len);
		if (connFd < 0){
			perror("accept");
			return -1;
		}

		pid_t pid;
		char buf[BUFSIZE];
		if ((pid = fork()) == 0){
			//child
			close(sockfd);
			while (1){
				memset(&buf, 0, sizeof(buf));
				fgets(buf, sizeof(buf), stdin);
				ret = write(connFd, buf, sizeof(buf));
				if (ret < 0){
					perror("write");
					close(connFd);
				}
				printf("server: %s\n", buf);
			}

		}else if (pid < 0){
			perror("fork");
			close(sockfd);
			close(connFd);
			return -1;
		}else {
			//parent
			while (1){
				memset(&buf, 0, sizeof(buf));
				ret = read(connFd, buf, sizeof(buf));
				if (ret < 0){
					perror("read");
					close(connFd);
					return -1;
				}
				printf("client: %s\n", buf);
			}
		}
	}
	return 0;
}
