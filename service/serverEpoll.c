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
	int connFd, readFd, writeFd;
	int i;
	pthread_t pidR, pidW;
	char buf[BUFSIZE];

	struct epoll_event ev, events[MAXEPOLL];
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = sockfd;

	int epfd = epoll_create(MAXLISTEN);

	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
	while (1){	
		int nfds = epoll_wait(epfd, events, MAXEPOLL, MAX_OF_WAIT_TIME);

		for (i = 0; i < nfds; i++){
			if (events[i].data.fd == sockfd){
				connFd = accept(sockfd, (struct sockaddr *)&clientAddr, &len);
				if (connFd < 0){
					close(sockfd);
					close(epfd);
					perror("accept");
					return -1;
				}
				printf("accept a new connection %d\n", clientAddr.sin_port);
				ev.data.fd = connFd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connFd, &ev);
			}else if (events[i].events & EPOLLIN){
				readFd = events[i].data.fd;
				memset(buf, 0, sizeof(buf));
				ret = read(readFd, buf, sizeof(buf));
				if (ret < 0){
					perror("read");
					close(connFd);
					close(epfd);
					close(readFd);
					return -1;
				}
				printf("from %d : %s\n", clientAddr.sin_port, buf);
			}
		}
	}

	return 0;
}
