// main.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// libc3p1 test program

#include <iostream>
#include "string.h"
#include "uptr.h"

using namespace c3p1::ptr;

// entry point
int main()
{
    char* pw = new char;
    uptr<char> p(pw);
    *p = 'c';
    return 0;
}