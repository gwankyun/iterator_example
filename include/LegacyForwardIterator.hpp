#pragma once
#include "common.hpp"
#include "LegacyInputIterator.hpp"

template<typename T>
struct LegacyForwardIterator
{
    typedef LegacyInputIterator<T> Iter_t;
#ifdef __cpp_lib_concepts
    using iterator_concept = std::forward_iterator_tag;
#endif
    typedef typename Iter_t::difference_type difference_type;
    typedef typename Iter_t::value_type value_type;
    typedef typename Iter_t::pointer pointer;
    typedef typename Iter_t::reference reference;
    typedef std::forward_iterator_tag iterator_category;

    LegacyForwardIterator() {}

    LegacyForwardIterator(const LegacyForwardIterator& other)
    : m_iter(other.m_iter)
    {}

    LegacyForwardIterator& operator=(const LegacyForwardIterator& other)
    {
        if (this != &other)
        {
            m_iter = other.m_iter;
        }
        return *this;
    }

    ~LegacyForwardIterator() {}

    reference operator*() const
    {
        return *m_iter;
    }

    LegacyForwardIterator& operator++()
    {
        ++m_iter;
        return *this;
    }

    LegacyForwardIterator operator++(int)
    {
        // ++m_iter;
        LegacyForwardIterator ip = *this;
        ++(*this);
        return ip;
    }

    pointer operator->()
    {
        return m_iter.operator->();
    }

    LegacyForwardIterator(T* ptr) : m_iter(ptr) {}

    LegacyForwardIterator& operator=(const T* ptr)
    {
        m_iter = ptr;
        return *this;
    }

    int compare(const LegacyForwardIterator& other)
    {
        if (m_iter < other.m_iter)
        {
            return -1;
        }
        else if (m_iter == other.m_iter)
        {
            return 0;
        }
        else // if (m_iter > other.m_iter)
        {
            return 1;
        }
    }

private:
    Iter_t m_iter;
};

template<typename T>
inline bool operator==(const LegacyForwardIterator<T>& lhs, const LegacyForwardIterator<T>& rhs)
{
    return lhs.compare(rhs) == 0;
}

template<typename T>
inline bool operator!=(const LegacyForwardIterator<T>& lhs, const LegacyForwardIterator<T>& rhs)
{
    return !(lhs == rhs);
}
