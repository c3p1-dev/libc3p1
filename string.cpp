// string.cpp
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// my libc/string.h implementation encapsulated in a string class

#include "string.h"
#include "exception.h"

// local implementation of string.h libc

void* c3p1::string::memcpy(void* restrict dst, const void* restrict src, c3p1::size_t size)
{
	// check if dst and src are not nullptr
	if (dst == nullptr && src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memcpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memcpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memcpy(dst, const src, size): src is nullptr.");
	}

	// cast raw pointers to unsigned char pointers and process copying byte a byte
	unsigned char* current_byte = static_cast<unsigned char*>(dst);
	const unsigned char* wp = static_cast<const unsigned char*>(src);

	// copy byte a byte src to dst
	for (c3p1::size_t i = 0; i < size; i++)
	{
		current_byte[i] = wp[i];
	}

	return dst;
}

void* c3p1::string::mempcpy(void* restrict dst, const void* restrict src, c3p1::size_t size)
{
	// check if dst and src are not nullptr
	if (dst == nullptr && src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::mempcpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::mempcpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::mempcpy(dst, const src, size): src is nullptr.");
	}

	// cast raw pointers to unsigned char pointers and process copying byte a byte
	unsigned char* currentbyte = static_cast<unsigned char*>(dst);
	const unsigned char* wp = static_cast<const unsigned char*>(src);
	// copy byte a byte src to dst
	for (c3p1::size_t i = 0; i < size; i++)
	{
		*currentbyte++ = wp[i];
	}

	return static_cast<void*>(currentbyte);
}

void* c3p1::string::memccpy(void* restrict dst, const void* restrict src, unsigned char searchedbyte, c3p1::size_t size)
{
	// check if dst and src are not nullptr  
	if (dst == nullptr && src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memccpy(dst, const src, searchedbyte, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memccpy(dst, const src, searchedbyte, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memccpy(dst, const src, searchedbyte, size): src is nullptr.");
	}

	unsigned char* d = static_cast<unsigned char*>(dst);
	const unsigned char* s = static_cast<const unsigned char*>(src);

	// write byte to byte the bloc src to dst count times or after first occurrence of byte  
	c3p1::size_t i = 0;
	do
	{
		d[i] = s[i];

		if (d[i] == searchedbyte)
		{
			// return address of the byte after the copy of searchedbyte
			return static_cast<void*>(d + i + 1);
		}

	} while (++i < size);

	return nullptr;
}

void* c3p1::string::memchr(const void* memory_block, unsigned char searched_byte, c3p1::size_t size)
{
	if (memory_block == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memchr(const memory_block, searched_byte, size): memory_block is nullptr.");
	}

	// cast raw pointer  
	unsigned char* current_byte = const_cast<unsigned char*>(static_cast<const unsigned char*>(memory_block));

	// search byteval
	for (c3p1::size_t i = 0; i < size; i++)
	{
		if (*current_byte == searched_byte)
		{
			return static_cast<void*>(current_byte);
		}
		current_byte++;
	}

	// searchedbyte not found
	return nullptr;
}

void* c3p1::string::memrchr(const void* memory_block, unsigned char searched_byte, c3p1::size_t size)
{
	if (memory_block == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memrchr(const memory_block, searched_byte, size): memory_block is nullptr.");
	}

	// cast raw pointer
	unsigned char* wp = const_cast<unsigned char*>(static_cast<const unsigned char*>(memory_block));
	// move at the end
	unsigned char* wc = wp + size;

	c3p1::size_t i = 0;
	while (*wc != searched_byte && i < size)
	{
		// read the next byte (from end to start)
		i++;
		wc--;
	}

	if (*wc == searched_byte)
	{
		// return address of found byte
		return wc;
	}
	else
	{
		// searched_byte not found
		return nullptr;
	}
}
void* c3p1::string::memmem(const void* big, c3p1::size_t big_size, const void* little, c3p1::size_t little_size)
{
	// check big and little
	if (big == nullptr && little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memmem(const big, big_size, const little, litte_size): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memmem(const big, big_size, const little, litte_size): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memmem(const big, big_size, const little, litte_size): little is nullptr.");
	}

	// cast raw pointers
	const unsigned char* wb = static_cast<const unsigned char*>(big);
	const unsigned char* wl = static_cast<const unsigned char*>(little);

	// return big if little_size is zero
	if (little_size == 0)
	{
		return const_cast<void*>(big);
	}

	// return nullptr if big_size < little_size
	if (big_size < little_size)
	{
		return nullptr;
	}

	// search byte to byte if big contains little
	for (c3p1::size_t i = 0; i <= big_size - little_size; i++)
	{
		bool match = true;
		for (c3p1::size_t j = 0; j < little_size; j++)
		{
			if (wb[i + j] != wl[j])
			{
				match = false;
				break;
			}
		}

		// return address of the first occurence of little in big
		if (match == true)
		{
			return const_cast<void*>(static_cast<const void*>(wb + i));
		}
	}

	// little not found
	return nullptr;
}

int c3p1::string::memcmp(const void* first, const void* second, c3p1::size_t size)
{
	// check first and second
	if (first == nullptr && second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memcmp(first, const second, size): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memcmp(first, const second, size): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memcmp(first, const second, size): second is nullptr.");
	}

	// cast pointers to unsigned char* to work with bytes
	const unsigned char* wp = static_cast<const unsigned char*>(first);
	const unsigned char* ws = static_cast<const unsigned char*>(second);

	// compare byte to byte the first `size` bytes
	for (c3p1::size_t i = 0; i < size; i++)
	{
		if (wp[i] != ws[i])
		{
			// return the difference of the first unequal byte
			return wp[i] - ws[i];
		}
	}

	// The memory blocks are equal
	return 0;
}

void* c3p1::string::memmove(void* dst, const void* src, c3p1::size_t size)
{
	// check if dst and src are not nullptr
	if (dst == nullptr && src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memmove(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memmove(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memmove(dst, const src, size): src is nullptr.");
	}

	// create a n bytes buffer
	unsigned char* wp = new unsigned char[size];

	// copy src to buffer
	memcpy(static_cast<void*>(wp), src, size);

	// copy buffer to dst
	memcpy(dst, wp, size);
	delete[] wp;

	return dst;
}

void* c3p1::string::memset(void* dst, unsigned char byte_val, c3p1::size_t size)
{
	// check dst
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::memset(dst, byte_val, size) : dst is nullptr.");
	}

	// copy n byte from dst to dst+n -> dst+2n
	unsigned char* p = static_cast<unsigned char*>(dst);
	for (c3p1::size_t i = 0; i < size; i++)
	{
		p[i] = byte_val;
	}

	return dst;

}

char* c3p1::string::strcpy(char* restrict dst, const char* restrict src)
{ 
	// check that dst and src are not null
	if (src == nullptr && dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcpy(dst, const src): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcpy(dst, const src): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcpy(dst, const src): src is nullptr.");
	}

	// copy src string to dst
    c3p1::size_t i = 0;
	while (*src != '\0')
	{
		*(dst++) = *src++;
		i++;
	}
	// null-terminate the destination string
	*dst = '\0';
		
	// return the address of the start of the string
	return dst - i;
}

char* c3p1::string::strncpy(char* restrict dst, const char* restrict src, c3p1::size_t size)
{
	// check that dst and src are not null
	if (src == nullptr && dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncpy(dst, const src, size): src is nullptr.");
	}

	// check count
	if (size == 0)
	{
		return dst;
	}

	// copy byte to byte
	char* wp = nullptr;
	for (c3p1::size_t i = 0; i < size; i++)
	{
		// if still copying
		if (wp == nullptr)
		{
			dst[i] = src[i];
		}
		else
		{
			// src was shorter than size, filling dst with '\0'
			dst[i] = '\0';
		}

		// keep the address of the first '\0'
		if (dst[i] == '\0' && wp == nullptr)
		{
			wp = &dst[i];
		}
	}

	return dst;
}

char* c3p1::string::stpcpy(char* restrict dst, const char* restrict src)
{
	// check that dst and src are not null
	if (src == nullptr && dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::stpcpy(dst, const src): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::stpcpy(dst, const src): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::stpcpy(dst, const src): src is nullptr.");
	}

	// copy src string to dst
	while (*src != '\0')
	{
		*(dst++) = *(src++);
	}
	// null-terminate the destination string
	*dst = '\0';

	// return the address of the start of the string
	return dst;
}

char* c3p1::string::stpncpy(char* restrict dst, const char* restrict src, c3p1::size_t size)
{
	// check that dst and src are not null
	if (src == nullptr && dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::stpncpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::stpncpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::stpncpy(dst, const src, size): src is nullptr.");
	}

	// check count
	if (size == 0)
	{
		return dst;
	}

	// copy byte to byte
	char* wp = nullptr;
	for (c3p1::size_t i = 0; i < size; i++)
	{
		// if still copying
		if (wp == nullptr)
		{
			dst[i] = src[i];
		}
		else
		{
			// src was shorter than size, filling dst with '\0'
			dst[i] = '\0';
		}

		// keep the address of the first '\0'
		if (dst[i] == '\0' && wp == nullptr)
		{
			wp = &dst[i];
		}
	}

	// no null-terminal copied, point to the last written char
	if (wp == nullptr)
	{
		wp = &dst[size-1];
	}

	return wp;
}

char* c3p1::string::strcat(char* restrict str, const char* restrict append)
{
	// check str and append pointers
	if (str == nullptr && append == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcat(str, const append): str and append are nullptr.");
	}
	if (str == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcat(str, const append): str is nullptr.");
	}
	if (append == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcat(str, const append): append is nullptr.");
	}

	c3p1::size_t i = 0;
	// move to the end of the first string
	while (*str != '\0')
	{
		str++;
		i++;
	}

	// append the second string
	while (*append != '\0')
	{
		*(str++) = *append++;
		i++;
	}

	// null-terminate and move to the beginning
	*str = '\0';
	str = str - i;

	return str;
}

char* c3p1::string::strncat(char* restrict str, const char* restrict append, c3p1::size_t size)
{
	// check str and append pointers
	if (str == nullptr && append == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncat(str, const append, size): str and append are nullptr.");
	}
	if (str == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncat(str, const append, size): str is nullptr.");
	}
	if (append == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncat(str, const append, size): append is nullptr.");
	}

	// move to the end of test
	c3p1::size_t i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}

	// copy byte to byte the n first characters of append
	for (c3p1::size_t j = 0; j < size; j++ && i++)
	{
		// i++;

		if (*append != '\0')
		{
			*(str++) = *(append++);
		}
		else
		{
			*(str++) = '\0';
		}
	}

	// add the null-terminal if needed
	if (*(str - 1) != '\0')
	{
		*str = '\0';
	}

	return str - i;
}

c3p1::size_t c3p1::string::strlen(const char* str)
{
	if (str == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strlen(const str): str is nullptr.");
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
		throw c3p1::exception("Exception @c3p1::string::strnlen(const str, maxlen): str is nullptr.");
	}

	// count characters until the first null-terminal is read or maxlen
	c3p1::size_t i = 0;
	while (*str != '\0' && i < maxlen)
	{
		i++;
		str++;
	}

	return i;
}

int c3p1::string::strcmp(const char* first, const char* second)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcmp(first, const second): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcmp(first, const second): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcmp(first, const second): second is nullptr.");
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
		else
		{
			return (*first - *second);
		}
	}

	// return 0 for equals string
	return 0;
}

int c3p1::string::strcasecmp(const char* first, const char* second)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcasecmp(first, const second): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcasecmp(first, const second): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcasecmp(first, const second): second is nullptr.");
	}

	unsigned char c1, c2;
	while (*first && *second)
	{
		c1 = c3p1::string::to_lower_ascii((unsigned char)*first);
		c2 = c3p1::string::to_lower_ascii((unsigned char)*second);

		if (c1 != c2)
		{
			return c1 - c2;
		}

		first++;
		second++;
	}
	
	return c3p1::string::to_lower_ascii((unsigned char)*first) - c3p1::string::to_lower_ascii((unsigned char)*second);
}

int c3p1::string::strncasecmp(const char* first, const char* second, c3p1::size_t size)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcasecmp(first, const second): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcasecmp(first, const second): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strcasecmp(first, const second): second is nullptr.");
	}

	unsigned char c1, c2;
	while (size-- > 0)
	{
		c1 = c3p1::string::to_lower_ascii((unsigned char)*first++);
		c2 = c3p1::string::to_lower_ascii((unsigned char)*second++);

		if (c1 != c2)
		{
			return c1 - c2;
		}

		// Si on atteint la fin d'une chaîne, on s'arrête
		if (c1 == '\0')
		{
			break;
		}
	}

	return 0;
}

int c3p1::string::to_lower_ascii(unsigned char c) {
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');  // ou simplement +32
	return c;
}

int c3p1::string::strncmp(const char* first, const char* second, c3p1::size_t size)
{
	// check if first and second are not nullptr
	if (first == nullptr && second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncmp(first, const second, size): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncmp(first, const second, size): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strncmp(first, const second, size): second is nullptr.");
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
		else
		{
			return *first - *second;
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
		throw c3p1::exception("Exception @c3p1::string::strdup(const src): src is nullptr.");
	}

	// allocate memory and copy src
	char* p = new char[c3p1::string::strlen(src) + 1];

	c3p1::string::strcpy(p, src);
	return p;
}

char* c3p1::string::strndup(const char* src, c3p1::size_t size)
{
	// check src value
	if (src == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strndup(const src, size): src is nullptr.");
	}

	char* p = new char[size + 1];

	// if count is equal to strlen(src), copy the string
	c3p1::string::strncpy(p, src, size);

	// add the null terminal if src was longer than count, because strncpy does not
	if (c3p1::string::strlen(src) > size)
	{
		p[size] = '\0';
	}

	return p;
}

char* c3p1::string::strchr(const char* str, char searched_char)
{
	// check str value
	if (str == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strchr(const str, searched_char): str is nullptr.");
	}

	c3p1::size_t l = c3p1::string::strlen(str);

	// reading character to character from the first to the last
	for (c3p1::size_t i = 0; i < l; i++)
	{
		if (str[i] == searched_char)
		{
			// return address of the found character
			return const_cast<char*>(str + i);
		}
	}

	// searched chararacter not found
	return nullptr;
}

char* c3p1::string::strrchr(const char* str, char searched_char)
{
	// check str value
	if (str == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strrchr(const str, searched_char): str is nullptr.");
	}

	// pointing at the end
	c3p1::size_t l = c3p1::string::strlen(str);
	char* wp = const_cast<char*>(str) + l;

	// reading character to character from the last to the first
	for (c3p1::size_t i = 0; i < l; i++)
	{
		if (*(wp) == searched_char)
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
		throw c3p1::exception("Exception @c3p1::string::strspn(const str, const accepted): str is nullptr.");
	}

	// count length of the first substring only made with accepted characters
	c3p1::size_t lstr = c3p1::string::strlen(str);
	c3p1::size_t lcs = c3p1::string::strlen(charset);
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
		throw c3p1::exception("Exception @c3p1::string::strcspn(const str, const accepted): str is nullptr.");
	}

	// count length of the first substring only made with accepted characters
	c3p1::size_t lstr = c3p1::string::strlen(str);
	c3p1::size_t lcs = c3p1::string::strlen(charset);
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
		throw c3p1::exception("Exception @c3p1::string::strpbrk(const str, const charset): str and charset are nullptr.");
	}
	if (str == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strpbrk(const str, const charset): str is nullptr.");
	}
	if (charset == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strpbrk(const str, const charset): charset is nullptr.");
	}

	// look for any characters from charset in str
	c3p1::size_t lcs = c3p1::string::strlen(charset);

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

char* c3p1::string::strstr(const char* big, const char* little)
{
	// check big and first value
	if (big == nullptr && little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strstr(const big, const little): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strstr(const big, const little): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strstr(const big, const little): little is nullptr.");
	}

	c3p1::size_t big_len = c3p1::string::strlen(big);
	c3p1::size_t little_len = c3p1::string::strlen(little);

	if (big_len < little_len)
	{
		// little is not found in big if big is shorter than little
		return nullptr;
	}

	// search the first occurence of little
	for (c3p1::size_t i = 0; i <= big_len - little_len; i++)
	{
		bool match = true;
		for (c3p1::size_t j = 0; j < little_len; j++)
		{
			if (big[i + j] != little[j])
			{
				match = false;
				break;
			}
		}

		if (match == true)
		{
			return const_cast<char*>(big + i);
		}
	}

	// little not found
	return nullptr;
}

char* c3p1::string::strcasestr(const char* big, const char* little)
{
	// check big and first value
	if (big == nullptr && little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strstr(const big, const little): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strstr(const big, const little): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strstr(const big, const little): little is nullptr.");
	}

	c3p1::size_t big_len = c3p1::string::strlen(big);
	c3p1::size_t little_len = c3p1::string::strlen(little);

	if (big_len < little_len)
	{
		// little is not found in big if big is shorter than little
		return nullptr;
	}

	// search for the first occurence of little - not case sensitive
	for (c3p1::size_t i = 0; i <= big_len - little_len; i++)
	{
		bool match = true;
		for (c3p1::size_t j = 0; j < little_len; j++)
		{
			if (c3p1::string::to_lower_ascii(big[i + j]) != c3p1::string::to_lower_ascii(little[j]))
			{
				match = false;
				break;
			}
		}

		if (match == true)
		{
			return const_cast<char*>(big + i);
		}
	}

	// little not found
	return nullptr;
}

char* c3p1::string::strnstr(const char* big, const char* little, c3p1::size_t size)
{
	// check big and first value
	if (big == nullptr && little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strnstr(const big, const little): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strnstr(const big, const little): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strnstr(const big, const little): little is nullptr.");
	}

	c3p1::size_t big_len = c3p1::string::strlen(big);
	c3p1::size_t little_len = c3p1::string::strlen(little) > size ? size : strlen(little);

	if (big_len < little_len)
	{
		// little is not found in big if big is shorter than little
		return nullptr;
	}

	// search the first occurence of little
	for (c3p1::size_t i = 0; i <= big_len - little_len; i++)
	{
		bool match = true;
		for (c3p1::size_t j = 0; j < little_len; j++)
		{
			if (big[i + j] != little[j])
			{
				match = false;
				break;
			}
		}

		if (match == true)
		{
			return const_cast<char*>(big + i);
		}
	}

	// little not found
	return nullptr;
}

char* c3p1::string::strtok(char* restrict str, const char* restrict sep)
{
	// position pointer
	static char* wpos = nullptr;

	// check sep value
	if (sep == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strtok(str, const sep): sep is nullptr.");
	}

	if (str != nullptr)
	{
		wpos = str;
	}
	else if (wpos == nullptr)
	{
		// nothing to do
		return nullptr;
	}

	// get back to the position
	char* wpstart = wpos;
	while (*wpstart && c3p1::string::strchr(sep, *wpstart))
	{
		wpstart++;
	}

	if (*wpstart == '\0')
	{
		wpos = nullptr;
		return nullptr;
	}

	// find token's end
	char* wpend = wpstart;
	while (*wpend && !c3p1::string::strchr(sep, *wpend))
	{
		wpend++;
	}

	// format the token and set the position for the next time
	if (*wpend)
	{
		*wpend = '\0';
		wpos = wpend + 1;
	}
	else
	{
		// end of string
		wpos = nullptr;
	}

	return wpstart;
}

char* c3p1::string::strtok_r(char* str, const char* sep, char** last)
{
	// nope, using last
	// position pointer
	//static char* wpos = nullptr;

	// check sep value
	if (sep == nullptr)
	{
		throw c3p1::exception("Exception @c3p1::string::strtok_r(str, const sep, last): sep is nullptr.");
	}

	if (str != nullptr)
	{
		*last = str;
	}
	else if (*last == nullptr)
	{
		// nothing to do
		return nullptr;
	}

	// get back to the position
	char* wpstart = *last;

	// skip leading separators
	while (*wpstart && c3p1::string::strchr(sep, *wpstart))
	{
		wpstart++;
	}

	if (*wpstart == '\0')
	{
		*last = nullptr;
		return nullptr;
	}

	// find token's end
	char* wpend = wpstart;
	while (*wpend && !c3p1::string::strchr(sep, *wpend))
	{
		wpend++;
	}

	// format the token and set the position for the next time
	if (*wpend)
	{
		*wpend = '\0';
		*last = wpend + 1;
	}
	else
	{
		// end of string
		*last = nullptr;
	}

	return wpstart;
}

char* c3p1::string::strsep(char** stringp, const char* delim)
{
	// check stringp value
	if (stringp == nullptr || *stringp == nullptr)
	{
		return nullptr;
	}

	// init pointers
	char* start = *stringp;
	char* end = start;

	// move to first not delimiter character
	while (*end && c3p1::string::strchr(delim, *end)) {
		end++;
	}

	// string is empty or only made of delimiters
	if (*end == '\0') {
		*stringp = nullptr;
		return nullptr;
	}

	// token starts with the first not delimiter character
	start = end;

	// find end of token
	while (*end && !c3p1::string::strchr(delim, *end)) {
		end++;
	}

	// if a delimiter is found, replace it by '\0' to end the token
	if (*end) {
		*end = '\0';
		*stringp = end + 1;  // move to the next token
	}
	else {
		*stringp = nullptr;  // end of string
	}

	return start;
}

// class string implementation

c3p1::string::string()
{
	// initialise to empty string
	m_capacity = 0;
	m_size = 0;
	m_str = const_cast<char*>(mc_nullterm);
}

c3p1::string::string(const char* str)
{
	// check str pointer
	if (str != nullptr)
	{
		// allocate enough memory
		m_capacity = c3p1::string::strlen(str);
		m_size = m_capacity;
		m_str = new char[m_size + 1];

		// copy str
		c3p1::string::strcpy(m_str, str);
	}
	else
	{
		// initialise to empty string
		m_capacity = 0;
		m_size = 0;
		m_str = const_cast<char*>(mc_nullterm);
	}
}

c3p1::string::string(const string& copy)
{
	if (!copy.empty())
	{
		// copy size and capacity value, then allocate the ptr
		m_size = copy.m_size;
		m_capacity = m_size;
		m_str = new char[m_size + 1];

		// copy string & add the null-terminal for C string compatibility
		c3p1::string::strncpy(m_str, copy.m_str, copy.size());
		m_str[m_size] = '\0';
	}
	else
	{
		// initialise to empty string
		m_capacity = 0;
		m_size = 0;
		m_str = const_cast<char*>(mc_nullterm);
	}
}

c3p1::string::string(c3p1::string&& other) noexcept
	: m_str(other.m_str), m_size(other.m_size), m_capacity(other.m_capacity)
{
	// reinit source object
	other.m_str = const_cast<char*>(mc_nullterm);
	other.m_size = 0;
	other.m_capacity = 0;
}

c3p1::string::~string()
{
	// use appropriate delete operator
	if (m_capacity != 0)
	{
		delete[] m_str;
	}
}

c3p1::size_t c3p1::string::length() const
{
	return m_size;
}

c3p1::size_t c3p1::string::size() const
{
	// length() alias
	return m_size;
}

c3p1::size_t c3p1::string::capacity() const
{
	return m_capacity;
}

c3p1::size_t c3p1::string::max_size() const
{
	return c3p1::string::mc_max_size;
}

void c3p1::string::resize(c3p1::size_t new_size)
{
	if (new_size == 0) // point to empty string
	{
		if (m_capacity != 0)
		{
			delete[] m_str;
			m_capacity = 0;
			m_size = 0;
		}

		m_str = const_cast<char*>(mc_nullterm);
	}
	else if (new_size < m_capacity)
	{
		// cut the string
		m_str[new_size] = '\0';
		m_size = new_size;
	}
	else if (new_size > m_capacity)
	{
		// reallocates memory
		char* wp = new char[new_size + 1];

		// copy the string to the buffer
		c3p1::string::strncpy(wp, m_str, m_size);
		// add c on each byte to fill the buffer
		for (c3p1::size_t i = m_size; i < new_size; i++)
		{
			wp[i] = '\0';
		}
		// add the null terminal
		wp[new_size] = '\0';

		if (m_capacity != 0)
		{
			delete[] m_str;
		}
		m_str = wp;
		m_capacity = new_size;
	}
}

void c3p1::string::resize(c3p1::size_t new_size, char c)
{
	if (new_size == 0) // point to empty string
	{
		if (m_capacity != 0)
		{
			delete[] m_str;
			m_capacity = 0;
			m_size = 0;
		}

		m_str = const_cast<char*>(mc_nullterm);
	}
	else if (new_size < m_capacity)
	{
		// cut the string
		m_str[new_size] = '\0';
		m_size = new_size;
	}
	else if (new_size > m_capacity)
	{
		// reallocates memory
		char* wp = new char[new_size + 1];

		// copy the string to the buffer
		c3p1::string::strncpy(wp, m_str, m_size);
		// add c on each byte to fill the buffer
		for (c3p1::size_t i = m_size; i < new_size; i++)
		{
			wp[i] = c;
		}
		// add the null terminal
		wp[new_size] = '\0';

		if (m_capacity != 0)
		{
			delete[] m_str;
		}
		m_str = wp;
		// set proper size if c is '\0', does count it
		if (c != '\0')
		{
			m_size = new_size;
		}
		m_capacity = new_size;
	}
}

void c3p1::string::reserve(c3p1::size_t new_size)
{
	if (m_capacity == 0) // this is empty
	{
		// allocate memory & check result
		m_str = new char[new_size + 1];

		m_capacity = new_size;
		m_size = 0;
		*m_str = '\0';
	}
	else if (new_size > m_capacity)
	{
		// allocate a new bunch of memory
		char* wp = new char[new_size + 1];

		// copy string and fill the last bytes with '\0'
		c3p1::string::strncpy(wp, m_str, new_size);
		wp[m_size] = '\0'; // & write the last nullterminal

		// delete current ptr (capacity already checked)
		delete[] m_str;
		m_str = wp;
		m_capacity = new_size;
		// m_size = m_size; // should not have changed
	}
}

void c3p1::string::clear()
{
	if (m_capacity != 0)
	{
		delete[] m_str;
		m_str = const_cast<char*>(mc_nullterm);
		m_size = 0;
		m_capacity = 0;
	}
}

bool c3p1::string::empty() const
{
	return m_size == 0;
}

const char* c3p1::string::c_str() const
{
	return m_str;
}

const char* c3p1::string::data() const
{
	// alias for c_str
	return m_str;
}

void c3p1::string::shrink_to_fit()
{
	if (m_capacity > size())
	{
		if (this->empty())
		{
			delete[] m_str;
			m_str = const_cast<char*>(mc_nullterm);
			m_capacity = 0;
		}
		else
		{
			// realloc the required amount of memory
			char* wp = new char[m_size + 1];

			// copy m_str to buffer & add null terminal
			c3p1::string::strncpy(wp, m_str, m_size);
			wp[m_size] = '\0';

			delete[] m_str; // capacity already checked
			m_str = wp;
			m_capacity = m_size;
		}
	}
}

c3p1::string& c3p1::string::operator=(const char* str)
{
	if (str != nullptr)
	{
		c3p1::size_t str_size = c3p1::string::strlen(str);

		if (str_size == 0) // check if str is an empty string
		{
			// set up an empty string
			if (m_capacity != 0)
			{
				delete[] m_str;
			}
			m_capacity = 0;
			m_size = 0;
			m_str = const_cast<char*>(mc_nullterm);
		}
		else if (m_capacity < str_size) // capacity is not enough
		{
			// realloc memory
			if (m_capacity != 0)
			{
				delete[] m_str;
			}
			m_capacity = str_size;
			m_size = str_size;
			m_str = new char[m_size + 1];

			// copy the string & add the null terminal for C string compatibility
			c3p1::string::strncpy(m_str, str, str_size);
			m_str[m_size] = '\0';
		}
		else if (m_capacity >= str_size) // capacity is enough
		{
			// no allocation required
			// copy the string & add the null terminal for C string compatibility
			m_size = str_size;
			c3p1::string::strncpy(m_str, str, str_size);
			m_str[m_size] = '\0';
		}
	}

	return *this;
}

c3p1::string& c3p1::string::operator=(const c3p1::string& str)
{
	// check str, then copy it
	if (!str.empty() && &str != this)
	{
		if (str.m_size == 0) // check if str is an empty string
		{
			// set up an empty string
			if (m_capacity != 0)
			{
				delete[] m_str;
			}
			m_str = const_cast<char*>(mc_nullterm);
			m_size = 0;
			m_capacity = 0;
		}
		else if (m_capacity < str.m_size) // capacity is not enough
		{
			// realloc memory
			if (m_capacity != 0)
			{
				delete[] m_str;
			}
			m_size = str.m_size;
			m_capacity = m_size;
			m_str = new char[m_size + 1];

			// copy the string & add the null terminal for C string compatibility
			c3p1::string::strncpy(m_str, str.m_str, m_size);
			m_str[m_size] = '\0';
		}
		else if (m_capacity >= str.m_size) // capacity is enough
		{
			// no allocation required
			// copy the string & add the null terminal for C string compatibility
			m_size = str.m_size;
			c3p1::string::strncpy(m_str, str.m_str, m_size);
			m_str[m_size] = '\0';
		}
	}

	return *this;
}

c3p1::string& c3p1::string::operator=(char c)
{
	if (m_capacity == 0)
	{
		if (c != '\0')
		{
			// allocate memory & write c
			m_size = 1;
			m_capacity = 1;
			m_str = new char[m_size + 1];
			m_str[0] = c;
			// add the null terminal
			m_str[1] = '\0';
		}
	}
	else
	{
		if (c != '\0')
		{
			// write c & add the null terminal
			m_str[0] = c;
			m_str[1] = '\0';
			m_size = 1;
		}
	}

	return *this;
}

c3p1::string& c3p1::string::operator=(string&& other) noexcept
{
	if (this != &other)
	{
		// free the buffer if its required
		if (m_str != mc_nullterm)
		{
			delete[] m_str;
		}

		// move ownship
		m_str = other.m_str;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		// reset source object
		other.m_str = const_cast<char*>(mc_nullterm);
		other.m_size = 0;
		other.m_capacity = 0;
	}

	return *this;
}

char& c3p1::string::at(c3p1::size_t pos)
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::at(pos) volatile: attempt to write to an empty string.");
	}
	else if (pos > size())
	{
		throw c3p1::exception("Exception @c3p1::string::at(pos) volatile: index is out of bounds.");
	}

	// return a volatile reference to the char at m_str[pos]
	return m_str[pos];
}

const char& c3p1::string::at(c3p1::size_t pos) const
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::at(pos) const: attempt to read from an empty string.");
	}
	else if (pos > size())
	{
		throw c3p1::exception("Exception @c3p1::string::at(pos) const: index is out of bounds.");
	}

	// return a const reference to the char at m_str[pos]
	return m_str[pos];
}

char& c3p1::string::front()
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::front() volatile: attempt to write to an empty string.");
	}
	else
	{
		return m_str[0];
	}
}

const char& c3p1::string::front() const
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::front() volatile: attempt to read from an empty string.");
	}
	else
	{
		return m_str[0];
	}
}

char& c3p1::string::back()
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::back() volatile: attempt to write to an empty string.");
	}
	else
	{
		return m_str[m_size - 1];
	}
}

const char& c3p1::string::back() const
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::back() const: attempt to write to an empty string.");
	}
	else
	{
		return m_str[m_size - 1];
	}
}

c3p1::string& c3p1::string::append(const string& str)
{
	// check str
	if (!str.empty())
	{
		if (m_capacity >= str.m_size + m_size) // there's enough memory
		{
			// no reallaction
			c3p1::string::strncat(m_str, str.m_str, str.m_size);
			// strncat return value is guaranted to be null terminated
			m_size += str.m_size;
		}
		else // there's not enough memory
		{
			// reallocate memory
			char* wp = new char[m_size + str.m_size + 1];
			c3p1::string::strcpy(wp, m_str);
			c3p1::string::strncat(wp, str.m_str, str.m_size);

			if (m_capacity != 0)
			{
				delete[] m_str;
			}

			m_str = wp;
			m_size += str.m_size;
			m_capacity = m_size;
		}
	}

	return *this;
}

c3p1::string& c3p1::string::append(const char* str)
{
	// check str
	if (str != nullptr)
	{
		c3p1::size_t str_len = c3p1::string::strlen(str);
		if (str_len > 0)
		{
			if (m_capacity >= str_len + m_size) // there's enough memory
			{
				// no reallocation
				c3p1::string::strncat(m_str, str, str_len);
				// strncat return value is guaranted to be null-terminated
				m_size += str_len;
			}
			else // there's not enough memory
			{
				// reallocate memory
				char* wp = new char[m_size + str_len + 1];
				c3p1::string::strcpy(wp, m_str);
				c3p1::string::strncat(wp, str, str_len);

				if (m_capacity != 0)
				{
					delete[] m_str;
				}

				m_str = wp;
				m_size += str_len;
				m_capacity = m_size;
			}
		}
	}

	return *this;
}

c3p1::string& c3p1::string::append(c3p1::size_t n, char c)
{
	// check if string is long enough
	if (m_capacity >= m_size + n)
	{
		// there's enough memory
		for (c3p1::size_t i = m_size; i < m_size + n; i++)
		{
			m_str[i] = c;
		}
		m_str[m_size + n] = '\0';
		if (c != '\0')
		{
			m_size += n;
		}
	}
	else
	{
		// reallocation required
		char* wp = new char[m_size + n + 1];

		// copy string & add n times c
		c3p1::string::strcpy(wp, m_str);
		for (c3p1::size_t i = m_size; i < m_size + n; i++)
		{
			wp[i] = c;
		}
		wp[m_size + n] = '\0';

		// change size only if c is not a null-terminal character
		c3p1::size_t final_capacity = m_size + n;
		if (c != '\0')
		{
			m_size += n;
		}
		if (m_capacity != 0)
		{
			delete[] m_str;
		}
		m_str = wp;
		m_capacity = final_capacity;
	}

	return *this;
}

c3p1::string& c3p1::string::append(const char* str, size_t size)
{
	// check str and size value
	if (str != nullptr && size != 0)
	{
		c3p1::size_t str_len = c3p1::string::strlen(str);
		if (str_len > 0)
		{
			if (m_capacity >= str_len + m_size) // there's enough memory
			{
				// no reallocation
				c3p1::string::strncat(m_str, str, str_len);
				// strncat return value is guaranted to be null-terminated
				m_size += str_len;
			}
			else // there's not enough memory
			{
				// reallocate memory
				char* wp = new char[m_size + size + 1];
				c3p1::string::strcpy(wp, m_str);
				c3p1::string::strncat(wp, str, size);

				if (m_capacity != 0)
				{
					delete[] m_str;
				}

				m_str = wp;
				m_size += size;
				m_capacity = m_size;
			}
		}
	}

	return *this;
}

char& c3p1::string::operator[](c3p1::size_t pos)
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::operator[] volatile: attempt to write to an empty string.");
	}
	else if (pos > size())
	{
		throw c3p1::exception("Exception @c3p1::string::operator[] volatile: index is out of bounds.");
	}

	// return a volatile reference to the char at m_str[pos]
	return m_str[pos];
}
const char& c3p1::string::operator[](c3p1::size_t pos) const
{
	if (empty())
	{
		throw c3p1::exception("Exception @c3p1::string::operator[] const: attempt to read from an empty string.");
	}
	else if (pos > size())
	{
		throw c3p1::exception("Exception @c3p1::string::operator[] const: index is out of bounds.");
	}

	// return a const reference to the char at m_str[pos]
	return m_str[pos];
}

// friend functions and operators
void c3p1::swap(c3p1::string& first, c3p1::string& second) noexcept
{
	// swap intern pointers
	char* wp = first.m_str;
	first.m_str = second.m_str;
	second.m_str = wp;

	// swap m_capacity values
	c3p1::size_t i = first.m_capacity;
	first.m_capacity = second.m_capacity;
	second.m_capacity = i;

	// swap m_size values
	c3p1::size_t j = first.m_size;
	first.m_size = second.m_size;
	second.m_size = j;
}

c3p1::string c3p1::operator+ (const c3p1::string& first, const c3p1::string& second)
{
	c3p1::string buffer = first;
	buffer.reserve(first.m_size + second.m_size);
	buffer.append(second);

	return buffer;
}

c3p1::string c3p1::operator+ (const c3p1::string& first, const char* second)
{
	c3p1::string buffer = first;
	buffer.reserve(first.m_size + c3p1::string::strlen(second));
	buffer.append(second);

	return buffer;
}

c3p1::string c3p1::operator+(const char* first, const c3p1::string& second)
{
	c3p1::string buffer = first;
	buffer.reserve(buffer.m_size + second.m_size);
	buffer.append(second);

	return buffer;
}

c3p1::string c3p1::operator+(const c3p1::string& first, char second)
{
	c3p1::string buffer = first;

	if (second != '\0')
	{
		buffer.reserve(buffer.m_size + 1);
		buffer.append(1, second);
	}

	return buffer;
}

c3p1::string c3p1::operator+(char first, const c3p1::string& second)
{
	c3p1::string buffer;
	if (first != '\0')
	{
		buffer = first;
		buffer.reserve(buffer.m_size + second.m_size);
		buffer.append(second);
		return buffer;
	}
	else
	{
		return second;
	}
}

std::ostream& c3p1::operator<<(std::ostream& os, const c3p1::string& str)
{
	return os << str.c_str();
}

std::istream& c3p1::operator>>(std::istream& is, c3p1::string& str)
{
	// clear  the current string
	str.clear();

	char c;
	while (is.get(c))
	{
		if (std::isspace(static_cast<unsigned char>(c)))
		{
			break;
		}
		str.append(&c, 1);
	}
	
	return is;
}

std::istream& c3p1::getline(std::istream& is, string& str, char delim)
{
	str.clear();

	char c;
	while (is.get(c))
	{
		if (c == delim)
		{
			break;
		}
		str.append(&c, 1);
	}

	if (!is && str.empty())
	{
		is.setstate(std::ios::failbit);
	}

	return is;
}

std::istream& c3p1::getline(std::istream& is, string& str)
{
	return getline(is, str, '\n');
}