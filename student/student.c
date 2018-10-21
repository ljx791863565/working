#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Student
{
	int ID;
	char name[20];
	char phone[20];
	char e_mail[20];
	int age;
	char sex[5];
	char class[20];
}Student;

typedef struct User
{
	char id[20];
	char passwd[20];
}User;

typedef struct ST_Node
{
	Student stu;
	User us;
	struct ST_Node *next;
}ST;

ST *head = NULL;
void Menu(void)
{
	printf("\n\n\n");
	printf("\twelcome to the student management system\n");
	printf("\t\t1.resister\n");
	printf("\t\t2.login\n");
	printf("\t\t3.exit");
	printf("please choose it...");
	printf("\n\n\n");
}

void Student_register(void)
{
	printf("this is the student register...\n");
	
	Student stu;
	memset(&stu, 0, sizeof(stu));
	
	printf("input the ID\n");
	int id;
	scanf("%d", &id);
	stu.ID = id;

	printf("input the ")
	return ;
}

void Student_login(void)
{
	printf("this is the student login...\n");
	return ;
}

void Student_exit(void)
{
	for (int i = 3; i > 0; i--){
		printf("the system will exit after %d secands\n", i);
		sleep(1);
	}
	printf("bye~\n");
	exit(0);
}

void Student_default(void)
{
	printf("input error,please input agint\n");
}
int main()
{
	char choose = 0;
	while (1){
		Menu();
		scanf("%c", &choose);
		switch (choose)
		{
			case '1':
				Student_register();
				break;
			case '2':
				Student_login();
				break;
			case '3':
				Student_exit();
				break;
			default:
				Student_default();
				break;
		}
	}
	return 0;
}
