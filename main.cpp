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
    c3p1::string s1 = "Youhou";
    prints1;
    const char* ps = "Yaahou, une grande chaine";
    s1 = ps;
    prints1;
    s1 = "Une petite";
    prints1;
    c3p1::string s2("La seconde chaine est plus grande que la premiere");
    prints2;
    s2 = s1;
    prints2;
    s2.shrink_to_fit();
    prints2;
    s2.clear();
    prints2;
    s2 = "J'aime le C";
    prints2;
    s2.resize(s2.size() + 2, '+');
    prints2;
    return 0;
}