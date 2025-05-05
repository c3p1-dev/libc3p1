#include "string.h"
#include "exception.h"

// local implementation of string.h libc

void* c3p1::string::memcpy(void* restrict dst, const void* restrict src, c3p1::size_t size)
{
	// check if dst and src are not nullptr
	if (dst == nullptr && src == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memcpy(dst, const src, size): src is nullptr.");
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
		throw exception("Exception @c3p1::string::mempcpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::mempcpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::mempcpy(dst, const src, size): src is nullptr.");
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
		throw exception("Exception @c3p1::string::memccpy(dst, const src, searchedbyte, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::memccpy(dst, const src, searchedbyte, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memccpy(dst, const src, searchedbyte, size): src is nullptr.");
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
		throw exception("Exception @c3p1::string::memchr(const memory_block, searched_byte, size): memory_block is nullptr.");
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
		throw exception("Exception @c3p1::string::memrchr(const memory_block, searched_byte, size): memory_block is nullptr.");
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
		throw exception("Exception @c3p1::string::memmem(const big, big_size, const little, litte_size): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw exception("Exception @c3p1::string::memmem(const big, big_size, const little, litte_size): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw exception("Exception @c3p1::string::memmem(const big, big_size, const little, litte_size): little is nullptr.");
	}

	// cast raw pointers
	unsigned char* wb = const_cast<unsigned char*>(static_cast<const unsigned char*>(big));
	unsigned char* wl = const_cast<unsigned char*>(static_cast<const unsigned char*>(little));

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
	for (c3p1::size_t i = 0; i < big_size; i++)
	{
		c3p1::size_t j = 0;
		while (j < little_size && wb[i + j] == wl[j])
		{
			j++;
		}
		if (j == little_size)
		{
			return static_cast<void*>(wb + i);
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
		throw exception("Exception @c3p1::string::memcmp(first, const second, size): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, const second, size): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::memcmp(first, const second, size): second is nullptr.");
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
		throw exception("Exception @c3p1::string::memmove(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::memmove(dst, const src, size): src is nullptr.");
	}

	// create a n bytes buffer and manage allocation failure
	unsigned char* wp = new unsigned char[size];
	if (wp != nullptr)
	{
		// copy src to buffer
		memcpy(static_cast<void*>(wp), src, size);

		// copy buffer to dst
		memcpy(dst, wp, size);
		delete[] wp;

		return dst;
	}
	else
	{
		throw exception("Exception @c3p1::string::memmove(dst, const src, size): memory allocation for the buffer has failed.");
	}
}

void* c3p1::string::memset(void* dst, unsigned char byte_val, c3p1::size_t size)
{
	// check dst
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::memset(dst, byte_val, size) : dst is nullptr.");
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
		throw exception("Exception @c3p1::string::strcpy(dst, const src): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dst, const src): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strcpy(dst, const src): src is nullptr.");
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
		throw exception("Exception @c3p1::string::strncpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::strncpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strncpy(dst, const src, size): src is nullptr.");
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
		throw exception("Exception @c3p1::string::stpcpy(dst, const src): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::stpcpy(dst, const src): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::stpcpy(dst, const src): src is nullptr.");
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
		throw exception("Exception @c3p1::string::stpncpy(dst, const src, size): dst and src are nullptr.");
	}
	if (dst == nullptr)
	{
		throw exception("Exception @c3p1::string::stpncpy(dst, const src, size): dst is nullptr.");
	}
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::stpncpy(dst, const src, size): src is nullptr.");
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
		throw exception("Exception @c3p1::string::strcat(str, const append): str and append are nullptr.");
	}
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(str, const append): str is nullptr.");
	}
	if (append == nullptr)
	{
		throw exception("Exception @c3p1::string::strcat(str, const append): append is nullptr.");
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
		throw exception("Exception @c3p1::string::strncat(str, const append, size): str and append are nullptr.");
	}
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(str, const append, size): str is nullptr.");
	}
	if (append == nullptr)
	{
		throw exception("Exception @c3p1::string::strncat(str, const append, size): append is nullptr.");
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
		throw exception("Exception @c3p1::string::strlen(const str): str is nullptr.");
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
		throw exception("Exception @c3p1::string::strnlen(const str, maxlen): str is nullptr.");
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
		throw exception("Exception @c3p1::string::strcmp(first, const second): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, const second): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcmp(first, const second): second is nullptr.");
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
		throw exception("Exception @c3p1::string::strcasecmp(first, const second): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strcasecmp(first, const second): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcasecmp(first, const second): second is nullptr.");
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
		throw exception("Exception @c3p1::string::strcasecmp(first, const second): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strcasecmp(first, const second): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strcasecmp(first, const second): second is nullptr.");
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
		throw exception("Exception @c3p1::string::strncmp(first, const second, size): first and second are nullptr.");
	}
	if (first == nullptr)
	{
		throw exception("Exception @c3p1::string::strncmp(first, const second, size): first is nullptr.");
	}
	if (second == nullptr)
	{
		throw exception("Exception @c3p1::string::strncmp(first, const second, size): second is nullptr.");
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
		throw exception("Exception @c3p1::string::strdup(const src): src is nullptr.");
	}

	// allocate memory and copy src
	char* p = new char[c3p1::string::strlen(src) + 1];

	if (p != nullptr)
	{
		c3p1::string::strcpy(p, src);
		return p;
	}
	else
	{
		throw exception("Exception @c3p1::string::strdup(const src): memory allocation for the new string has failed.");
	}
}

char* c3p1::string::strndup(const char* src, c3p1::size_t size)
{
	// check src value
	if (src == nullptr)
	{
		throw exception("Exception @c3p1::string::strndup(const src, size): src is nullptr.");
	}

	char* p = new char[size + 1];

	if (p == nullptr)
	{
		throw exception("Exception @c3p1::string::strndup(const src, size): memory allocation for the new string has failed.");
	}

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
		throw exception("Exception @c3p1::string::strchr(const str, searched_char): str is nullptr.");
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
		throw exception("Exception @c3p1::string::strrchr(const str, searched_char): str is nullptr.");
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
		throw exception("Exception @c3p1::string::strspn(const str, const accepted): str is nullptr.");
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
		throw exception("Exception @c3p1::string::strcspn(const str, const accepted): str is nullptr.");
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
		throw exception("Exception @c3p1::string::strpbrk(const str, const charset): str and charset are nullptr.");
	}
	if (str == nullptr)
	{
		throw exception("Exception @c3p1::string::strpbrk(const str, const charset): str is nullptr.");
	}
	if (charset == nullptr)
	{
		throw exception("Exception @c3p1::string::strpbrk(const str, const charset): charset is nullptr.");
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
		throw exception("Exception @c3p1::string::strstr(const big, const little): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw exception("Exception @c3p1::string::strstr(const big, const little): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw exception("Exception @c3p1::string::strstr(const big, const little): little is nullptr.");
	}

	// search the first occurence of big
	return static_cast<char*>(c3p1::string::memmem(big, c3p1::string::strlen(big) + 1, little, string::strlen(little) + 1));
}

char* c3p1::string::strcasestr(const char* big, const char* little)
{
	// check big and first value
	if (big == nullptr && little == nullptr)
	{
		throw exception("Exception @c3p1::string::strstr(const big, const little): big and little are nullptr.");
	}
	if (big == nullptr)
	{
		throw exception("Exception @c3p1::string::strstr(const big, const little): big is nullptr.");
	}
	if (little == nullptr)
	{
		throw exception("Exception @c3p1::string::strstr(const big, const little): little is nullptr.");
	}

	// first, transform little and big to lowered  strings
	c3p1::size_t big_len = c3p1::string::strlen(big);
	c3p1::size_t little_len = c3p1::string::strlen(little);

	if (big_len < little_len)
	{
		// big is shorter than little, little can't be found
		return nullptr;
	}

	// cast big and little to volatile pointers
	char* wb = new char[big_len + 1];
	char* wl = new char[little_len + 1];

	if (wb == nullptr || wl == nullptr)
	{
		// exception for buffers memory allocation failed
		throw exception("Exception @c3p1::string::strcasestr(const big, const little): memory allocation for the buffers has failed.");
	}

	for (c3p1::size_t i = 0; i < big_len; i++)
	{
		wb[i] = c3p1::string::to_lower_ascii(big[i]);
	}
	wb[big_len] = '\0';

	for (c3p1::size_t i = 0; i < little_len; i++)
	{
		wl[i] = c3p1::string::to_lower_ascii(little[i]);
	}
	wl[little_len] = '\0';

	// search the first occurence of big
	char* wr = c3p1::string::strstr(wb, wl);

	if (wr == nullptr)
	{
		// delete buffers
		delete[] wb;
		delete[] wl;
		// little not found
		return nullptr;
	}
	else
	{
		// get the address of little first occurence
		size_t offset = static_cast<size_t>(wr - wb);
		// delete buffers
		delete[] wb;
		delete[] wl;

		// return address of the first occurence of little in big
		return const_cast<char*>(big+offset);
	}
}

// class string implementation

c3p1::string::string()
{
	// Initialise to empty string
	m_str = new char;

	// check allocation result
	if (m_str == nullptr)
	{
		throw exception("Exception @c3p1::string::string(void): memory allocation for the string has failed.");
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
		m_memsize = c3p1::string::strlen(str) + 1;
		m_str = new char[m_memsize];
		
		// check allocation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(str): memory allocation for the string has failed.");
		}

		// copy str
		strcpy(m_str, str);
	}
	else
	{
		// no-exception on string constructors
		// initialise to empty string
		m_str = new char;

		// check allocation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(str): memory allocation for the string has failed.");
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
		throw exception("Exception c3p1::string::string(&copy): copy.m_str is nullptr.");
	}

	if (copy.m_memsize != 0)
	{
		m_memsize = copy.m_memsize;
		m_str = new char[m_memsize];

		// check allocation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(&copy): memory allocation for the string has failed.");
		}

		strcpy(m_str, copy.m_str);
	}
	else
	{
		m_str = new char;

		// check allcation result
		if (m_str == nullptr)
		{
			throw exception("Exception @c3p1::string::string(&copy): memory allocation for the string has failed.");
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
	return c3p1::string::strlen(m_str);
}

c3p1::string& c3p1::string::operator=(const char* str)
{
	if (str != nullptr)
	{
		c3p1::size_t len = c3p1::string::strlen(str);
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
				throw exception("Exception @c3p1::string::operator(=) (const str): memory allocation for the string has failed.");
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