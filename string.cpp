#include "string.h"
#include "exception.h"

// local implementation of string.h libc

void* c3p1::string::memcpy(void* restrict dst, const void* restrict src, c3p1::size_t size)
{
	// check if dst and src are not nullptr
	if (dst == nullptr && src == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dst, const src, size) : dest and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dst, const src, size) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dst, const src, size) : src is nullptr.");
	}

	// cast raw pointers to unsigned char pointers and process copying byte a byte
	unsigned char* currentbyte = static_cast<unsigned char*>(dst);
	const unsigned char* bytes = static_cast<const unsigned char*>(src);

	// copy byte a byte src to dst
	for (c3p1::size_t i = 0; i < size; i++)
	{
		currentbyte[i] = bytes[i];
	}

	return dst;
}

char* c3p1::string::strcpy(char* dest, const char* src)
{ 
	// check that dest and src are not null
	if (src == nullptr && dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, const src) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, const src) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, const src) : src is nullptr.");
	}

	// copy src string to dest
    size_t i = 0;
	while (*src != '\0')
	{
		*(dest++) = *src++;
		i++;
	}
	// null-terminate the destination string
	*dest = '\0';
		
	// return the address of the start of the string
	return dest - i;
}

char* c3p1::string::strncpy(char* dest, const char* src, c3p1::size_t size)
{
	// check that dest and src are not null
	if (src == nullptr && dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strncpy(dest, const src, size) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strncpy(dest, const src, size) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strncpy(dest, const src, size) : src is nullptr.");
	}

	// check count
	if (size == 0)
	{
		return dest;
	}

	// copy byte to byte
	size_t i = 0;
	while (i < size)
	{
		if (*(src + i) != '\0')
		{
			*(dest + i) = *(src + i);
			i++;
		}
		else
		{
			*(dest + i) = '\0';
			i++;
		}
	}

	return dest;
}

char* c3p1::string::strcat(char* dest, const char* append)
{
	// check dest and append pointers
	if (dest == nullptr && append == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(dest, const append) : dest and append are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(dest, const append) : dest is nullptr.");
	}
	if (append == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(dest, const append) : dest and append are nullptr.");
	}
	int i = 0;
	// move to the end of the first string
	while (*dest != '\0')
	{
		dest++;
		i++;
	}

	// append the second string
	while (*append != '\0')
	{
		*(dest++) = *append++;
		i++;
	}

	// null-terminate and move to the beginning
	*dest = '\0';
	dest = dest - i;

	return dest;
}

char* c3p1::string::strncat(char* dest, const char* append, size_t size)
{
	// check dest and append pointers
	if (dest == nullptr && append == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(dest, const append, size) : dest and append are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(dest, const append, size) : dest is nullptr.");
	}
	if (append == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(dest, const append, size) : dest and append are nullptr.");
	}

	// move to the end of test
	c3p1::size_t i = 0;
	while (*dest != '\0')
	{
		dest++;
		i++;
	}

	// copy byte to byte the n first characters of append
	for (c3p1::size_t j = 0; j < size; j++ && i++)
	{
		// i++;

		if (*append != '\0')
		{
			*(dest++) = *(append++);
		}
		else
		{
			*(dest++) = '\0';
		}
	}

	// add the null-terminal if needed
	if (*(dest - 1) != '\0')
	{
		*dest = '\0';
	}

	return dest - i;
}

c3p1::size_t c3p1::string::strlen(const char* str)
{
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strlen(const str) : str is nullptr.");
	}

	// count characters until the first null-terminal
	c3p1::size_t i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}

	return i;
}

c3p1::size_t c3p1::string::strnlen(const char* str, c3p1::size_t maxlen)
{
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strnlen(const str, maxlen) : str is nullptr.");
	}

	// count characters until the first null-terminal or maxlen
	c3p1::size_t i = 0;
	while (*str != '\0')
	{
		if (i < maxlen)
		{
			i++;
			str++;
		}
	}

	return i;
}

int c3p1::string::strcmp(const char* first, const char* second)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, const second) : first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, const second) : first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, const second) : second is nullptr.");
	}

	// compare character to character
	while (*second != '\0')
	{
		if (*first == *second)
		{
			// same character, reading the next one
			first++;
			second++;
		}
		else if (*first < *second)
		{
			return -1;
		}
		else
		{
			return +1;
		}
	}

	// return 0 for equals string
	return 0;
}

int c3p1::string::strncmp(const char* first, const char* second, size_t size)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw exception("Exception @c3p1::string::strncmp(first, const second, size) : first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strncmp(first, const second, size) : first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strncmp(first, const second, size) : second is nullptr.");
	}

	// compare the n first characters
	for (c3p1::size_t i = 0; i < size; i++)
	{
		if (*first == *second)
		{
			// same character, reading the next one
			first++;
			second++;
		}
		else if (*first < *second)
		{
			return -1;
		}
		else
		{
			return +1;
		}
	}

	// n first characters are equals
	return 0;
}

char* c3p1::string::strdup(const char* src)
{
	// check src value	
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strdup(const src) : src is nullptr.");
	}

	// allocate memory and copy src
	char* p = new char[strlen(src) + 1];

	if (p != nullptr)
	{
		strcpy(p, src);
		return p;
	}
	else
	{
		throw exception("Exception @c3p1::string::strdup(const src) : memory allocation for the new string has failed.");
	}
}

char* c3p1::string::strndup(const char* src, size_t size)
{
	// check src value
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strndup(const src, size) : src is nullptr.");
	}

	char* p = new char[size + 1];

	if (p == nullptr)
	{
		throw exception("Exception @c3p1::string::strndup(const src, size) : memory allocation for the new string has failed.");
	}

	// if count is equal to strlen(src), copy the string
	strncpy(p, src, size);

	// add the null terminal if src was longer than count, because strncpy does not
	if (strlen(src) > size)
	{
		p[size] = '\0';
	}

	return p;
}

char* c3p1::string::strchr(const char* str, char searchedchar)
{
	// check str value
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strchr(const str, searchedchar) : str is nullptr.");
	}

	c3p1::size_t l = strlen(str);

	// reading character to character from the first to the last
	for (c3p1::size_t i = 0; i < l; i++)
	{
		if (str[i] == searchedchar)
		{
			// return address of the found character
			return const_cast<char*>(str + i);
		}
	}

	// searched chararacter not found
	return nullptr;
}

char* c3p1::string::strrchr(const char* str, char searchedchar)
{
	// check str value
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strrchr(const str, searchedchar) : str is nullptr.");
	}

	// pointing at the end
	c3p1::size_t l = strlen(str);
	char* wp = const_cast<char*>(str) + l;

	// reading character to character from the last to the first
	for (c3p1::size_t i = 0; i < l; i++)
	{
		if (*(wp) == searchedchar)
		{
			// return address of the found character
			return wp;
		}
		else
		{
			wp--;
		}
	}

	// searched character not found
	return nullptr;
}

c3p1::size_t c3p1::string::strspn(const char* str, const char* charset)
{
	// check str value
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strspn(const str, const accepted) : str is nullptr.");
	}

	// count length of the first substring only made with accepted characters
	c3p1::size_t lstr = strlen(str);
	c3p1::size_t lcs = strlen(charset);
	c3p1::size_t count = 0;

	// read str from first character to the first unaccepted character or to the null-terminal and keep the count
	for (c3p1::size_t i = 0; i < lstr; i++)
	{
		// track count variation
		c3p1::size_t c = count;

		for (c3p1::size_t j = 0; j < lcs; j++)
		{
			if (str[i] == charset[j])
			{
				count++;
			}
		}

		// if count has not been increased, end of accepted characters string
		if (count != c + 1)
		{
			break;
		}
	}

	// the whole string is made of accepted characters
	return count;
}

c3p1::size_t c3p1::string::strcspn(const char* str, const char* charset)
{
	// check str value
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strspn(const str, const accepted) : str is nullptr.");
	}

	// count length of the first substring only made with accepted characters
	c3p1::size_t lstr = strlen(str);
	c3p1::size_t lcs = strlen(charset);
	c3p1::size_t count = 0;

	// read str from first character to the first unaccepted character or to the null-terminal and keep the count
	for (c3p1::size_t i = 0; i < lstr; i++)
	{
		// track count variation
		c3p1::size_t c = count;

		for (c3p1::size_t j = 0; j < lcs; j++)
		{
			if (str[i] != charset[j])
			{
				count++;
			}
		}

		// if count has not been increased, end of accepted characters string
		if (count != c + 1)
		{
			break;
		}
	}

	// the whole string is made of accepted characters
	return count;
}

char* c3p1::string::strpbrk(const char* str, const char* charset)
{
	// check if str and charset are not nullptr
	if (str == nullptr && charset == nullptr)
	{
		throw exception("Exception @c3p1::string::strpbrk(const str, const charset) : str and charset are nullptr.");
	}
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strpbrk(const str, const charset) : str is nullptr.");
	}
	if (charset == nullptr)
	{
		throw exception("Exception @c3p1::string::strpbrk(const str, const charset) : charset is nullptr.");
	}

	// look for any characters from charset in str
	c3p1::size_t lcs = strlen(charset);

	while (*str != '\0')
	{
		// compare the character at the address str to charset
		for (c3p1::size_t i = 0; i < lcs; i++)
		{
			if (*str == charset[i])
			{
				// found it, returns address
				return const_cast<char*>(str);
			}
		}

		// move to next character
		str++;
	}

	// characters not found
	return nullptr;
}

void* c3p1::string::memccpy(void* dest, const void* src, unsigned char searchedbyte, c3p1::size_t size)  
{  
	// check if dest and src are not nullptr  
	if (dest == nullptr && src == nullptr)  
	{  
		throw exception("Exception @c3p1::string::memccpy(dest, const src, searchedbyte, size) : dest and src are nullptr.");  
	}  
	if (dest == nullptr)  
	{  
		throw exception("Exception @c3p1::string::memccpy(dest, const src, searchedbyte, size) : dest is nullptr.");  
	}  
	if (src == nullptr)  
	{  
		throw exception("Exception @c3p1::string::memccpy(dest, const src, searchedbyte, size) : src is nullptr.");  
	}  

	unsigned char* d = static_cast<unsigned char*>(dest);  
	const unsigned char* s = static_cast<const unsigned char*>(src);  

	// write byte to byte the bloc src to dest count times or after first occurrence of byte  
	c3p1::size_t i = 0;  
	do  
	{  
		d[i] = s[i];  

		if (d[i] == searchedbyte)  
		{  
			// Fix: Return the correct pointer type by adding an offset to the destination pointer  
			return static_cast<void*>(d + i + 1);  
		}  

	} while (++i < size);  

	return nullptr;  
}

void* c3p1::string::memmove(void* dest, const void* src, c3p1::size_t size)
{
	// check if dest and src are not nullptr
	if (dest == nullptr && src == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dest, const src, size) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dest, const src, size) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dest, const src, size) : src is nullptr.");
	}

	// create a n bytes buffer and manage allocation failure
	unsigned char* buffer = new unsigned char[size];
	if (buffer != nullptr)
	{
		// copy src to buffer
		memcpy(static_cast<void*>(buffer), src, size);

		// copy buffer to dest
		memcpy(dest, buffer, size);
		delete[] buffer;

		return dest;
	}
	else
	{
		throw exception("Exception @c3p1::string::memmove(dest, src, size) : memory allocation for the buffer has failed.");
	}
}

void* c3p1::string::memset(void* dest, unsigned char byteval, c3p1::size_t size)
{
	// check dest
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::memset(dest, byte, size) : dest is nullptr.");
	}

	// copy n byte from dest to dest+n
	unsigned char* p = static_cast<unsigned char*>(dest);
	for (c3p1::size_t i = 0; i < size; i++)
	{
		p[i] = byteval;
	}

	return dest;

}

int c3p1::string::memcmp(const void* first, const void* second, c3p1::size_t size)
{
	// check first and second
	if (first == nullptr && second == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, const second, size) : first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, const second, size) : first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, const second, size) : second is nullptr.");
	}

	// cast pointers to unsigned char* to work with bytes
	const unsigned char* pfirst = static_cast<const unsigned char*>(first);
	const unsigned char* psecond = static_cast<const unsigned char*>(second);

	// compare byte to byte the n first bytes
	for (c3p1::size_t i = 0; i < size; i++)
	{
		if (pfirst[i] == psecond[i])
		{
			// bytes are equals, reading the next ones
			pfirst++;
			psecond++;
		}
		else if (pfirst[i] < psecond[i])
		{
			// first is inferior to second
			return -1;
		}
		else
		{
			// first is superior to second
			return +1;
		}
	}

	// memblocs are equals
	return 0;
}

void* c3p1::string::memchr(const void* memoryblock, unsigned char searchedbyte, c3p1::size_t size)  
{  
	if (memoryblock == nullptr)  
	{  
		throw exception("Exception @c3p1::string::memchr(const memoryblock, searchedbyte, size) : memoryblock is nullptr.");  
	}  

	// cast raw pointer  
	unsigned char* currentbyte = const_cast<unsigned char*>(static_cast<const unsigned char*>(memoryblock));

	// search byteval
	for (c3p1::size_t i = 0; i < size; i++)
	{
		if (*currentbyte == searchedbyte)
		{
			return static_cast<void*>(currentbyte);
		}
		currentbyte++;
	}

	// byteval not found
	return nullptr;
}

// class string implementation

c3p1::string::string()
{
	// Initialise to empty string
	m_str = new char;

	// check allocation result
	if (m_str == nullptr)
	{
		throw exception("Exception @c3p1::string::string(void) : memory allocation for the string has failed.");
	}

	m_memsize = 1;
	*m_str = '\0';
}

c3p1::string::string(const char* str)
{
	// check str pointer
	if (str != nullptr)
	{
		// allocate enough memory
		m_memsize = strlen(str) + 1;
		m_str = new char[m_memsize];
		
		// check allocation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(str) : memory allocation for the string has failed.");
		}

		// copy str
		strcpy(m_str, str);
	}
	else
	{
		// no-exceptions on string constructors
		// initialise to empty string
		m_str = new char;

		// check allocation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(str) : memory allocation for the string has failed.");
		}

		m_memsize = 1;
		*m_str = '\0';
	}
}

c3p1::string::string(string& copy)
{
	// check copy.m_str pointer
	if (copy.m_str == nullptr)
	{
		throw exception("Exception c3p1::string::string(&copy) : copy.m_str is nullptr.");
	}

	if (copy.m_memsize != 0)
	{
		m_memsize = copy.m_memsize;
		m_str = new char[m_memsize];

		// check allocation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(&copy) : memory allocation for the string has failed.");
		}

		strcpy(m_str, copy.m_str);
	}
	else
	{
		m_str = new char;

		// check allcation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(&copy) : memory allocation for the string has failed.");
		}

		m_memsize = 1;
		*m_str = '\0';
	}
}

c3p1::string::~string()
{
	if (m_str != nullptr)
	{
		delete[] m_str;
		m_str = nullptr;
	}
	m_memsize = 0;
}

c3p1::size_t c3p1::string::length() const
{
	return strlen(m_str);
}

c3p1::string& c3p1::string::operator=(const char* str)
{
	if (str != nullptr)
	{
		size_t len = strlen(str);
		// check if memsize is enough
		if (m_memsize < len + 1)
		{
			// realloc memory
			delete[] m_str;
			m_memsize = len + 1;
			m_str = new char[m_memsize];

			// check allocation result
			if (m_str == nullptr)
			{
				throw exception("Exception @c3p1::string::string(&copy) : memory allocation for the string has failed.");
			}
		}

		// copy the string
		strcpy(m_str, str);
		return *this;
	}
	else
	{
		// error handling for nullptr
		return *this;
	}
}
