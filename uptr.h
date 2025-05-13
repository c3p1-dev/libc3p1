// uptr.h
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// uptr is my implementation of std::unique_ptr

#pragma once

namespace c3p1::ptr
{
	template <class T>
	class uptr
	{
	};

	// specialized version for dynamically-allocated arrays
	template <class T>
	class uptr<T[]>
	{
	};
}