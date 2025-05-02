#include <iostream>
#include "exception.h"

c3p1::exception::exception(const char* msg)
{
	message = msg;
	std::cerr << message <<  std::endl;
}