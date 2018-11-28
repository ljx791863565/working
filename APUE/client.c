#include "apue.h"
#include <sys/socket.h>
#include <arpa/inet.h>		
#include <netinet/in.h>
pthread_mutex_t mu;
int a = 10;

void* handler1(void *arg)
{
	while (1){
		pthread_mutex_lock(&mu);
		printf("this is handler1... %d\n", a);
		a++;
		sleep(1);
		pthread_mutex_unlock(&mu);
	}
}

void* handler2(void *arg)
{
	while (1){
		pthread_mutex_lock(&mu);
		printf("this is handler2... %d\n", a);
		a--;
		sleep(2);
		pthread_mutex_unlock(&mu);
	}
}
int main()
{
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons("8080");
	client.sin_addr.s_addr = "127.0.0.1";

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}

	pthread_t pid1, pid2;
	int ret = pthread_create(&pid1, NULL, handler1, NULL);
	if (ret < 0){
		perror("pthread_create");
		return -1;
	}

	ret = pthread_create(&pid2, NULL, handler2, NULL);
	if (ret < 0){
		perror("pthread_create");
		return -1;
	}

	pthread_mutex_init(&mu, NULL);

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	pthread_mutex_destroy(&mu);

	return 0;
}
