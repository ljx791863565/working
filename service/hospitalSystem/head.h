#ifndef __HEAD_H_
#define __HEAD_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <mysql/mysql.h>

//#include "threadpool.h"

#define BUFSIZE 1024	//数据缓存区大小
#define MAXLISTEN 100	//描述符的最大监听数
#define MAXEPOLL 20
#define MAX_OF_WAIT_TIME 500 //监听最大阻塞时间
#define MAX_THREAD_NUM  4//线程池线程数
typedef struct msghead
{
	int len;		//消息头长度
	int msgtype;	//消息头类型
	int result;		//返回的消息类型
}MSGHEAD_T;

typedef struct msg
{
	int fd;
	char buf[BUFSIZE];
}MSG_T;

#endif
