#include <stdio.h>
<<<<<<< HEAD

int charToNumber(char *str)
{
	if (str == NULL){
		return 0;
	}
	int number = 0;
	while (*str != '\0'){
		number = number * 10 + *str - '0';
		++str;
	}
	return number;
}
int main()
{
	char str[10] = "12345";
	int num = charToNumber(str);
	printf("num = %d\n", num);

	return 0;
=======
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
>>>>>>> 632b22c6934d3bb9bb30dffc0eccf9e5804d8a25
}
