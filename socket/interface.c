#include "head.h"
int num;

void break_interface()
{
	printf("正在退出\n");
	sleep(2);
	return;
}

void default_interface()
{
	printf("输入有误，请重新输入\n");
	break;
}

void interface_main(int fd)
{
	while (1){
		printf_menu_main();
		scanf("%c", &num);
		switch(num)
		{
			case '1':
				interface_doctor(sockfd);
				break;
			case '2':
				interface_sicker(sockfd);
				break;
			case '3':
				interface_nures(sockfd);
				break;
			case '4':
				interface_root(sockfd);
				break;
			case '5':
				break_interface();
			default:
				default_interface();
		}
	}
}

void interface_doctor(int fd)
{
	while (1){
		printf_menu_doctor();
		scanf("%s", &num);
		switch(num)
		{
			case '1':
				myRegister_doctor(sockfd);
				break;
			case '2':
				{
					while (1){
						myLogin_doctor(sockfd);
						/*
						 * doing something
						 * 这里要验证登录，如果成功，break出来
						 */
					}
					interfac_doctor_login(sockfd);
					break;
				}
			case '3':
				break_interface();
			default:
				default_interface();
		}
	}
}

//医生登录成功后
void interface_doctor_login(int fd)
{
	while (1){
		printf_menu_doctor_login();
		scanf("%s", &num);
		switch(num)
		{
			case '1':
				myInfo_doctor(sockfd);
				break;
			case '2':
				myTurnPasswd_doctor(sockfd);
				break;
			case '3':
				myOrders_create_doctor(sockfd);
				break;
			case '4':
				myOrders_update_doctor(sockfd);
				break;
			case '5':
				myOrders_delete_doctor(sockfd);
				break;
			case '6':
				myInfo_all_sicker_doctor(sockfd);
				break;
			case '7':
				break_interface();
			default:
				default_interface();
		}
	}
}

void interface_sicker()
{

}

void interface_nures()
{
	
}

void interface_root()
{

}
