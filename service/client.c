#include "head.h"

void *handler(void *arg)
{
	int fd = *((int*)arg);
	char buf[BUFSIZE];
	MSGHEAD_T msghead;

	while (1){
		memset(&buf, 0, sizeof(buf));
		int ret;
		if ((ret = read(fd, buf, sizeof(buf))) < 0){
			perror("read");
			return -1;
		}

		memset(&msghead, 0, sizeof(msghead));
		memcpy(&msghead, buf, sizeof(msghead));

		msghead.len = ntohl(msghead.len);	//将一个无符号长整型数从网络字节序转换为主机字节序
		msghead.msgtype = ntohl(msghead.msgtype);
		msghead.result = ntohl(msghead.result);

		//返回注册信息
		if (msghead.msgtype == 2){
			register_result(msghead.result);
		} else if (msghead.msgtype == 4){
			login_result(msghead.result);
		} else if (msghead.msgtype == 6){
			if (msghead.len == sizeof(msghead)){
				printf("没有数据\n");
			}else {
				printf("%s\n", buf+sizeof(msghead));
			}
		}
	}

	return ;
}
int main(int argc, char *argv[])
{
	// $ ./a.out path port
	if (argc != 3){
		printf("参数错误\n");
		return -1;
	}
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return -1;
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
		perror("connect");
		return -1;
	}

	pthread_t pid;
	if (pthread_create(&pid, NULL, handler, &sockfd) < 0){
		perror("pthread_create");
		return -1;
	}

	int choose;
	char buf[BUFSIZE];

	while (1){
		print_menu();
		scanf("%c", &choose);
		switch(choose)
		{
			case '1':
				myRegister();
				break;
			case '2':
				myLogin();
				break;
			default:
				{
					printf("输入有误，请重新输入\n");
					break;
				}
		}
	}
}
