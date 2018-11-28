#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

long long charToNumber(const char *str)
{
	assert(str != NULL);	

	long long number = 0;
	if (str[0] == '-'){
		for (int i = 1; i < strlen(str); i++){
			if (isdigit(str[i]))
				number = number * 10 + (str[i] - '0');
			else
				return 0;
		}
		return -number;
	}else{
		for (int i = 0; i < strlen(str); i++){
			if (isdigit(str[i]))
				number = number * 10 + (str[i] - '0');
			else
				return 0;
		}
		return number;
	}
}

int main()
{
	char test[18];
	memset(&test, 0, sizeof(test));
	strcpy(test, "12345000");
	printf("%ld\n", charToNumber(test));
}
