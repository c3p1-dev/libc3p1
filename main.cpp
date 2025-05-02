#include <iostream>
#include "string.h"

using namespace c3p1;

int main()
{
    std::cout << "Program begins" << std::endl;

    char* n = string::strdup("(chaine A)");
    char* m = string::strdup("(chaine B)");
    char* o = new char[string::strlen(n) + string::strlen(m) + 5];
    *o = '\0';

    std::cout << "n = " << n << std::endl << "m = " << m << std::endl << "o = " << o << std::endl;

    std::cout << "copy '" << n << "' to a new string o ..." << std::endl;
    string::strcpy(o, n);
    std::cout << "o = '" << o << "'" << std::endl;

    
    std::cout << "concatening '" << o << "', '" << m << "' ..." << std::endl;
    string::strncat(o, m, string::strlen(m));
    std::cout << "o = '" << o << "'" << std::endl;
    
    // 
    delete[] o; o = nullptr;
    delete[] n; n = nullptr;
    delete[] m; m = nullptr;

    std::cout << "End of program" << std::endl;
}
