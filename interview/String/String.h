#ifndef __STRING__H__
#define __STRING__H__

#include <iostream>
#include <string.h>
using namespace std;
class String
{
public:
	String(const char *str = NULL);
	~String();
	String(const String& s);

	String operator+(const String &s) const;
	String& operator=(const String &s);
	String& operator+=(const String &s);
	bool operator==(const String &s) const;
	char& operator[](int n) const;

	size_t size() const;
	const char* c_str() const;

	friend istream& operator>>(istream &is, String &s);
	friend ostream& operator<<(ostream &os, String &s);
private:
	char *m_data;
	size_t m_len;
};
#endif
