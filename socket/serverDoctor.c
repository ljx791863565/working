#include "head"

void Register_doctor(int fd, char *buf)
{
	DOCTOR_T doctor;
	memset(&doctor, 0, sizeof(doctor));

	memcpy(&doctor, buf + sizeof(MSGHEAD_T), sizeof(doctor));

	MYSQL db;
	MYSQL *pdb;

	mysql_init(&db);

	pdb = mysql_real_connect(&db, "127.0.0.1", "root", "liaojiaxing", "hospital", 3306, NULL, 0);
	if (pdb == NULL){
		perror("mysql_real_connect");
		send_result(fd, 1, 2);
		return;
	}
	printf("mysql connect ok\n");

	int ret;
	char sqlSetbuf[BUFSIZE];
	memset(&sqlSetbuf, 0, sizeof(sqlbuf));
	strcpy(sqlSetbuf, "set name utf8");	//设置中文

	mysql_query(&db, sqlSetbuf);

	char sqlbuf[BUFSIZE];
	memset(&sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "insert into doctor values('%s', '%s', '%d', '%s', '%s', '%s');",
			doctor.ID, doctor.name, doctor.age, doctor.passwd, doctor.sex, doctor.department);
	ret = mysql_query(&db, sqlbuf);
	if (ret == 0){
		printf("insert ok\n");
		send_result(fd, 0, 2);
	}else {
		printf("insert fail: %s\n",sqlbuf);
		send_result(fd, 1, 2);
	}

	mysql_close(&db);

	return ;
}
