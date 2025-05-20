// string.h
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// my libc/string.h implementation encapsulated in a string class

#pragma once

// for streams
#include <iostream>

// for Visual Studio and BSD
#ifndef restrict
	#define restrict __restrict
#endif

#if defined(__x86_64__) || defined(_M_X64)
	#define ARCH_64
#elif defined(__i386__) || defined(_M_IX86)
	#define ARCH_32
#endif

namespace c3p1
{
	// typedef
#if defined ARCH_64
	typedef unsigned long long size_t;
#elif defined ARCH_32
	typedef unsigned int size_t;
#endif

	class string
	{
	// public members
	public:
		// constructors & destructors

		// default constructeur
		// (+) creates a new null-terminated empty string.
		string();

		// constructor(const str) from C string
		// (+) creates a new null-terminated string of strlen(str) characters,
		// (+) copies str value to the new string.
		string(const char* str);

		// copy constructor(&copy)
		// (+) create a new string and copies the value from copy,
		// (+) manages exception for nullptr copy.m_str,
		string(const string& copy);

		// move constructor
		string(string&& other) noexcept;

		// destructor
		~string();

		// public accessors & functions

		// length(void) returns the number of characters in the string
		size_t length() const;

		// size(void) returns the number of bytes in memory
		// (+) length() alias.
		size_t size() const;

		// capacity(void) returns the current capacity of the string
		size_t capacity() const;

		// max_size(void) returns the maximal size of a string object
		// (+) depends of system arch
		size_t max_size() const;

		// resize(new_size) resizes the string to new_size
		// (+) if new_size > current size, write '\0' on the unset bytes,
		// (+) if new_size < current size, cut the string to the new size.
		void resize(size_t new_size);

		// resize(new_size, c) resizes the string to new_size
		// (+) if new_size > current size, write c on the unset bytes,
		// (+) if new_size < current size, cut the string to the new size.
		void resize(size_t new_size, char c);

		// reserve(new_size) reserves more space in memory for the string
		// (+) if new_size > capacity, reallocates intern pointer to match with new_size,
		// (+) if new_size < capacity, has no effect.
		void reserve(size_t new_size);

		// clear() erase the string & let it empty
		void clear();

		// empty() returns true if the string is empty, false otherwise
		bool empty() const;

		// shrink_to_fit() shrinks the allocated memory size to the required amount
		void shrink_to_fit();

		// c_str(void) returns a const C string
		const char* c_str() const;

		// data(void) returns a const C string
		const char* data() const;

		// at(pos) gives a char reference to the specified character
		char& at(size_t pos);

		// at(pos) gives a char reference to the specified character, const version
		const char& at(size_t pos) const;

		// front() gives a char reference to the first character
		char& front();

		// front() gives a char reference the the first character, const version
		const char& front() const;

		// back() gives a char reference to the last character
		char& back();

		// back() gives a char reference to the last character, const version
		const char& back() const;

		// append(const &str) adds str at the end of the string
		// (+) returns *this
		string& append(const string& str);

		// append(const str) adds str at the end of the string
		// (+) returns *this
		string& append(const char* str);

		// append(const str, size) adds the first n=size characters of str at the end of the string
		// (+) returns *this
		string& append(const char* str, size_t size);

		// append(n, c) adds n times c character at the end of the string
		// (+) returns *this
		string& append(size_t n, char c);

		/* TODO : IMPLEMENT to match with std::string
		string& append (const string& str, size_t subpos, size_t sublen);
		template <class InputIterator>   string& append (InputIterator first, InputIterator last);
		*/

		// operator= (const str) copy a C string
		// (+) reallocs memory for intern pointer is not large enough,
		// (+) returns *this
		// (!) str must be a null-terminated string!
		string& operator= (const char* str);

		// operator= (const str) creates a new string from str
		// (+) reallocs memory if intern pointer is not large enough,
		// (+) returns *this
		string& operator= (const string& str);

		// operator= (&&move)
		string& operator= (string&& other) noexcept;

		// operator= (const c) create a new string from a single copy of c character,
		// (+) copy c, size becomes 1
		string& operator= (char c);

		// operator[] (pos) gives a char reference to the specified character
		char& operator[] (size_t pos);
		// operator[] (pos) gives a char reference to the specified character, const version
		const char& operator[] (size_t post) const;

		// friend operators and functions

		// swap(first, second) swaps first and second value
		// (+) swaps intern pointers and their intern size tracker
		friend void swap(string& first, string& second);

		// operator+ (const first, const second) concatenates first and second
		friend string operator+ (const string& first, const string& second);
		// operator+ (const first, const second) concatenates first and second
		// (!) second must be a null-terminated string!
		friend string operator+ (const string& first, const char* second);
		// operator+ (const first, const second) concatenates first and second
		// (!) first must be a null-terminated string!
		friend string operator+ (const char* first, const string& second);
		// operator+ (const first, second) concatenates first and second
		// (!) adding null-terminal in the string will lead to undefined behavior!
		friend string operator+ (const string& first, char second);
		// operator+ (const first, second) concatenates first and second
		// (!) adding null-terminal in the string will lead to undefined behavior!
		friend string operator+ (char first, const string& second);

		// operator ostream <<
		friend std::ostream& operator<<(std::ostream& os, const string& str);
		// operator istream >>
		friend std::istream& operator>>(std::istream& is, string& str);
		// getline (&istream, &str, delim) extracts characters from istream and stores them into str
		friend std::istream& getline(std::istream& is, string& str, char delim);
		friend std::istream& getline(std::istream& is, string& str);

	// protected members
	protected:
		char*  m_str;
		size_t m_size;
		size_t m_capacity;

	// internal constants
	private:
		// ptr to empty string
		static inline constexpr const char* mc_nullterm = "\0";
#if defined ARCH_64
		// max_size on 64 bits systems
		const size_t mc_max_size = 9223372036854775807; // 2^63 -1
#elif defined ARCH_32
		// max_size on 32 bit systems
		const size_t m_max_size = 4294967294; // 2^32 -2
#endif

	// local implementation of string.h libc
	private:

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

		// memchr(const memory_block, searched_byte, size) locates the first occurence of searched_byte in memory_block
		// (+) returns address of the first occurence of searched_byte,
		// (+) returns nullptr if searched_byte is not found.
		// (+) manages exception for nullptr value for memory_block,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memchr(const void* memory_block, unsigned char searched_byte, size_t size);

		// memrchr(const memory_block, searched_byte, size) locates the first occurence of searched_byte in memory_block from end to start
		// (+) returns address of the first occurence of searched_byte,
		// (+) returns nullptr if searched_byte is not found.
		// (+) manages exception for nullptr value for memoryblock,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memrchr(const void* memory_block, unsigned char searched_byte, size_t size);

		// memmem(const big, big_size, little, little_size) locates the first occurence of little bytes string in big
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

		// strncpy(dst, const src, size) copies at most n=size characters from src to dst
		// (+) returns dst address,
		// (-) does nothing if n=size is 0,
		// (+) if n < strlen(str), a null-terminal IS NOT added at the end of string!
		// (+) if n > strlen(str), '\0' are added after the end of string!
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) dst and src must not overlap, its an undefined behavior!
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strncpy(char* restrict dst, const char* restrict src, size_t size);

		// stpcpy(dst, const src) copies src to dst
		// (+) returns address to dst null-terminal,
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) dst and src must not overlap, its an undefined behavior!
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* stpcpy(char* restrict dst, const char* restrict src);

		// stpncpy(dst, const src, size) copies at most n=size characters from src to dst
		// (+) returns address to dst null-terminal,
		// (+) returns address to dst[size] if stpncpy does not terminate dest with null-terminal,
		// (-) does nothing if n=size is 0,
		// (-) does not add a null-terminal if not present in src[O] to src[size-1],
		// (+) if n < strlen(str), a null-terminal IS NOT added at the end of string!
		// (+) if n > strlen(str), '\0' are added after the end of string!q
		// (+) manages exception for nullptr value for dst and/or src,
		// (!) dst and src must not overlap, its an undefined behavior!
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* stpncpy(char* restrict dst, const char* restrict src, size_t size);

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

		// strchr(const str, searched_char) locates a character in a string
		// (+) returns first the address of the first occurence of searched_char,
		// (+) returns nullptr if searched_char is not in str,
		// (+) manages exception for nullptr value for str,
		// (!) could lead to undefined behavior if str is not a null-terminated string!
		static char* strchr(const char* str, char searched_char);

		// strrchr(const str, searched_char) locates a character in a string
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

		// strstr(const big, const little) locates the first occurence of little in big,
		// (+) is case sensitive,
		// (+) returns address of the first occurence of little in big,
		// (+) returns nullptr if little was not found in big,
		// (+) manages exception for nullptr value for big and/or little
		// (!) could lead to undefined behavior if big and/or little are not null-terminated string!
		static char* strstr(const char* big, const char* little);

		// strcasestr(const big, const little) locates the first occurence of little in big,
		// (+) is NOT case sensitive,
		// (+) returns address of the first occurence of little in big,
		// (+) returns nullptr if little was not found in big,
		// (+) manages exception for nullptr value for big and/or little
		// (!) could lead to undefined behavior if big and/or little are not null-terminated string!
		static char* strcasestr(const char* big, const char* little);

		// strnstr(const big, const little, size_t size) locates the first occurence of n=size bytes first bytes of little in big,
		// (+) is case sensitive,
		// (+) returns address of the first occurence of n=size first bytes of little in big,
		// (+) returns nullptr if the first n=size bytes of little were not found in big,
		// (+) does not read anything after the first null-terminal in little,
		// (+) manages exception for nullptr value for big and/or little
		// (!) could lead to undefined behavior if big and/or little are not null-terminated string!
		static char* strnstr(const char* big, const char* little, size_t size);

		// strtok(str, const sep) isolates sequential tokens in str separated by at least 1 character from sep
		// (+) is case sensitive,
		// (+) the first time strok is called, str must be not null, the static pointer is reset for a new string,
		// (+) str must be nullptr on the next calls on the same string.
		// (+) manages exception for nullptr value for sep;
		// (!) could lead to undefined behavior if str and/or sep are not null-terminated strings!
		static char* strtok(char* restrict str, const char* restrict sep);

		// strtok_r(str, const sep, last) isolates sequential tokens in str separated by at least 1 character from sep
		// (+) reentrant version of strtok, thread safe
		// (+) is case sensitive,
		// (+) the first time strok is called, str must be not null, last is initialized on str adress,
		// (+) str must be nullptr on the next calls on the same string, the lecture will start on last value.
		// (+) manages exception for nullptr value for sep;
		// (!) could lead to undefined behavior if str and/or sep are not null-terminated strings!
		static char* strtok_r(char* str, const char* sep, char** last);

		// strsep(stringp, delim) isolates sequential tokens in *stringp separated by at least 1 character from delim
		// (+) reentrant and thread-safe version of strtok
		// (+) handles cases where *stringp is initially pointing to a non-null string and manages successive token extraction
		// (+) modifies *stringp to point to the next token after the current one
		// (+) if the string is empty or composed only of delimiters, *stringp is set to nullptr
		// (+) if a token is found, it replaces the delimiter with '\0' and returns the token
		// (+) works with custom delimiters and is case-sensitive
		// (+) returns nullptr when no more tokens are found
		// (!) could lead to undefined behavior if *stringp and/or delim are not null-terminated strings
		static char* strsep(char **stringp, const char* delim);

		// WONT be implemented (locale management is to complex for this project) :
		// static size_t strxfrm(char* dest, const char* src, size_t size);
		// static int strcoll (const char* first, const char* second);

		// internal functions
		static int to_lower_ascii(unsigned char c);
	};
}
