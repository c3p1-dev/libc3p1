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
	int len = 0;
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

c3p1::size_t c3p1::string::strlen(const char* str)
{
	// check if str is not nullptr
	if (str != nullptr)
	{
		size_t len = 0;
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
void* c3p1::string::memcpy(void* dest, const void* src, size_t count)
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
	for (size_t i = 0; i < count; i++)
	{
		byte[i] = bytesrc[i];
	}

	return dest;
}

void* c3p1::string::memmove(void* dest, const void* src, size_t count)
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

	// create a n bytes buffer
	unsigned char* buffer = new unsigned char[count];
	memcpy(static_cast<void*>(buffer), src, count);

	// copy buffer to dest
	memcpy(dest, buffer, count);
	delete[] buffer;

	return dest;
}
void* c3p1::string::memset(void* dest, unsigned char byte, size_t count)
{
	// check dest
	if (dest == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dest, byte, count) : dest and byte are nullptr.");
	}

	// copy n byte from dest to dest+n
	unsigned char* p = static_cast<unsigned char*>(dest);
	for (size_t i = 0; i < count; i++)
	{
		p[i] = byte;
	}

	return dest;

}


// class string implementation

c3p1::string::string()
{
	// Initialise to empty string
	m_str = new char;
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

		// copy str
		strcpy(m_str, str);
	}
	else
	{
		// no-exceptions on string constructors
		// initialise to empty string
		m_str = new char;
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
		strcpy(m_str, copy.m_str);
	}
	else
	{
		m_str = new char;
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
		if (m_memsize < static_cast<unsigned>(len + 1))
		{
			// realloc memory
			delete[] m_str;
			m_memsize = len + 1;
			m_str = new char[m_memsize];
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
