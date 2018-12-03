#include "unp.h"

int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("arguments error : usage : a.out addrpath\n");
		return -1;
	}

	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(atoi("13"));
	clientAddr.sin_addr.s_addr = inet_addr(argv[1]);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}

	int ret = connect(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
	if (ret < 0){
		perror("connect");
		return -1;
	}

	char buf[BUFSIZE];
	memset(&buf, 0, sizeof(buf));

	ret = read(sockfd, buf, sizeof(buf));
	if (ret < 0){
		perror("read");
		return -1;
	}

	printf("%s\n", buf);

	return 0;
}
