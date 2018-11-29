#include "head.h"

void register_result_doctor(int result)
{
	if (result == 0){
		printf("Doctor: 注册成功\n");
	}else{
		printf("Doctor: 注册失败\n");
	}

	return ;
}

void myRegister_doctor(int fd)
{
	MSGHEAD_T msghead;
	memset(&msghead, 0, sizeof(msghead));
	DOCTOR_T doctor;
	memset(&doctor, 0, sizeof(doctor));

	printf("输入用户名\n");
	scanf("%s", doctor.ID);
	printf("输入姓名\n");
	scanf("%s", doctor.name);
	printf("输入性别\n");
	scanf("%s", doctor.sex);
	printf("输入年龄\n");
	scanf("%d", &doctor.age);
	printf("输入所在科室\n");
	scanf("%s", doctor.department);
	printf("输入密码\n");
	scanf("%s", doctor.passwd);

	//发送数据包的总长度
	msghead.len = sizeof(msghead) + sizeof(doctor);
	//doctor register
	msghead.msgtype = 1;	

	msghead.len = htonl(msghead.len);
	msghead.msgtype = htonl(msghead.type);

	//组装数据包 包头+医生数据包
	char buf[BUFSIZE];
	memset(&buf, 0, sizeof(buf));
	memcpy(buf, &msghead, sizeof(msghead));
	memcpy(buf+sizeof(msghead), &doctor, sizeof(doctor));

	//发送给服务器
	int ret = write(fd, buf, len);
	if (ret < 0){
		perror("myRegister_doctor");
		return ;
	}
}
