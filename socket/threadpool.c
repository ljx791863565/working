#include "threadpool.h"

CThread_pool *pool = NULL;

void pool_init(int max_thread_num)
{
	pool = (CThread_pool*)malloc(sizeof(CThread_pool));
	pthread_mutex_init(&(pool->queue_lock), NULL);
	pthread_cond_init(&(pool->queue_ready), NULL);

	pool->queue_head = NULL;
	pool->max_thread_num = max_thread_num;
	pool->shutdown = 0;
	pool->threadid = (pthread_t*)malloc(max_thread_num * sizeof(pthread_t));

	int i = 0;
	int ret;

	for (i = 0; i < max_thread_num; i++){
		ret = pthread_create(&(pool->threadid[i]), NULL, thread_routine, NULL);
		if (ret < 0){
			perror("pthread");
			return ;
		}
	}
}

//向线程池中加入任务
int pool_add_worker(void *(*process)(void *arg), void *arg)
{
	CThread_worker *newWorker = (CThread_worker*)malloc(sizeof(CThread_worker));
	newWorker->process = process;	//注册回调函数
	newWorker->arg = arg;
	newWorker->next = NULL;

	pthread_mutex_lock(&(pool->queue_lock));
	//将任务加入到等待队列中
	CThread_worker *member = pool->queue_head;
	if (member != NULL){
		while (member->next != NULL){
			member = member->next;
		}
		member->next = newWorker;
	}else{
		pool->queue_head = newWorker;
	}

	pool->cur_queue_size++;

	pthread_mutex_unlock(&(pool->queue_lock));
	pthread_cond_signal(&(pool->queue_ready));

	return 0;
}

//销毁线程池
int pool_dectroy()
{
	if (pool->shutdown){
		//防止重复销毁
		return -1;
	}
	//唤醒所有等待的线程，准备销毁
	pthread_cond_broadcast(&(pool->queue_ready));

	int i;
	for (i = 0; i < pool->max_thread_num; i++){
		pthread_join(pool->threadid[i], NULL);	//阻塞等待线程退出
	}
	free((void*)pool->threadid[i]);

	//销毁等待队列
	CThread_worker *head = NULL;
	while (pool->queue_head != NULL){
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free(head);
	}

	//销毁锁和条件变量
	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->queue_ready));

	//释放线程池
	free(pool);
	pool = NULL;

	return 0;
}

void *thread_routine(void *arg)
{
	//获取线程id
	printf("starting thread 0x%x\n", (unsigned int)pthread_self());

	while (1){
		pthread_mutex_lock(&(pool->queue_lock));
		//当工作队列里没有可以处理的数据时，进入wait
		//根据cur_quque_size 判断工作队列是否有数据
		//当shutdown时无需wait，程序已经return -1
		while (pool->cur_queue_size == 0 && pool->shutdown){
			printf("thread 0x%x is waiting\n", (int)pthread_self());
			//开始等待
			pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
		}

		//线程池要销毁了
		if (pool->shutdown){
			pthread_mutex_unlock(&(pool->queue_lock));
			printf("thread 0x%x will exit\n", (int)pthread_self());
			pthread_exit(NULL);
		}

		//这里开始是正常线程工作数据处理
		printf("thread 0x%x starting to work\n", (int)pthread_self());

		pool->cur_queue_size--;
		CThread_worker *worker = pool->queue_head;
		pool->queue_head = worker->next;
		pthread_mutex_unlock(&(pool->queue_lock));
		//执行回调函数
		(*(worker->process))(worker->arg);
		//执行完成后销毁
		free(worker);
		worker = NULL;
	}
	pthread_exit(NULL);
}

void *myprocess(void *arg)
{
	printf("thread is 0x%x , working on task %d\n", (int)pthread_self, *((int*)arg));
	sleep(1);
	return ;
}
