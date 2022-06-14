#pragma once
#include "common.hpp"
#include "LegacyIterator.hpp"

template<typename T>
struct LegacyInputIterator
{
    typedef LegacyIterator<T> Iter_t;
#ifdef __cpp_lib_concepts
    using iterator_concept = std::input_iterator_tag;
#endif
    typedef typename Iter_t::difference_type difference_type;
    typedef typename Iter_t::value_type value_type;
    typedef typename Iter_t::pointer pointer;
    typedef typename Iter_t::reference reference;
    typedef std::input_iterator_tag iterator_category;

    LegacyInputIterator() {}

    LegacyInputIterator(const LegacyInputIterator& other)
    : m_iter(other.m_iter)
    {}

    LegacyInputIterator& operator=(const LegacyInputIterator& other)
    {
        if (this != &other)
        {
            m_iter = other.m_iter;
        }
        return *this;
    }

    ~LegacyInputIterator() {}

    reference operator*() const
    {
        return *m_iter;
    }

    LegacyInputIterator& operator++()
    {
        ++m_iter;
        return *this;
    }

    LegacyInputIterator& operator++(int)
    {
        ++m_iter;
        return *this;
    }

    pointer operator->()
    {
        return m_iter.operator->();
    }

    LegacyInputIterator(T* ptr) : m_iter(ptr) {}

    LegacyInputIterator& operator=(const T* ptr)
    {
        m_iter = ptr;
        return *this;
    }

    int compare(const LegacyInputIterator& other)
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
inline bool operator==(const LegacyInputIterator<T>& lhs, const LegacyInputIterator<T>& rhs)
{
    return lhs.compare(rhs) == 0;
}

template<typename T>
inline bool operator!=(const LegacyInputIterator<T>& lhs, const LegacyInputIterator<T>& rhs)
{
    return !(lhs == rhs);
}
