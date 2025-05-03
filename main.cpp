#include <iostream>
#include "string.h"

using namespace c3p1;

int main()
{
    std::cout << "Program begins" << std::endl;

    const char* text = "Ceci est ma premiere phrase. Et ceci est ma seconde.";
    const size_t len = string::strlen(text);

    char* firstSentance = new char[len+1];
    char* res = static_cast<char*>(string::memccpy(firstSentance, text, static_cast<unsigned char>('.'), len));
    *res = '\0';

    if (res != nullptr)
    {
        std::cout << "Une phrase a ete trouvee : '" << firstSentance << "'" << std::endl;
    }
    else
    {
        std::cout << "Aucune phrase n'a ete trouvee." << std::endl;
    }

    std::cout << text << std::endl;
 
    std::cout << "End of program" << std::endl;
}
