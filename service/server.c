#include "head.h"

void* myworker(void *arg)
{
	MSG_T *p = (MSG_T *)arg;
	MEGHEAD_T msghead;

	memcpy(&msghead, p->buf, sizeof(msghead));
	msghead.len = ntohl(msghead.len);
	msghead.msgtype = ntohl(msghead.msgtype);

	switch(msghead.msgtype){
		case 1:
			myRegister(p->fd, p->buf);
	}
}
int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("参数有误\n");
		return -1;
	}

	int epfd;
	epfd = epoll_create(MAXLISTEN);
	
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0 ,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int ret;
	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret < 0){
		perror("bind");
		return -1;
	}

	ret = listen(sockfd, MAXLISTEN);
	if (ret < 0){
		perror("listen");
		return -1;
	}

	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = sockfd;
	//将sockfd套接字加入到epall监听队列
	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

	//创建一个监听数组保存通知事件
	struct epoll_event events[20];
	int count;		//保存通知事件的个数

	char buf[BUFSIZE];
	int i;
	int clientFd;
	struct sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	int readFd;

	MSGHEAD_T msghead;

	//线程池的创建和初始化
	pool_init(4);

	MSG_T *pmsg;
	while (1){
		count = epoll_wait(epfd, events, 20, 500);
		for (i = 0; i < count; i++){
			//客户端第一次链接
			if (events[i].data.fd == sockfd){
				clientFd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientLen);
				if (clientFd < 0){
					continue;
				}
				printf("a new client connect ok %d\n", serverAddr.sin_port);

				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = clientFd;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clientFd, &ev);
			}
			//表示管道有数据可以读取
			else if (events[i].events & EPOLLIN){
				readFd = events[i].data.fd;
				memset(buf, 0, sizeof(buf));

				ret = read(readFd, buf, sizeof(buf));
				if (ret <= 0){
					continue;
				}
				pmsg = (MSG_T *)malloc(sizeof(MSG_T));
				if (pmsg == NULL){
					perror("malloc");
					return -1;
				}
				pmsg->fd = readFd;
				memcpy(pmsg->buf, buf, ret);
				pool_add_worker(myworker, pmsg);

			}

		}
	}
	return 0;
}
