#pragma once

namespace c3p1
{
	class string
	{
	public:
		string();
		string(const char* str);
		string(string& str);
		~string();

		size_t length() const;
		string& operator = (const char* str);
	public:
		char* m_str;
		size_t m_memsize;

		// local implementation of string.h libc
		static int _strcpy(char* dest, const char* src);
		static int _strlen(const char* str);
		static char* _strcat(char* first, const char* second);
	};
}
