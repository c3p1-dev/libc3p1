// main.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// libc3p1 test program

#include <iostream>
#include "string.h"
#include "uptr.h"

// macro for quick result output
#define prints1 std::cout << s1.c_str() << std::endl \
<< "s1.size() = " << s1.size() << std::endl \
<< "s1.capacity() = " << s1.capacity() << std::endl;
#define prints2 std::cout << s2.c_str() << std::endl \
<< "s2.size() = " << s2.size() << std::endl \
<< "s2.capacity() = " << s2.capacity() << std::endl;

using namespace c3p1::ptr;
// entry point
int main()
{
    c3p1::string s1;
    std::cout << "Enter s1 : ";
    c3p1::getline(std::cin, s1);
    std::cout << "s1 = " << s1 << std::endl;
    prints1;

    return 0;
}