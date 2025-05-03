// string.h
// c3p1-dev
// my libc/string.h implementation encapsulated in a string class

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
		size_t length() const;
		string& operator = (const char* str);

	protected:
		// protected members
		char* m_str;
		size_t m_memsize;

	public:
		// local implementation of string.h libc

		// memcpy(dest, const src, size) copies n=size bytes from src to dest,
		// (+) manages exceptions for nullptr value for dest and/or src,
		// (-) does not manage overlap betweetn dest and src,
		// (+) return dest address,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memcpy(void* dest, const void* src, size_t size);

		// memccpy(dest, const src, searchedbyte, size) copies n=size bytes from src to dest until searchedbyte is read,
		// (+) manages exception for nullptr value for dest and/or src,
		// (-) does not manage overlap between src and dest,
		// (+) returns dest address,
		// (!) could lead to undefined behavior if n is superior to dest and/or src size!
		static void* memccpy(void* dest, const void* src, unsigned char searchedbyte, size_t size);

		// memmove(dest, const src, size) copies n=size bytes from src to dest,
		// (+) manages exceptions for nullptr value for dest and/or src,
		// (+) manages overlap betweetn dest and src by copying src in a buffer first,
		// (+) manages exception if memory allocation fails for the buffer,
		// (+) return dest address,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memmove(void* dest, const void* src, size_t size);

		// memset(dest, byteval, size) copies n=size times byteval to dest,
		// (+) manages exceptions for nullptr value for dest and/or src,
		// (+) return dest address,
		// (!) could lead to undefined behavior by buffer overflow!
		static void* memset(void* dest, unsigned char byteval, size_t size);

		// memcmp(first, const second, size) compares the n=size first bytes of first and second,
		// (+) manage exceptions for nullptr value for first and/or second,
		// (-) does not manage overlap between first and second,
		// (+) returns 0 if first and second are equals,
		// (+) returns -1 if first is inferior to second,
		// (+) returns +1 if first is superior to second,
		// (!) could lead undefined behavior if n is superior to first and/or second size!
		static int memcmp(const void* first, const void* second, size_t size);

		// memchr(const memoryblock, byteval, size) search the first occurence of byteval in memoryblock,
		// (+) manage exceptions for nullptr value for memoryblock,
		// (+) returns address of the first occurence of byteval,
		// (+) returns nullptr if byteval is not found.
		// (!) could lead to undefined behavior if n is superior to memoryblock size!
		static void* memchr(const void* memoryblock, unsigned char byte, size_t size);

		// strcpy(dest, const src) copies src to dest,
		// (+) manages exceptions for nullptr value for dest and/or src,
		// (-) does not manage overlap between dest and src,
		// (+) return dest address,
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strcpy(char* dest, const char* src);

		// strncpy(dest, const src, size) copies n=size characters from src to dest,
		// (+) manages exceptions for nullptr value for dest and/or src,
		// (-) does not manage overlap between dest and src,
		// (-) does nothing if n is 0,
		// (+) return dest address,
		// (!) if n < strlen(str), a null-terminal is NOT added at the end of string!
		// (+) if n > strlen(str), '\0' are added after the end of string!
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strncpy(char* dest, const char* src, size_t size);

		// strcat(dest, const append) adds append at the end of dest,
		// (+) manages exceptions for nullptr value for dest and/or append,
		// (+) return dest address,
		// (!) could lead to undefined behavior if dest or append are not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strcat(char* dest, const char* append);

		// strncat(dest, const append, size) adds the n=size first bytes of append at the end of dest,
		// (+) manages exceptions for nullptr value for dest and/or append,
		// (+) return dest address,
		// (+) returned string is guaranted to be null-terminated,
		// (!) could lead to undefined behavior if dest or append are not a null-terminated string!
		// (!) could lead to undefined behavior by buffer overflow!
		static char* strncat(char* dest, const char* append, size_t size);

		// strlen(const str) return str length,
		// (+) manages exceptions fur nullptr value for str,
		// (!) could lead to undefined behavior if append is not a null-terminated string!
		static c3p1::size_t strlen(const char* str);

		// strcmp(const first, const second) compares first and second,
		// (+) manages exceptions for nullptr value for first and/or second,
		// (+) is case sensitive,
		// (+) returns 0 if first and second are equals,
		// (+) return -1 if first < second (in lexicographic order),
		// (+) return +1 if first > second (in lexicographic order),
		// (!) could lead to undefined behavior if first and/or second are not null-terminated strings!
		// (!) could lead to undefined behavior if second is bigger than first!
		static int strcmp (const char* first, const char* second);

		// strcmp(const first, const second, size) compares the n=size first characters of first and second,
		// (+) manages exceptions for nullptr value for first and/or second,
		// (+) is case sensitive,
		// (+) returns 0 if the n first characters of first and second are equals,
		// (+) return -1 if the n first characters of first < second (in lexicographic order),
		// (+) return +1 if the n first characters of first > second (in lexicographic order),
		// (!) could lead to undefined behavior if first and/or second are not null-terminated strings!
		// (!) could lead to undefined behavior if n is bigger than first size!
		static int strncmp(const char* first, const char* second, size_t size);

		// strdup(const src) allocate enough memory for a new chain and copy src to it,
		// (+) manages exception for nullptr value for src,
		// (+) manages exception for allocation failure,
		// (+) return address of the new string,
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) pointer returned must be deleted at the end of its scope!
		static char* strdup(const char* src);

		// strndup(const src, size) allocate enough memory for a new chain and copy n=size characters from src to it,
		// (+) manages exception for nullptr value for src,
		// (+) manages exception for allocation failure,
		// (+) return address of the new string,
		// (!) could lead to undefined behavior if src is not a null-terminated string!
		// (!) pointer returned must be deleted at the end of its scope!
		static char* strndup(const char* src, size_t size);

		// TODO to fully implemente libc string.h :
		// static char* strchr (const char* str, char c);
 		// static char* strrchr(const char* str, char c);
		// static int strcoll (const char* first, const char* second);
		// static size_t strcspn (const char* str, const char* rejected_chars);
		// static const char* strpbrk(const char* str, const char* searched_chars);
		// static size_t strspn(const char* str, const char* accepted_chars);
		// static const char* strstr(const char* fullstring, const char* substring);
		// static char* strtok(char* strc, const char* delimiters);
		// static size_t strxfrm(char* dest, const char* src, size_t size);
	};
}
