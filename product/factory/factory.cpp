#include "factory.h"
#include "product.h"
#include <iostream>

using namespace std;

Factory::Factory()
{

}

Factory::~Factory()
{

}

ConcreateFactory::ConcreateFactory()
{
	cout << "ConcreateFactory..." << endl;
}

ConcreateFactory::~ConcreateFactory()
{

}

Product* ConcreateFactory::CreateProduct()
{
	return new ConcreateProduct();
}
