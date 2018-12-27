#include "String.h"

int main()
{
	String s1;
	std::cin>>s1;
	String s2("hello");
	
	std::cout << "s1 :" << s1 << std::endl;
	std::cout << "s2 :" << s2 << std::endl;

	String s3 = s2;
	String s4(s3);
	std::cout << "s3 :" << s3 << std::endl;
	std::cout << "s4 :" << s4 << std::endl;
	
	s4 += s1;
	std::cout << "s4 :" << s4 << std::endl;

	s4 = s3 + s1;
	std::cout << "s4 :" << s4 << std::endl;

	std::cout << s1[4] << s1[5] << std::endl;	
	if (s1 == s2){
		std::cout << "s1 == s2" << std::endl;
	}else {
		std::cout << "s1 != s2" << std::endl;
	}
	
	return 0;
}
