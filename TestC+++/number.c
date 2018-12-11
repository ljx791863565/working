#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef int number;

number randNum()
{
	return rand();
}

int main(int argc, char *argv[])
{
	int i;
	int N = atoi(argv[1]);
	float m1 = 0.0;
	float m2 = 0.0;

	number x;
	for (i = 0; i < N; i++){
		x = randNum();
		m1 += ((float)x) / N;
		m2 += ((float)x*x) / N;
	}

	printf("avgrage: %f\n", m1);
	printf("std.deviation : %f\n", sqrt(m2 - m1*m1));

	return 0;

}
