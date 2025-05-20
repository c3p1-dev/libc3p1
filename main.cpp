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
    c3p1::string s1 = "J'aime le ";
    c3p1::string s2 = "C++";
    c3p1::string s3 = " et le C#";

    s1.append(s2.c_str());
    s1.append(s3);
    s3 = " mais pas le PHP et le Java";
    s1.append(s3.c_str(), s3.size() - 11);
    prints1;
    s1.append(10, '!');
    prints1;
    s1.append(10, '\0');
    prints1;

    return 0;
}