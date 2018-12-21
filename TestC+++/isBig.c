#include <stdio.h>

int main()
{
	int a = 1;
	char *p = (char*)&a;
	if (*p == 1){
		printf(" 主机是小端\n");
	}else {
		printf(" 主机是大端\n");
	}
}
