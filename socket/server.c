#include "head.h"

void send_result(int fd, int result, int msgtype)
{
	MSGHEAD_T msghead;
	memset(&msghead, 0, sizeof(msghead));
	msghead.len = sizeof(msghead);
	msghead.msgtype = msgtype;
	msghead.result = result;

	msghead.len = htonl(msghead.len);
	msghead.msgtype = htonl(msghead.msgtype);
	msghead.result = htonl(msghead.result);

	//当从服务器传回时，只有包含结果MSGHEAD头
	int ret = write(fd, &msghead, sizeof(msghead));
	if (ret < 0){
		perror("write");
		return;
	}
	return ;
}

void *myworker(void *arg)
{
	MSG_T *p;
	p = (MSG_T *)arg;

	MSGHEAD_T msghead;
	memset(&msghead, 0, sizeof(msghead));
	memcpy(&msghead, p->buf, sizeof(msghead));
	msghead.len = ntohl(msghead.len);
	msghead.msgtype = ntohl(msghead.msgtype);

	switch (msghead.msgtype){
		case 1:
			Register_doctor(p->fd, p->buf);
			break;
		case 3:
			Login_doctor(p->fd, p->buf);
			break;
	}
}
// ./server 8090
int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("依次输入 ./server port\n");
		return -11;
	}
	

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -12;
	}
	
	int ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret < 0){
		perror("bind");
		return -13;
	}

	ret = listen(sockfd, MAXLISTEN);
	if (ret < 0){
		perror("listen");
		return -14;
	}
	//ev用于注册事件，events数组用于回传处理的事件
	struct epoll_event ev, events[MAXEPOLL];
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = sockfd;	//设置要处理的事件相关描述符
	
	int epfd;
	epfd = epoll_create(MAXLISTEN);	

	//注册epoll事件
	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));
	socklen_t clientLen = sizeof(clientAddr);
	int clientFd;
	int i, nfds;
	int readFd, writeFd;
	char buf[BUFSIZE];
	memset(&buf, 0, sizeof(buf));

	pool_init(4);
	MSGHEAD_T msghead;
	MSG_T *pmsg;

	while (1){
		//等待epoll事件发生
		nfds = epoll_wait(epfd, events, MAXEPOLL, MAX_OF_WAIT_TIME);

		for (i = 0; i < nfds; i++){
			//如果新监听到一个socket链接到了绑定的socket端口
			if (events[i].data.fd == sockfd){
				clientFd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientLen);
				if (clientFd < 0){
					perror("accept");
					return -15;
				}
				printf("accept a connection from %s \n", inet_ntoa(clientAddr.sin_addr.s_addr));
				ev.data.fd = clientFd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clientFd, &ev);
			}
			
			//如果是已链接用户，并且收到数据，进行读socket
			else if(events[i].events & EPOLLIN){
				if ((readFd = events[i].data.fd) < 0){
					continue;
				}
				if ((ret = read(readFd, buf, sizeof(buf))) <= 0){
					continue;
				}	
				pmsg = (MSG_T*)malloc(sizeof(MSG_T));
				if (pmsg == NULL){
					perror("malloc");
					return -15;
				}

				memset(pmsg, 0, sizeof(MSG_T));
				pmsg->fd = readFd;
				memcpy(pmsg->buf, buf, ret);

				pool_add_worker(myworker, pmsg);
			}
			/*
			//如果有数据发送，进行写socket
			else if (events[i].events & EPOLLOUT){
				writeFd = events[i].data.fd;
				write(writeFd, buf, sizeof(buf));

				ev.data.fd = writeFd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, writeFd, &ev);
			}
			*/
		}
	}
	close(sockfd);
	close(epfd);
	return 0;
}
