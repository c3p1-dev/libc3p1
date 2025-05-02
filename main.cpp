#include <iostream>
#include "string.h"

using namespace c3p1;

int main()
{
    char* p = new char[10];
    *p = '\0';
    string::strcat(p, "test");
    string::strcat(p, "test");

    std::cout << "p = " << p << std::endl << "p len = " << string::strlen(p) << std::endl << std::endl;
    for (int i = 0; i < string::strlen(p); i++)
    {
        char* t = p + i;
        std::cout << "p[" << i << "] = " << *t << std::endl;
    }

    std::cout << "End of program\n";

}
