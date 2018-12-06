#include "product.h"
#include "factory.h"
#include <iostream>

using namespace std;

int main()
{
	Factory *fac = new ConcreateFactory();
	Product *pro = fac->CreateProduct();
	return 0;
}
