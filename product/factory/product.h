#ifndef __PRODUCT__H__
#define __PRODUCT__H__

class Product
{
public:
	virtual ~Product() = 0;
protected:
	Product();
private:
	
};

class ConcreateProduct : public Product
{
public:
	ConcreateProduct();
	~ConcreateProduct();

};
#endif
