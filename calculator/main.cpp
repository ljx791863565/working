#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int main()
{
	printf("Date %s\n", __DATE__);
	printf("Time %s\n", __TIME__);
	printf("Line %d\n", __LINE__);
	printf("File %s\n", __FILE__);
	return 0;
}
