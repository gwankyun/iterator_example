#pragma once
#include "common.hpp"
#include "LegacyForwardIterator.hpp"

template<typename T>
struct LegacyBidirectionalIterator
{
    typedef LegacyForwardIterator<T> Iter_t;
#ifdef __cpp_lib_concepts
    using iterator_concept = std::bidirectional_iterator_tag;
#endif
    typedef typename Iter_t::difference_type difference_type;
    typedef typename Iter_t::value_type value_type;
    typedef typename Iter_t::pointer pointer;
    typedef typename Iter_t::reference reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    LegacyBidirectionalIterator() {}

    LegacyBidirectionalIterator(const LegacyBidirectionalIterator& other)
    : m_iter(other.m_iter)
    {}

    LegacyBidirectionalIterator& operator=(const LegacyBidirectionalIterator& other)
    {
        if (this != &other)
        {
            m_iter = other.m_iter;
        }
        return *this;
    }

    ~LegacyBidirectionalIterator() {}

    reference operator*() const
    {
        return *m_iter;
    }

    LegacyBidirectionalIterator& operator++()
    {
        ++m_iter;
        return *this;
    }

    LegacyBidirectionalIterator& operator--()
    {
        --m_iter;
        return *this;
    }

    LegacyBidirectionalIterator operator++(int)
    {
        LegacyBidirectionalIterator ip = *this;
        ++(*this);
        return ip;
    }

    LegacyBidirectionalIterator operator--(int)
    {
        LegacyBidirectionalIterator ip = *this;
        --(*this);
        return ip;
    }

    pointer operator->()
    {
        return m_iter.operator->();
    }

    LegacyBidirectionalIterator(T* ptr) : m_iter(ptr) {}

    LegacyBidirectionalIterator& operator=(const T* ptr)
    {
        m_iter = ptr;
        return *this;
    }

    int compare(const LegacyBidirectionalIterator& other)
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

    T* data()
    {
        return m_iter.data();
    }

private:
    Iter_t m_iter;
};

template<typename T>
inline bool operator==(const LegacyBidirectionalIterator<T>& lhs, const LegacyBidirectionalIterator<T>& rhs)
{
    return lhs.compare(rhs) == 0;
}

template<typename T>
inline bool operator!=(const LegacyBidirectionalIterator<T>& lhs, const LegacyBidirectionalIterator<T>& rhs)
{
    return !(lhs == rhs);
}
