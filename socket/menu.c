#include "head.h"
int num;
void printf_menu_main()
{
	printf("\t\t1.医生\n");
	printf("\t\t2.病人\n");
	printf("\t\t3.护士\n");
	printf("\t\t4.管理员\n");
	printf("\t\t5.退出\n");
	printf("\t\t6.请选择...\n\n\n");
}

void printf_menu_doctor()
{
	printf("\t\t医生入口\n\n");
	printf("\t\t1.注册\n");
	printf("\t\t2.登录\n");
	printf("\t\t3.退出\n");
	printf("\t\t请选择...\n\n\n");
}

void printf_menu_doctor_login()
{
	printf("\t\t1.查看个人信息\n");
	printf("\t\t2.修改个人密码\n");
	printf("\t\t3.编写医嘱\n");
	printf("\t\t4.修改医嘱\n");
	printf("\t\t5.删除医嘱\n");
	printf("\t\t6.查看全部患者信息\n");
	printf("\t\t7.退出\n");
	printf("\t\t请选择...\n");
}
