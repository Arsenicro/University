#include <iostream>
#include <string>

int main( int argc, char* argv [ ] )
{
	std::cout << "what is your name? \n";
	std::string name;
	std::cin >> name;
	std::cout << "hello, " << name << "!\n";
	return 0;
}
