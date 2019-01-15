#ifndef __STACK__H__
#define __STACK__H__


template <typename T>
class Stack
{
	T data;
	int _size;
private:

public:
	Stack()
	{

	}
	int size()
	{
		return _size;
	}
	bool empty()
	{
		return _size <= 0;
	}
	void push(T const &e);
	T top();
	T pop();
};
#endif
