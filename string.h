// string.h
// c3p1-dev
// my libc/string.h implementation encapsulated in a string class
#pragma once

// Visual Studio 2022 does not know restrict
#ifndef restrict
	#define restrict __restrict
#endif

namespace c3p1
{
	// typedef
	typedef unsigned long long size_t;

	class string
	{
	public:
		// public members
		// constructors and destructor

		// default constructeur
		// (+) creates a new null-terminated empty string.
		string();

		// constructor(const str) from str
		// (+) creates a new null-terminated string of strlen(str) characters,
		// (+) copies str value to the new string.
		string(const char* str);

		// copy constructor(&copy)
		// (+) create a new string and copies the value from copy,
		// (+) manages exception for nullptr copy.m_str,
		string(string& copy);

		// destructor
		~string();

		// public functions and operators

		// length(void) returns the number of characters in the string
		// (-) does not count the null-terminal.
		size_t length() const;
		string& operator = (const char* str);

	protected:
		// protected members
		char* m_str;
		size_t m_memsize;

	public:
		// local implementation of string.h libc

		// memcpy(dst, const src, size) copies n=size bytes from src to dst
		// (+) returns original dst pointer,
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) src and dst must not overlap, it's an undefined behavior!
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memcpy(void* restrict dst, const void* restrict src, size_t size);

		// mempcpy(dst, const src, searchedbyte, size) copies n=size bytes from src to dst
		// (+) returns last written byte address,
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) src and dst must not overlap, it's an undefined behavior!
		// (!) could lead to undefined behavior by buffer overflow!
		static void* mempcpy(void* restrict dst, const void* restrict src, size_t size);

		// memccpy(dst, const src, searched_byte, size) copies n=size bytes from src to dst until searched_byte is read
		// (+) returns dst address,
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) src and dst must not overlap, it's an undefined behavior!
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memccpy(void* restrict dst, const void* restrict src, unsigned char searched_byte, size_t size);

		// memchr(const memory_block, searched_byte, size) searches the first occurence of searched_byte in memory_block
		// (+) returns address of the first occurence of searched_byte,
		// (+) returns nullptr if searched_byte is not found.
		// (+) manages exception for nullptr value for memory_block,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memchr(const void* memory_block, unsigned char searched_byte, size_t size);

		// memrchr(const memory_block, searched_byte, size) searches the first occurence of searched_byte in memory_block from end to start
		// (+) returns address of the first occurence of searched_byte,
		// (+) returns nullptr if searched_byte is not found.
		// (+) manages exception for nullptr value for memoryblock,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memrchr(const void* memory_block, unsigned char searched_byte, size_t size);

		// memmem(const big, big_size, little, little_size) searches the first occurence of little bytes string in big
		// (+) returns address of the first occurence of little,
		// (+) returns nullptr if little is not found.
		// (+) manages exception for nullptr value for big and/or little,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memmem(const void* big, size_t big_size, const void* little, size_t little_size);

		// memcmp(first, const second, size) compares the n=size first bytes of first and second
		// (+) returns 0 if first and second are equals,
		// (+) returns <0 if first is inferior to second,
		// (+) returns >0 if first is superior to second,
		// (+) manages exception for nullptr value for first and/or second,
		// (!) big and little must not overlap, its an undefined behavior!
		// (!) could lead to undefined behavior by buffer overflow!
		static int memcmp(const void* first, const void* second, size_t size);

		// memmove(dst, const src, size) copies n=size bytes from src to dst
		// (+) returns dst address,
		// (+) manages exception for nullptr value for dst and/or src,
		// (+) manages exception if memory allocation fails for the buffer,
		// (+) manages overlap betweetn dst and src by copying src in a buffer first,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memmove(void* dst, const void* src, size_t size);

		// memset(dst, byte_val, size) copies n=size times byte_val to dst
		// (+) returns dst address,
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memset(void* dst, unsigned char byte_val, size_t size);

		// strcpy(dst, const src) copies src to dst
		// (+) returns dst address,
		// (+) manages exception for nullptr value for dst and/or src,
 		// (!) dst and src must not overlap, its an undefined behavior!
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strcpy(char* restrict dst, const char* restrict src);

		// strncpy(dst, const src, size) copies n=size characters from src to dst
		// (+) returns dst address,
		// (-) does nothing if n=size is 0,
		// (+) if n < strlen(str), a null-terminal IS NOT added at the end of string!
		// (+) if n > strlen(str), '\0' are added after the end of string!
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) dst and src must not overlap, its an undefined behavior!
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strncpy(char* restrict dst, const char* restrict src, size_t size);

		// strcat(str, const append) adds append at the end of str
		// (+) returns str address,
		// (+) manages exception for nullptr value for str and/or append,
		// (!) could lead to undefined behavior if str or append are not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strcat(char* restrict str, const char* restrict append);

		// strncat(str, const append, size) adds the n=size first characters of append at the end of str
		// (+) returns str address,
		// (+) returned string is guaranted to be null-terminated,
		// (+) manages exception for nullptr value for str and/or append,
		// (!) could lead to undefined behavior if str or append are not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strncat(char* restrict str, const char* restrict append, size_t size);

		// strlen(const str) returns str length
		// (+) manages exception for nullptr value for str,
		// (!) could lead to undefined behavior if str is not a null-terminated string!
		static size_t strlen(const char* str);

		// strnlen(const str, maxlen) returns length if inferior to maxlen, or maxlen
		// (+) manages exception for nullptr value for str,
		// (!) could lead to undefined behavior if str is not a null-terminated string shorter than maxlen!
		static size_t strnlen(const char* str, size_t maxlen);

		// strcmp(const first, const second) compares first and second
		// (+) is case sensitive,
		// (+) returns 0 if first and second are equals,
		// (+) returns -1 if first < second (in lexicographic order),
		// (+) returns +1 if first > second (in lexicographic order),
		// (+) manages exception for nullptr value for first and/or second,
		// (!) could lead to undefined behavior if first and/or second are not null-terminated strings!
		// (!) could lead to undefined behavior if second is bigger than first!
		static int strcmp (const char* first, const char* second);

		// strncmp(const first, const second, size) compares the n=size first characters of first and second
		// (+) is case sensitive,
		// (+) returns 0 if the n first characters of first and second are equals,
		// (+) returns -1 if the n first characters of first < second (in lexicographic order),
		// (+) returns +1 if the n first characters of first > second (in lexicographic order),
		// (+) manages exceptions for nullptr value for first and/or second,
		// (!) could lead to undefined behavior if first and/or second are not null-terminated strings!
		// (!) could lead to undefined behavior if n is bigger than first size!
		static int strncmp(const char* first, const char* second, size_t size);

		// strcasecmp(const first, const second) compares first and second
		// (+) is not case sensitive,
		// (+) returns 0 if first and second are equals,
		// (+) returns -1 if first < second (in lexicographic order),
		// (+) returns +1 if first > second (in lexicographic order),
		// (+) manages exception for nullptr value for first and/or second,
		// (!) could lead to undefined behavior if first and/or second are not null-terminated strings!
		// (!) could lead to undefined behavior if second is bigger than first!
		static int strcasecmp(const char* first, const char* second);

		// strncasecmp(const first, const second, size) compares first and second n=size first characterr
		// (+) is not case sensitive,
		// (+) returns 0 if first and second are equals,
		// (+) returns -1 if first < second (in lexicographic order),
		// (+) returns +1 if first > second (in lexicographic order),
		// (+) manages exception for nullptr value for first and/or second,
		// (!) could lead to undefined behavior if first and/or second are not null-terminated strings!
		// (!) could lead to undefined behavior if second is bigger than first!
		static int strncasecmp(const char* first, const char* second, size_t size);

		// strdup(const src) allocates enough memory for a new chain and copy src to it
		// (+) returns address of the new string,
		// (+) manages exception for nullptr value for src,
		// (+) manages exception for allocation failure,
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) pointer returned must be deleted at the end of its scope!
		static char* strdup(const char* src);

		// strndup(const src, size) allocates enough memory for a new chain and copy n=size characters from src to it
		// (+) returns address of the new string,
		// (+) manages exception for nullptr value for src,
		// (+) manages exception for allocation failure,
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) pointer returned must be deleted at the end of its scope!
		static char* strndup(const char* src, size_t size);

		// strchr(const str, searched_char) searches a character in a string
		// (+) returns first the address of the first occurence of searched char,
		// (+) returns nullptr if searchedchar is not in str,
		// (+) manages exception for nullptr value for str,
		// (!) could lead to undefined behavior if str is not a null-terminated string!
		static char* strchr(const char* str, char searched_char);

		// strrchr(const str, searched_char) searches a character in a string
		// (+) returns first the address of the first occurence of searched_char, reading from end to start
		// (+) returns nullptr if searched_char is not in str,
		// (+) manages exception for nullptr value for str,
		// (!) could lead to undefined behavior if str is not a null-terminated string!
		static char* strrchr(const char* str, char searched_char);

		// strspn(const str, const charset) compares str character to character with (accepted) charset
		// (+) returns the length of the first sub-string only made of accepted characters,
		// (+) manages exception for nullptr value for str and charset,
		// (!) could lead to undefined behavior if str and/or accepted are not null-terminated string!
		static size_t strspn(const char* str, const char* charset);

		// strcspn(const str, const charset) compares each character of str to the (rejected) charset
		// (+) returns the length of the first sub-string that excludes all the rejected characters,
		// (+) manages exception for nullptr value for str and charset,
		// (!) could lead to undefined behavior if str and/or accepted are not null-terminated string!
		static size_t strcspn(const char* str, const char* charset);

		// strpbrk(const str, const charset) locates the first occurence of any character in charset
		// (+) manages exception for nullptr value for str and charset,
		// (+) return the address of the first occurrence of any character in charset,
		// (!) could lead to undefined behavior if str and/or charset are not null-terminated strings!
		static char* strpbrk(const char* str, const char* charset);

		// TODO to fully implemente libc string.h :
		// static const char* strstr(const char* fullstring, const char* substring);
		// static const char* strnstr(const char* fullstring, const char* substring, size_t size); 
		// static char* strtok(char* strc, const char* delimiters);

		// WONT be implemented (locale management is to complex for this project) :
		// static size_t strxfrm(char* dest, const char* src, size_t size);
		// static int strcoll (const char* first, const char* second);

	private:
		// internal functions
		static int to_lower_ascii(unsigned char c);
	};
}
