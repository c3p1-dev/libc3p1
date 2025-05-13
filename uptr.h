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
	public:
		constexpr uptr() noexcept;
		explicit uptr(T* pointer) noexcept;
		~uptr();

		T& operator*() const { return *m_ptr; }
		T* operator->() const { return m_ptr; }

	protected:
			T* m_ptr;
	};

	// specialized version for dynamically-allocated arrays
	template <class T>
	class uptr<T[]>
	{
	};
}

// template functions implementations
// must be in the header file
template <class T>
constexpr c3p1::ptr::uptr<T>::uptr() noexcept
{
	// init internal pointer
	m_ptr = nullptr;
}

template <class T>
c3p1::ptr::uptr<T>::uptr(T* pointer) noexcept
{
	// init internal pointer
	m_ptr = pointer;
}

template <class T>
c3p1::ptr::uptr<T>::~uptr()
{
	// delete managed object when this is destructed
	if (m_ptr != nullptr)
		delete m_ptr;
}