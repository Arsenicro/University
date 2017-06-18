#include "string.h"
#include <iostream>

int main()
{
	string s="STRIN";
	s+="G";

	std::cout << "s= " << s << std::endl; 

	string s2="FUNNY ";
	string s3=s2 + s;

	std::cout << "s3= " << s3 << std::endl;

	s2+=s3;

	std::cout << "s2= " << s2 << std::endl;

	s+=s;

	std::cout << "s+=s " << s << std::endl;

	std::cout << "s[2]= " << s[2] << std::endl;

	//std::cout << "s[100]= " << s[100] << std::endl;
	string qwerty = "qwerty";
	string qwerty2 = "qwerty";
	string q_werty = "q werty";
	string asdfgh = "asdfgh";
	string linuks = "linuks";
	string windows = "windows";
	string aaa="aaa";
	string aaaa="aaaa";

	std::cout << "qwerty == asdfgh " << (qwerty == asdfgh) << std::endl;
	std::cout << "qwerty == qwerty " << (qwerty != qwerty2) << std::endl;
	std::cout << "q werty == qwerty " << (q_werty == qwerty) << std::endl;
	std::cout << "linuks <= windows " << (linuks <= windows) << std::endl;
	std::cout << "linuks >= windows " << (linuks >= windows) << std::endl;
	std::cout << "linuks < windows " << (linuks < windows) << std::endl;
	std::cout << "linuks > windows " << (linuks > windows) << std::endl;
	std::cout << "aaa == aaaa " << (aaa == aaaa) << std::endl;

	return 0;
}


