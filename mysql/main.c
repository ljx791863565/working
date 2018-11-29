#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main()
{
	MYSQL mysql;
	int res;

	//初始化mysql
	mysql_init(&mysql);

	if (mysql_real_connect(&mysql, "localhost", "root", "", "student", 0, NULL, 0)){
		printf("connect successn\n");
		res = mysql_query(&mysql, "insert into student valuse (1008, 'anny', 17)");

	}

	return 0;
}
