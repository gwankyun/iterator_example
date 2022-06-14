#pragma once
#include "common.hpp"

template<typename T>
struct LegacyIterator
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::input_iterator_tag iterator_category;

    LegacyIterator() : m_ptr(NULLPTR) {}

    LegacyIterator(const LegacyIterator& other) : m_ptr(other.m_ptr) {}
    
    LegacyIterator& operator=(const LegacyIterator& other)
    {
        if (this != &other)
        {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    ~LegacyIterator() {}

    reference operator*()
    {
        return *m_ptr;
    }

    reference operator*() const
    {
        return *m_ptr;
    }

    LegacyIterator& operator++()
    {
        m_ptr++;
        return *this;
    }

    LegacyIterator& operator++(int)
    {
        m_ptr++;
        return *this;
    }

    LegacyIterator(T* ptr) : m_ptr(ptr) {}

    LegacyIterator& operator=(const T* ptr)
    {
        m_ptr = ptr;
        return *this;
    }

private:
    T* m_ptr;
};
