// exception.h
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// base exception class implementation.

#pragma once

namespace c3p1
{
	class exception
	{
	public:
		// constructor (const msg)
		exception(const char* msg);

		// const
		const char* message;
	};
}