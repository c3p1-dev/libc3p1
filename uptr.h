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
		constexpr uptr() noexcept;
		explicit uptr(T* pointer) noexcept;

		~uptr();

		protected:
			T* m_ptr;
	};

	// specialized version for dynamically-allocated arrays
	template <class T>
	class uptr<T[]>
	{
	};
}