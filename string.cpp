#include "string.h"
#include "exception.h"

// local implementation of string.h libc

char* c3p1::string::strcpy(char* dest, const char* src)
{ 
	// check that dest and src are not null
	if (src == nullptr && dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, src) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, src) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, src) : src is nullptr.");
	}

	// copy src string to dest
    size_t len = 0;
	while (*src != '\0')
	{
		*(dest++) = *src++;
		len++;
	}
	// null-terminate the destination string
	*dest = '\0';
		
	// return the adress of the start of the string
	return dest - len;
}

char* c3p1::string::strncpy(char* dest, const char* src, c3p1::size_t count)
{
	// check that dest and src are not null
	if (src == nullptr && dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, src) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, src) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dest, src) : src is nullptr.");
	}

	// check count
	if (count == 0)
	{
		return dest;
	}

	// copy byte to byte
	size_t len = 0;
	while (len < count)
	{
		if (*(src + len) != '\0')
		{
			*(dest + len) = *(src + len);
			len++;
		}
		else
		{
			*(dest + len) = '\0';
			len++;
		}
	}

	return dest;
}

char* c3p1::string::strcat(char* dest, const char* append)
{
	// check dest and append pointers
	if (dest == nullptr && append == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(dest, append) : dest and append are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(dest, append) : dest is nullptr.");
	}
	if (append == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(dest, append) : dest and append are nullptr.");
	}
	int len = 0;
	// move to the end of the first string
	while (*dest != '\0')
	{
		dest++;
		len++;
	}

	// append the second string
	while (*append != '\0')
	{
		*(dest++) = *append++;
		len++;
	}

	// null-terminate and move to the beginning
	*dest = '\0';
	dest = dest - len;

	return dest;
}

char* c3p1::string::strncat(char* dest, const char* append, size_t count)
{
	// check dest and append pointers
	if (dest == nullptr && append == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(dest, append) : dest and append are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(dest, append) : dest is nullptr.");
	}
	if (append == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(dest, append) : dest and append are nullptr.");
	}

	// move to the end of test
	c3p1::size_t len = 0;
	while (*dest != '\0')
	{
		dest++;
		len++;
	}

	// copy byte to byte the n first characters of append
	for (c3p1::size_t i = 0; i < count; i++)
	{
		len++;

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

	return dest - len;
}

c3p1::size_t c3p1::string::strlen(const char* str)
{
	// check if str is not nullptr
	if (str != nullptr)
	{
		c3p1::size_t len = 0;
		while (*str != '\0')
		{
			len++;
			str++;
		}
		return len;
	}
	else
	{
		// throw exception
		throw exception("Exception @c3p1::strlen(str) : str is nullptr.");
	}
}

int c3p1::string::strcmp(const char* first, const char* second)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, second) : first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, secondt) : first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, second) : second is nullptr.");
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

int c3p1::string::strncmp(const char* first, const char* second, size_t count)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, second) : first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, secondt) : first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, second) : second is nullptr.");
	}

	// compare the n first characters
	for (c3p1::size_t i = 0; i < count; i++)
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
		throw exception("Exception @c3p1::string::strdup(src) : src is nullptr.");
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
		throw exception("Exception @c3p1::string::strdup(src) : memory allocation for the new string has failed.");
	}
}

char* c3p1::string::strndup(const char* src, size_t count)
{
	// check src value
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strdup(src) : src is nullptr.");
	}

	char* p = new char[count+1];

	if (p == nullptr)
	{
		throw exception("Exception @c3p1::string::strndup(src) : memory allocation for the new string has failed.");
	}

	// if count is equal to strlen(src), copy the string
	strncpy(p, src, count);

	// add the null terminal if src was longer than count, because strncpy does not
	if (strlen(src) > count)
	{
		p[count] = '\0';
	}

	return p;
}

void* c3p1::string::memcpy(void* dest, const void* src, c3p1::size_t count)
{
	// check if dest and src are not nullptr
	if (dest == nullptr && src == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dest, src, count) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dest, src, count) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dest, src, count) : src is nullptr.");
	}

	// cast raw pointers to unsigned char pointers and process copying byte a byte
	unsigned char* byte = static_cast<unsigned char*>(dest);
	const unsigned char* bytesrc = static_cast<const unsigned char*>(src);

	// copy byte a byte src to dest
	for (c3p1::size_t i = 0; i < count; i++)
	{
		byte[i] = bytesrc[i];
	}

	return dest;
}

void* c3p1::string::memmove(void* dest, const void* src, c3p1::size_t count)
{
	// check if dest and src are not nullptr
	if (dest == nullptr && src == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dest, src, count) : dest and src are nullptr.");
	}
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dest, src, count) : dest is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dest, src, count) : src is nullptr.");
	}

	// create a n bytes buffer and manage allocation failure
	unsigned char* buffer = new unsigned char[count];
	if (buffer != nullptr)
	{
		// copy src to buffer
		memcpy(static_cast<void*>(buffer), src, count);

		// copy buffer to dest
		memcpy(dest, buffer, count);
		delete[] buffer;

		return dest;
	}
	else
	{
		throw exception("Exception @c3p1::string::memmove(dest, src, count) : memory allocation for the buffer has failed.");
	}
}

void* c3p1::string::memset(void* dest, unsigned char byte, c3p1::size_t count)
{
	// check dest
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::memset(dest, byte, count) : dest is nullptr.");
	}

	// copy n byte from dest to dest+n
	unsigned char* p = static_cast<unsigned char*>(dest);
	for (c3p1::size_t i = 0; i < count; i++)
	{
		p[i] = byte;
	}

	return dest;

}

int c3p1::string::memcmp(const void* first, const void* second, c3p1::size_t count)
{
	// check first and second
	if (first == nullptr && second == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, second, n) : first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, second, n) : first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, second, n) : second is nullptr.");
	}

	// cast pointers to unsigned char* to work with bytes
	const unsigned char* f = static_cast<const unsigned char*>(first);
	const unsigned char* s = static_cast<const unsigned char*>(second);

	// compare byte to byte the n first bytes
	for (c3p1::size_t i = 0; i < count; i++)
	{
		if (f[i] == s[i])
		{
			// bytes are equals, reading the next ones
			f++;
			s++;
		}
		else if (f[i] < s[i])
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
