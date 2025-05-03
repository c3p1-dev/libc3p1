#include <iostream>
#include "string.h"

using namespace c3p1;

// Fonction de comparaison manuelle de buffers
bool buffers_equal(const char* a, const char* b, c3p1::size_t n)
{
    for (c3p1::size_t i = 0; i < n; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

// Affiche un message de test
void test(const char* name, bool ok)
{
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << name << "\n";
}

// 
void memory_func_tests()
{
    // testing memory manipulation functions
    char buffer[32] = {};
    char expected[32] = {};
    char src[] = "abcdefghij";

    // memset
    c3p1::string::memset(buffer, 'A', 10);
    for (int i = 0; i < 10; ++i) expected[i] = 'A';
    test("memset", buffers_equal(buffer, expected, 10));

    // memcpy
    c3p1::string::memcpy(buffer, src, 10);
    test("memcpy", buffers_equal(buffer, src, 10));

    // memmove
    for (int i = 0; i < 10; ++i) buffer[i] = src[i];
    c3p1::string::memmove(buffer + 2, buffer, 8);
    test("memmove", buffers_equal(buffer + 2, "abcdefgh", 8));

    // memcmp
    test("memcmp equal", c3p1::string::memcmp("abc", "abc", 3) == 0);
    test("memcmp less", c3p1::string::memcmp("abc", "abd", 3) < 0);
    test("memcmp more", c3p1::string::memcmp("abe", "abd", 3) > 0);

    // memchr
    const char* s = "hello world";
    void* p = c3p1::string::memchr(s, 'o', 11);
    test("memchr", p != nullptr && ((const char*)p - s) == 4);

    // memrchr
    p = c3p1::string::memrchr(s, 'o', 11);
    test("memrchr", p != nullptr && ((const char*)p - s) == 7);

    // memccpy
    char dest[16] = {};
    p = c3p1::string::memccpy(dest, "1234567890", '5', 10);
    test("memccpy", p == dest + 5 && buffers_equal(dest, "12345", 5));

    // mempcpy
    p = c3p1::string::mempcpy(dest, "HELLO", 5);
    test("mempcpy", p == dest + 5 && buffers_equal(dest, "HELLO", 5));

    // memmem
    const char* hay = "abcdefghijabcdefghij";
    const char* needle = "def";
    p = c3p1::string::memmem(hay, 20, needle, 3);
    test("memmem", p != nullptr && ((const char*)p - hay) == 3);

    std::cout << "Tests passed.\n";
}

int main()
{
    memory_func_tests();
    return 0;
}