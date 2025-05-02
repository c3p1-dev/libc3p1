// string.h correspond to my local libc implementation and a class string interfacing it in c++
// c3p1-dev
#pragma once

namespace c3p1
{
	// typedef
	typedef unsigned long long size_t;

	class string
	{
	public:
		// public members
		// constructors and destructor

		// default constructeur,
		// +create a new null-terminated empty string
		string();

		// constructor(const str) from str
		// +creates a new null-terminated string of strlen(str) characters,
		// +copies str value to the new string
		string(const char* str);

		// copy constructor(&copy)
		// +create a new string and copies the value from copy
		// +manages exceptions for nullptr copy.m_str 
		string(string& copy);

		// destructor
		~string();

		// public functions and operators
		c3p1::size_t length() const;
		string& operator = (const char* str);

	protected:
		// protected members
		char* m_str;
		c3p1::size_t m_memsize;

	public:
		// local implementation of string.h libc

		// memcpy(dest, const src, n) copies n bytes from src to dest,
		// +manages exceptions for nullptr value for dest and/or src,
		// -does not manage overlap betweetn dest and src,
		// +return dest adress,
		// !could lead to undefined behavior by buffer overflow!
		static void* memcpy(void* dest, const void* src, c3p1::size_t count);

		// memmove(dest, const src, n) copies n bytes from src to dest,
		// +manages exceptions for nullptr value for dest and/or src,
		// +manages overlap betweetn dest and src,
		// +return dest adress,
		// !could lead to undefined behavior by buffer overflow!
		static void* memmove(void* dest, const void* src, c3p1::size_t count);

		// memmove(dest, const src, n) copies n bytes from src to dest,
		// +manages exceptions for nullptr value for dest and/or src,
		// +return dest adress,
		// !could lead to undefined behavior by buffer overflow!
		static void* memset(void* dest, unsigned char byte, c3p1::size_t count);

		// strcpy(dest, const src) copies src to dest,
		// +manages exceptions for nullptr value for dest and/or src,
		// -does not manage overlap between dest and src,
		// +return dest adress,
		// !could lead to undefined behavior if src is not a null-terminated string!
		// !could lead to undefined behavior by buffer overflow!
		static char* strcpy(char* dest, const char* src);

		// strncpy(dest, const src, n) copies n characters from src to dest,
		// +manages exceptions for nullptr value for dest and/or src,
		// -does not manage overlap between dest and src,
		// -does nothing if n is 0
		// +return dest adress,
		// !if n < strlen(str), a null-terminal is NOT added at the end of string!
		// +if n > strlen(str), '\0' are added after the end of string!
		// !could lead to undefined behavior if src is not a null-terminated string!
		// !could lead to undefined behavior by buffer overflow!
		static char* strncpy(char* dest, const char* src, c3p1::size_t count);

		// strcat(dest, const append) adds append at the end of dest,
		// +manages exceptions for nullptr value for dest and/or append,
		// +return dest adress,
		// !could lead to undefined behavior if dest or append are not a null-terminated string!
		// !could lead to undefined behavior by buffer overflow!
		static char* strcat(char* dest, const char* append);

		// strlen(const str) return str length,
		// +manages exceptions fur nullptr value for str,
		// !could lead to undefined behavior if append is not a null-terminated string!
		static c3p1::size_t strlen(const char* str);

		// TODO :
		// static void* memccpy(void* dest, const void* src, unsigned char byte, size_t count);
		// static void* memchr(const void* memoryblock, unsigned char byte, size_t size);
		// static int memcmp(const void* first, const void* second, size_t count);
		// static char* strchr (const char* str, char c);
 		// static char* strrchr(const char* str, char c);
		// static int strcmp (const char* first, const char* second);
		// static int strcoll (const char* first, const char* second);
		// static size_t strcspn (const char* str, const char* rejected_chars);
		// static char* strdup(const char* src);
		// static const char* strpbrk(const char* str, const char* searched_chars);
		// static size_t strspn(const char* str, const char* accepted_chars);
		// static const char* strstr(const char* fullstring, const char* substring);
		// static char* strtok(char* strc, const char* delimiters);
		// static size_t strxfrm(char* dest, const char* src, size_t size);
	};
}
