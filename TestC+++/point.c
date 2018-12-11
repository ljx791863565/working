#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point
{
	double x;
	double y;

}Point;

double distance(Point a, Point b)
{
	double dx = b.x - a.x;
	double dy = b.y - a.y;

	return sqrt(dx*dx - dy*dy);
}
int main()
{	
	Point a;
	a.x = 4;
	a.y = 5;

	Point b;
	b.x = 3;
	b.y = 5;

	printf("distance = %f\n", distance(a, b));

	return 0;

}
