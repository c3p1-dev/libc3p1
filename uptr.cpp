#include "uptr.h"

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