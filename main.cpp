// main.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// libc3p1 test program

#include <iostream>
#include "string.h"
#include "exception.h"
#include "uptr.h"

void printstr(const c3p1::string& str)
{
	std::cout << (str.empty() ? "empty string" : str) << std::endl \
		<< "size: " << str.size() << std::endl
		<< "capacity: " << str.capacity() << std::endl;
}

using namespace c3p1::ptr;
// entry point
int main()
{
	std::cout << "sizeof(c3p1::string) = " << sizeof(c3p1::string) << std::endl;
	c3p1::string sa;
	sa.reserve(100);
	printstr(sa);
	
	sa = "Youpidou"; printstr(sa);
	sa += " et yiha"; printstr(sa);
	sa = sa + " et yahou"; printstr(sa);
	std::cout << "sizeof(c3p1::string) = " << sizeof(sa) << std::endl;
	sa.shrink_to_fit();
	printstr(sa);
}