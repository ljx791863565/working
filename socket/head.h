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

#include "threadpool.h"

#define BUFSIZE 1024	//数据缓存区大小
#define MAXLISTEN 100	//描述符的最大监听数
#define MAXEPOLL 20
#define MAX_OF_WAIT_TIME 500 //监听最大阻塞时间

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

typedef struct root_user
{
	char ID[20];
	char passwd[20];
}ROOT_T;

typedef struct doctor
{
	char ID[20];
	char name[20];
	int age;
	char passwd[20];
	char sex[20];
	char department[20];	//科室 
}DOCTOR_T;

typedef struct sicker
{
	char ID[20];
	char name[20];
	char passwd[20];
	char sex[20];
	int age;
	char doctor[20];
	char nures[20];
	char atTime[20];
	char status[80];	//在挂号时填写，既往病史，药物过敏等，目前身体状态等
}SICKER_T;

typedef struct nures
{
	char ID[20];
	char name[20];
	char passwd[20];
	char sex[20];
	char grade[20];		//职称
	//something
}NURES_T；

//医嘱
typedef struct orders
{
	int orderID;	//医嘱流水ID
	char name[20];	//病人姓名
	char sex[20];
	int age;
	char doctor[20];	//主治医生姓名
	char nures[20];		//主管护士姓名
	char data[20];		//入院时间 年月日
	char diagnose[80];	//医生给出的诊断，医疗建议
}ORDERS_T;
#endif
