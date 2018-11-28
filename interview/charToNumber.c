#include <stdio.h>

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
}
