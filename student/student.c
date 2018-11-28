#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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

void Login_Menu()
{
	printf("\n\n\n");
	printf("\t\t1.update passwd\n");
	printf("\t\t2.display\n");
	printf("\t\t3.exit\n");
	printf("\n\n\n");
}
void saveUser(struct User *us)
{
	FILE *fp = fopen("user.txt", "a+");
	if (fp == NULL){
		perror("fopen");
		return;
	}
	int ret = fwrite(us, sizeof(User), 1, fp);
	if (ret < 0){
		perror("fwrite");
		return;
	}
	fclose(fp);
}

User *loadUser(const char *strid)
{
	FILE *fp = fopen("user.txt", "r");
	if (fp == NULL){
		perror("fopen");
		return NULL;
	}
	User *tus = (User*)malloc(sizeof(User));
	while (1){
		memset(&tus, 0, sizeof(tus));
		int ret = fread(&tus, sizeof(User), 1, fp);
		if (ret < 0){
			perror("fread");
			return NULL;
		}
		if (strcmp(tus->id, strid)){
			continue;
		}else{
			printf("id = %s\n passwd = %s\n", tus->id, tus->passwd);
			return tus;
		}
	}
}
int insert_Student(Student *stu)
{
	ST *p = (ST *)malloc(sizeof(ST));
	if (p == NULL){
		perror("malloc");
		return -1;
	}
	p->stu.ID = stu->ID;
	p->stu.age = stu->age;
	strcpy(p->stu.name, stu->name);
	strcpy(p->stu.phone, stu->phone);
	strcpy(p->stu.e_mail, stu->e_mail);
	strcpy(p->stu.sex, stu->sex);
	strcpy(p->stu.class, stu->class);

	if (head == NULL){
		head = p;
		p->next = NULL;
	}
	ST *t = head;
	while (t->next != NULL){
		t = t->next;
	}
	t->next = p;
	p->next = NULL;
	return 0;
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

	printf("input the name\n");
	char buf[20];
	memset(&buf, 0, sizeof(buf));
	scanf("%s", buf);
	strcpy(stu.name, buf);

	printf("input the phone\n");
	memset(&buf, 0, sizeof(buf));
	scanf("%s", buf);
	strcpy(stu.phone, buf);

	printf("input the e_mail\n");
	memset(&buf, 0, sizeof(buf));
	scanf("%s", buf);
	strcpy(stu.e_mail, buf);

	printf("input the age\n");
	scanf("%d", &stu.age);

	printf("input the sex\n");
	memset(&buf, 0, sizeof(buf));
	scanf("%s", buf);
	strcpy(stu.sex, buf);

	printf("inout the class\n");
	memset(&buf, 0, sizeof(buf));
	scanf("%s", buf);
	strcpy(stu.class, buf);

	User us;
	memset(&us, 0, sizeof(us));
	printf("input the id\n");
	memset(&buf, 0, sizeof(buf));
	scanf("%s", buf);
	strcpy(us.id, buf);
	while (1){
		printf("input the passwd\n");
		memset(&buf, 0, sizeof(buf));
		scanf("%s", buf);
		char tbuf[20];
		memset(&tbuf, 0, sizeof(tbuf));
		printf("please input the passwd again\n");
		scanf("%s", tbuf);
		if (!strcmp(buf, tbuf)){
			strcpy(us.passwd, buf);
			break;
		}else{
			printf("the passwords entered do not match,please re-enter\n");
		}
	}

	saveUser(&us);
	User *u = loadUser(us.id);
	printf("id = %s\n", u->id);
	printf("pasaswd = %s\n", u->passwd);
	insert_Student(&stu);
	return ;
}

void login()
{
	int choose;
	while (1){
		Login_Menu();
		printf("please choose\n");
		scanf("%c", &choose);
		switch(choose)
		{
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			default:
				break;
		}
	}
}
void Student_login(void)
{
	while (1){
		printf("this is the student login...\n");
		printf("input the id\n");
		char buf[20];
		memset(&buf, 0, sizeof(buf));
		scanf("%s", buf);
		User *p = loadUser(buf);
		if (p == NULL){
			printf("has no id %s, please reguster\n", buf);
			return;
		}
		printf("input passwd\n");
		memset(&buf, 0, sizeof(buf));
		if (strcmp(buf, p->passwd)){
			continue;	
		}
		printf("login susses\n");
		login();
	}
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
