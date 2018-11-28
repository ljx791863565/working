#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct Worker{
	void *(*process)(void *arg);	//工作的回调函数
	void *arg;						//回调函数的参数
	struct Worker *next;
}CThread_worker;

typedef struct pool{
	pthread_mutex_t queue_lock;	//保护工作任务链表的锁
	pthread_cond_t queue_ready;	//线程等待
	CThread_worker *queue_head;	//工作任务链表头指针

	int shutdown;				//退出线程的标志	0：在工作 1：退出
	pthread_t *threadid;		//保存创建线程id
	
	int max_thread_num;			//线程池最大线程数
	int cur_queue_size;			//工作任务队列的任务个数
}CThread_pool;

int pool_add_worker(void *(*process)(void *arg), void *arg);
void *thread_routine(void *arg);

extern CThread_pool *pool;
#endif
