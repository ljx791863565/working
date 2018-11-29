#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("user.txt", "r+");
	char buf[200] = "helloworld";
	int ret = fwrite(buf, sizeof(char), strlen(buf), fp);
	if (ret < 0){
		perror("fwrite");
	}

	return 0;
}
