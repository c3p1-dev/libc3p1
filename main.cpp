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

// run mem* func tests
void memory_func_tests()
{
    using namespace c3p1;

    int total_tests = 0;
    int total_failures = 0;

    auto run = [&](const char* name, bool ok) {
        ++total_tests;
        if (!ok) ++total_failures;
        test(name, ok);
        };

    std::cout << "Start memory manipulation tests..." << std::endl;

    // memcpy
    {
        char src[] = "hello";
        char dst[6] = {};
        string::memcpy(dst, src, 6);
        run("memcpy basic", buffers_equal(dst, src, 6));
    }

    // memmove (non-overlapping)
    {
        char buf[] = "12345";
        string::memmove(buf + 2, buf, 3);  // expected: "12123"
        run("memmove non-overlap", buffers_equal(buf, "12123", 5));
    }

    // memmove (overlapping backward)
    {
        char buf[] = "abcdef";
        string::memmove(buf + 1, buf, 5);  // move "abcde" to "bcdef"
        run("memmove overlap forward", buffers_equal(buf, "aabcde", 6));
    }

    // memcmp
    {
        unsigned char a[4] = { 1, 2, 3, 0 };
        unsigned char b[4] = { 1, 2, 3, 0 };
        unsigned char c[4] = { 1, 2, 4, 0 };

        run("memcmp equal", string::memcmp((const char*)a, (const char*)b, 3) == 0);
        run("memcmp less", string::memcmp((const char*)a, (const char*)c, 3) < 0);
        run("memcmp greater", string::memcmp((const char*)c, (const char*)a, 3) > 0);
    }

    // memset
    {
        char buf[8];
        string::memset(buf, 'A', 8);
        bool ok = true;
        for (int i = 0; i < 8; ++i)
            if (buf[i] != 'A') ok = false;
        run("memset fill", ok);
    }

    // memchr
    {
        const char* s = "abcdef";
        run("memchr found", string::memchr(s, 'd', 6) == s + 3);
        run("memchr not found", string::memchr(s, 'x', 6) == nullptr);
    }

    // Résumé
    std::cout << "Passed : " << (total_tests - total_failures)
        << " / " << total_tests << std::endl;;

    if (total_failures > 0) 
    {
        std::cout << total_failures << " fails detected." << std::endl;
    }
}

// run str* func tests
void string_func_tests()
{
    using namespace c3p1;

    int total_tests = 0;
    int total_failures = 0;

    auto run = [&](const char* name, bool ok) {
        ++total_tests;
        if (!ok) ++total_failures;
        test(name, ok);
        };

    std::cout << std::endl << "Start string manipulation tests ..." << std::endl;

    // strcpy / strncpy
    {
        char buf[32];
        string::strcpy(buf, "Hello");
        run("strcpy basic", string::strcmp(buf, "Hello") == 0);

        string::strncpy(buf, "World", 3);
        buf[3] = '\0';
        run("strncpy partial", string::strcmp(buf, "Wor") == 0);
    }

    // strcat / strncat
    {
        char buf[32] = "Hello";
        string::strcat(buf, "World");
        run("strcat basic", string::strcmp(buf, "HelloWorld") == 0);

        buf[5] = '\0';
        string::strncat(buf, "Planet", 3);
        run("strncat partial", string::strcmp(buf, "HelloPla") == 0);
    }

    // strlen / strnlen
    {
        run("strlen", string::strlen("Test") == 4);
        run("strnlen truncate", string::strnlen("Test", 2) == 2);
        run("strnlen overflow", string::strnlen("Test", 10) == 4);
    }

    // strcmp / strncmp
    {
        run("strcmp equal", string::strcmp("abc", "abc") == 0);
        run("strcmp less", string::strcmp("abc", "abd") < 0);
        run("strcmp greater", string::strcmp("abe", "abd") > 0);

        run("strncmp equal on 2", string::strncmp("abc", "abd", 2) == 0);
        run("strncmp full", string::strncmp("abc", "abd", 3) < 0);
    }

    // strdup / strndup
    {
        char* dup = string::strdup("CopyMe");
        run("strdup", string::strcmp(dup, "CopyMe") == 0);
        // si tu as un free(), libère dup

        char* ndup = string::strndup("CopyMe", 4);
        run("strndup", string::strlen(ndup) == 4 && string::strncmp(ndup, "Copy", 4) == 0);
        // si tu as un free(), libère ndup
    }

    // strchr / strrchr
    {
        const char* s = "abcabc";
        run("strchr first b", string::strchr(s, 'b') == s + 1);
        run("strrchr last b", string::strrchr(s, 'b') == s + 4);
        run("strchr not found", string::strchr(s, 'x') == nullptr);
    }

    // strspn / strcspn
    {
        const char* s = "abc123";
        run("strspn abc", string::strspn(s, "abc") == 3);
        run("strcspn until 1", string::strcspn(s, "123") == 3);
    }

    // strpbrk
    {
        const char* s = "hello world";
        run("strpbrk found", string::strpbrk(s, "w") == s + 6);
        run("strpbrk not found", string::strpbrk(s, "xz") == nullptr);
    }

    // Résumé
    std::cout << "Passed tests : " << (total_tests - total_failures)
        << " / " << total_tests << std::endl;;

    if (total_failures > 0)
    {
        std::cout << total_failures << " fails detected." << std::endl;
    }
}

// entry point
int main()
{
    memory_func_tests();
    string_func_tests();
    return 0;
}