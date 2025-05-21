// main.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// libc3p1 test program

#include <iostream>
#include "string.h"
#include "uptr.h"

void printstr(const c3p1::string& str)
{
	std::cout << str << std::endl \
		<< "size: " << str.size() << std::endl
		<< "capacity: " << str.capacity() << std::endl;
}

using namespace c3p1::ptr;
// entry point
int main()
{
	c3p1::string sa = "une chaine";
	sa.resize(25);
	printstr(sa);
}