#include <stdio.h>
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("1.txt", "r+");
	if (fp == NULL){
		perror("fopen");
		return -1;
	}
	printf("input\n");
	char buf[20];
	memset(&buf, 0, sizeof(buf));
/*	
 	fgets(buf, 8, stdin);
	fputs(buf, fp);
	puts(buf);
*/	
	while (fgets(buf, 20, stdin) != NULL && buf[0] != '\n'){
		fputs(buf, stdout);
	}
	fputs("Done.", stdout);
	return 0;
}
