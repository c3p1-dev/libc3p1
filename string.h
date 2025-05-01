#pragma once

namespace c3p1
{
	// typedef
	typedef unsigned long long size_t;
	typedef long long ssize_t;

	class string
	{
	public:
		// public members
		// constructors and destructor
		string();
		string(const char* str);
		string(string& str);
		~string();

		// public functions and operators
		ssize_t length() const;
		string& operator = (const char* str);

	protected:
		// protected members
		char* m_str;
		size_t m_memsize;

	private:
		// local implementation of string.h libc
		static void* memcpy(void* dest, const void* src, size_t n);
		static char* strcpy(char* dest, const char* src);
		static char* strcat(char* first, const char* second);
		static ssize_t strlen(const char* str);
	};
}
