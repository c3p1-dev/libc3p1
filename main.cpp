// main.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// libc3p1 test program

#include <iostream>
#include "string.h"
#include "exception.h"
#include "uptr.h"

void printstr(const std::string& str)
{
	std::cout << (str.empty() ? "empty string" : str) << std::endl \
		<< "size: " << str.size() << std::endl
		<< "capacity: " << str.capacity() << std::endl;
}

using namespace c3p1::ptr;
// entry point
int main()
{
	std::string s;
	printstr(s);
	s.resize(10);
	s.shrink_to_fit();
	printstr(s);
	s.at(3) = 'c';
	std::cout << s;
}