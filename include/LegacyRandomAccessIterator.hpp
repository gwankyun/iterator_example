#pragma once
#include "common.hpp"
#include "LegacyBidirectionalIterator.hpp"

template<typename T>
struct LegacyRandomAccessIterator
{
    typedef LegacyBidirectionalIterator<T> Iter_t;
#ifdef __cpp_lib_concepts
    using iterator_concept = std::random_access_iterator_tag;
#endif
    typedef typename Iter_t::difference_type difference_type;
    typedef typename Iter_t::value_type value_type;
    typedef typename Iter_t::pointer pointer;
    typedef typename Iter_t::reference reference;
    typedef std::random_access_iterator_tag iterator_category;

    LegacyRandomAccessIterator() {}

    LegacyRandomAccessIterator(const LegacyRandomAccessIterator& other)
    : m_ptr(other.m_ptr)
    {}

    LegacyRandomAccessIterator& operator=(const LegacyRandomAccessIterator& other)
    {
        if (this != &other)
        {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    ~LegacyRandomAccessIterator() {}

    reference operator*() const
    {
        return *m_ptr;
    }

    LegacyRandomAccessIterator& operator++()
    {
        ++m_ptr;
        return *this;
    }

    LegacyRandomAccessIterator& operator--()
    {
        --m_ptr;
        return *this;
    }

    LegacyRandomAccessIterator operator++(int)
    {
        LegacyRandomAccessIterator ip = *this;
        ++(*this);
        return ip;
    }

    LegacyRandomAccessIterator operator--(int)
    {
        LegacyRandomAccessIterator ip = *this;
        --(*this);
        return ip;
    }

    LegacyRandomAccessIterator& operator+=(difference_type n)
    {
        m_ptr += n;
        return *this;
    }

    LegacyRandomAccessIterator& operator-=(difference_type n)
    {
        m_ptr -= n;
        return *this;
    }

    pointer operator->()
    {
        return m_ptr;
    }

    reference operator[](difference_type n)
    {
        return *(m_ptr + n);
    }

    reference operator[](difference_type n) const
    {
        return *(m_ptr + n);
    }

    LegacyRandomAccessIterator(T* ptr) : m_ptr(ptr) {}

    LegacyRandomAccessIterator& operator=(const T* ptr)
    {
        m_ptr = ptr;
        return *this;
    }

    int compare(const LegacyRandomAccessIterator& other)
    {
        if (m_ptr < other.m_ptr)
        {
            return -1;
        }
        else if (m_ptr == other.m_ptr)
        {
            return 0;
        }
        else // if (m_iter > other.m_iter)
        {
            return 1;
        }
    }

    difference_type difference(const LegacyRandomAccessIterator& other)
    {
        return m_ptr - other.m_ptr;
    }

private:
    T* m_ptr;
};

template<typename T>
inline bool operator==(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    return lhs.compare(rhs) == 0;
}

template<typename T>
inline bool operator!=(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline LegacyRandomAccessIterator<T> operator+(
    const LegacyRandomAccessIterator<T>& iter,
    typename LegacyRandomAccessIterator<T>::difference_type n)
{
    LegacyRandomAccessIterator<T> temp = iter;
    return temp += n;
}

template<typename T>
inline LegacyRandomAccessIterator<T> operator+(
    typename LegacyRandomAccessIterator<T>::difference_type n,
    const LegacyRandomAccessIterator<T>& iter)
{
    LegacyRandomAccessIterator<T> temp = iter;
    return temp += n;
}

template<typename T>
inline LegacyRandomAccessIterator<T> operator-(
    const LegacyRandomAccessIterator<T>& iter,
    typename LegacyRandomAccessIterator<T>::difference_type n)
{
    LegacyRandomAccessIterator<T> temp = iter;
    return temp -= n;
}

template<typename T>
inline typename LegacyRandomAccessIterator<T>::difference_type operator-(
    const LegacyRandomAccessIterator<T>& lhs,
    const LegacyRandomAccessIterator<T>& rhs)
{
    return lhs.difference(rhs);
}

template<typename T>
inline bool operator<(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    return rhs - lhs > 0;
}

template<typename T>
inline bool operator>(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline bool operator<=(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    return !(lhs > rhs);
}
