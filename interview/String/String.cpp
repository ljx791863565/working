#include "String.h"


using namespace std;
String::String(const char *str)
{
	if (!str){
		m_data = new char[1];
		*m_data = '\0';
		m_len = 0;
	}else {
		m_len = strlen(str);
		m_data = new char[m_len +1];
		strcpy(m_data, str);
	}
}

String::~String()
{
	m_len = 0;
	delete [] m_data;
}
String::String(const String &s)
{
	m_len = s.size();
	m_data = new char[m_len + 1];
	strcpy(m_data, s.c_str());	
}

String String::operator+(const String &s) const
{
	String temp;
	temp.m_len = m_len + s.m_len;
	temp.m_data = new char[temp.m_len + 1];
	strcpy(temp.m_data, m_data);
	strcat(temp.m_data, s.m_data);
	return temp;
}

String& String::operator=(const String &s)
{
	if (this == &s){
		return *this;
	}
	delete []m_data;
	m_len = s.m_len;
	m_data = new char[m_len+1];
	strcpy(m_data, s.m_data);
	return *this;
}

String& String::operator+=(const String &s)
{
	m_len = m_len + s.m_len;
	char *temp = new char[m_len + 1];
	strcpy(temp, m_data);
	strcat(temp, s.m_data);
	delete []m_data;
	m_data = temp;
	return *this;
}


bool String::operator==(const String &s) const
{
	if (m_len != s.m_len){
		return false;
	}
	return strcmp(m_data, s.m_data) ? false : true;
}

char& String::operator[](int n)const
{
	if (n >= m_len){
		return m_data[m_len - 1];
	}
	return m_data[n];
}

inline size_t String::size() const 
{
	return m_len;
}

inline const char* String::c_str() const
{
	return m_data;
}


istream& operator>>(istream& is, String &s)
{
	char temp[1000];
	is >> temp;
	s.m_len = strlen(temp);
	s.m_data = new char [s.m_len +1];
	strcpy(s.m_data, temp);

	return is;
}

ostream& operator<<(ostream& os, String &s)
{
	os << s.c_str();
	return os;
}


