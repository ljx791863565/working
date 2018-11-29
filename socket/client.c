#include "head.h"

void *handler(void *arg)
{
	int *p = (int *)arg;
	int fd = *p;
	int ret;
	char buf[BUFSIZE];

	MSGHEAD_T msghead;

	while (1){
		memset(&buf, 0, sizeof(buf));
		
		ret = read(fd, buf, sizeof(buf));
		if (ret <= 0){
			perror("read");
			exit(-1);
		}
		
		memset(&msghead, 0, sizeof(msghead));
		//服务器传回的信息
		memcpy(&msghead, buf, sizeof(buf));

		msghead.len = ntohl(msghead.len);
		msghead.msgtype = ntohl(msghead.msgtype);
		msghead.result = mtohl(msghead.result);

		switch (msghead.msgtype)
		{
			case 2:
				register_result_doctor(msghead.result);
				break;
			case 4:
				login_result_doctor(msghead.result);
				break;
		}
	}
}
// ./client 127.0.0.1 8090
int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("请依次输入 client port addr\n");
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

	int ret = connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0){
		perror("connect");
		close(sockfd);
		return -1;
	}

	printf("%d connect to the server..., this is client %d\n", atoi(argv[2]), getpid());	
	
	pthread_t pid;
	ret = pthread_create(&pid, NULL, handler, &sockfd);
	if (ret < 0){
		perror("pthread_create");
		return -1;
	}
	char buf[BUFSIZE];
	while (1){
		memset(&buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		ret = write(sockfd, buf, sizeof(buf));
		if (ret < 0){
			perror("write");
			return -1;
		}
		printf("client %d: %s\n", getpid(), buf);
	}
	interface_main(sockfd);
	pthread_join(pid, NULL);
	close(sockfd);
}
