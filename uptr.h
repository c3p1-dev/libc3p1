// uptr.h
// Copyright© C3P1 - https://github.com/c3p1-dev/libc3p1
// BSD3 License - https://github.com/c3p1-dev/libc3p1/blob/master/LICENSE.txt
// uptr is my implementation of std::unique_ptr

#pragma once

#include "string.h"

/*namespace c3p1::ptr
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
	public:
	    constexpr uptr() noexcept;
		~uptr() { if (m_ptr != nullptr) delete[] m_ptr; m_ptr = nullptr; }

	protected:
		T* m_ptr;
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
constexpr c3p1::ptr::uptr<T[]>::uptr() noexcept
{
	// init internal pointer
	m_ptr = nullptr;
}

template <class T>
c3p1::ptr::uptr<T>::~uptr()
{
	// delete managed object when this is destructed
	if (m_ptr != nullptr)
		delete m_ptr;
}
*/

#pragma once

#include <utility> // for std::move

namespace c3p1::ptr
{
	// unique pointer for single objects
	template <class T>
	class uptr
	{
	public:
		constexpr uptr() noexcept : m_ptr(nullptr) {}
		explicit uptr(T* ptr) noexcept : m_ptr(ptr) {}

		~uptr() { delete m_ptr; }

		// only one instance is allowed
		uptr(const uptr&) = delete;
		uptr& operator=(const uptr&) = delete;

		// for move
		uptr(uptr&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }

		// operator =
		uptr& operator=(uptr&& other) noexcept 
		{
			if (this != &other) {
				delete m_ptr;
				m_ptr = other.m_ptr;
				other.m_ptr = nullptr;
			}
			return *this;
		}

		T& operator*() const { return *m_ptr; }
		T* operator->() const { return m_ptr; }

		T* get() const noexcept { return m_ptr; }
		explicit operator bool() const noexcept { return m_ptr != nullptr; }

		T* release() noexcept
		{
			T* tmp = m_ptr;
			m_ptr = nullptr;
			return tmp;
		}

		void reset(T* ptr = nullptr)
		{
			if (m_ptr != ptr)
			{
				delete m_ptr;
				m_ptr = ptr;
			}
		}

	protected:
		T* m_ptr;
	};

	// specialization for arrays
	template <class T>
	class uptr<T[]> {
	public:
		constexpr uptr() noexcept : m_ptr(nullptr) {}
		explicit uptr(T* ptr) noexcept : m_ptr(ptr) {}

		~uptr() { delete[] m_ptr; }

		uptr(const uptr&) = delete;
		uptr& operator=(const uptr&) = delete;

		uptr(uptr&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }

		uptr& operator=(uptr&& other) noexcept
		{
			if (this != &other)
			{
				delete[] m_ptr;
				m_ptr = other.m_ptr;
				other.m_ptr = nullptr;
			}
			return *this;
		}

		T& operator[](c3p1::size_t index) const { return m_ptr[index]; }

		T* get() const noexcept { return m_ptr; }
		explicit operator bool() const noexcept { return m_ptr != nullptr; }

		T* release() noexcept
		{
			T* tmp = m_ptr;
			m_ptr = nullptr;
			return tmp;
		}

		void reset(T* ptr = nullptr)
		{
			if (m_ptr != ptr)
			{
				delete[] m_ptr;
				m_ptr = ptr;
			}
		}

	protected:
		T* m_ptr;
	};

} // namespace c3p1::ptr