#include "string.h"

// local implementation of string.h libc
char* c3p1::string::strcpy(char* dest, const char* src)
{ 
	int len = 0;

	if (src != nullptr)
	{
		while (*src != '\0')
		{
			*(dest++) = *src++;
			len++;
		}
		// Null-terminate the destination string
		*dest = '\0';
		
		// Return the adress of the start of the string
		return dest - len;
	}
	else
	{
		return nullptr; // Error code nullptr for null source
	}
}
c3p1::ssize_t c3p1::string::strlen(const char* str)
{
	ssize_t len = 0;
	if (str != nullptr)
	{
		while (*str != '\0')
		{
			len++;
			str++;
		}
		return len;
	}
	else
	{
		return -1; // Error code -1 for null str
	}
}
char* c3p1::string::strcat(char* dest, const char* append)
{
	int len = 0;
	if (dest != nullptr && append != nullptr)
	{
		// Move to the end of the first string
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

		// Null-terminante and move to the beginning
		*dest = '\0';
		dest = dest - len;

		return dest;
	}
	else
	{
		return nullptr; // Error code for null destination or append args
	}
}
void* c3p1::string::memcpy(void* dest, const void* src, size_t n)
{
	// Cast raw pointers to unsigned char pointers and process copying byte a byte
	unsigned char* byte = static_cast<unsigned char*>(dest);
	const unsigned char* bytesrc = static_cast<const unsigned char*>(src);

	for (size_t i = 0; i < n; i++)
	{
		byte[i] = bytesrc[i];
	}

	return dest;
}

// Implementation of string class
c3p1::string::string()
{
	// Initialise to empty string
	m_str = new char;
	m_memsize = 1;
	*m_str = '\0';
}

c3p1::string::string(const char* str)
{
	if (str != nullptr)
	{
		m_memsize = strlen(str) + 1;
		m_str = new char[m_memsize];
		strcpy(m_str, str);
	}
	else
	{
		// Initialise to empty string
		m_str = new char;
		m_memsize = 1;
		*m_str = '\0';
	}
}

c3p1::string::string(string& str)
{
	if (str.m_str != nullptr && str.m_memsize != 0)
	{
		m_memsize = str.m_memsize;
		m_str = new char[m_memsize];
		strcpy(m_str, str.m_str);
	}
	else // initialize to empty string
	{
		m_memsize = 1;
		m_str = new char;
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

c3p1::ssize_t c3p1::string::length() const
{
	return strlen(m_str);
}

c3p1::string& c3p1::string::operator=(const char* str)
{
	if (str != nullptr)
	{
		ssize_t len = strlen(str);
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
		// Error handling for nullptr
		return *this;
	}
}
