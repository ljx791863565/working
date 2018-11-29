#include <stdio.h>
#include <iostream>
#include <event.h>

using namespace std;

//定时回调函数
void onTime(int sock, short event, void *arg)
{
	cout  << "Game Over" << endl;

	struct timeval tv;
	tv.tv_sec = 1;	//设定时间为1s
	tv.tv_usec = 0;

	event_add((struct event*)arg, &tv);
}

int main()
{
	event_init();
	struct event evTime;

	evtimer_set(&evTime, onTime, &evTime);

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	event_add(&evTime, &tv);
	event_dispatch();
	return 0;
}

