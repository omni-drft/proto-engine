#include <iostream>

int main()
{
	std::cout << "Premake Test!\n";
#ifdef DEBUG
	std::cout << "Compiled in DEBUG mode\n";
#else
	std::cout << "Compiled in RELEASE mode\n";
#endif
	return 0;

}