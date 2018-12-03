#include "head.h"

void *myworker(void *arg)
{
	int *p = (int *)arg;
	int fd = *p;
	char buf[BUFSIZE];
	
	while (1){
		memset(&buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		int ret = write(fd, buf, sizeof(buf));
		printf("server: %s\n", buf);
	}
}

int main(int argc, char *argv[])
{
	
	if (argc != 2){
		printf("参数有误, ./server port\n");
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
	memset(&clientAddr, 0, sizeof(clientAddr));
	socklen_t clientLen = sizeof(clientAddr);
	int clientFd, readFd, writeFd;

	int epfd;
	struct epoll_event ev, events[MAXEPOLL];
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = sockfd;

	epfd = epoll_create(MAXLISTEN);

	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
	
	pool_init(MAX_THREAD_NUM);

	int i, nfds;
	char buf[BUFSIZE];

	while (1){
		nfds = epoll_wait(epfd, events, MAXEPOLL, MAX_OF_WAIT_TIME);
		
		for (i = 0; i < nfds; i++){
			if (events[i].data.fd == sockfd){
				clientFd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
				if (clientFd < 0){
					perror("accept");
					return -1;
				}
				printf("accept a new connection from %s\n", inet_addr(clientAddr.sin_addr.s_addr));
				ev.data.fd = clientFd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clientFd, &ev);	//将新的fd添加到监听队列中去
			}else if (events[i].events & EPOLLIN){
				memset(&buf, 0, sizeof(buf));
				readFd = events[i].data.fd;
				ret = read(readFd, buf, sizeof(buf));
				if (ret < 0){
					perror("readFd");
					close(readFd);
					return -1;
				}
				printf("client  : %s\n", buf);
			}else if (events[i].events & EPOLLOUT){
				writeFd = events[i].data.fd;
				pool_add_worker(myworker, &writeFd);
			}
		}
	}
	close(epfd);
	close(sockfd);
	return 0;
}
