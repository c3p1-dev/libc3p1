// exception.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// base exception class implementation.

#include <iostream>
#include "exception.h"

c3p1::exception::exception(const char* msg)
{
	// init message
	message = msg;

	// write it on error output
	std::cerr << message <<  std::endl;
}