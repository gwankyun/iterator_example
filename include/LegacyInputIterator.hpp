#pragma once
#include "common.hpp"
#include "LegacyIterator.hpp"

template<typename Iter>
struct LegacyInputIterator
    : public Indirection<LegacyInputIterator<Iter>, Iter>
    , public Increment<LegacyInputIterator<Iter>, Iter>
{
#ifdef __cpp_lib_concepts
    using iterator_concept = std::input_iterator_tag;
#endif

    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;

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

    pointer operator->()
    {
        //return m_iter.operator->();
        return Iter::member_access(m_iter);
    }

    LegacyInputIterator(pointer ptr) : m_iter(ptr) {}

    LegacyInputIterator& operator=(const pointer ptr)
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

    pointer& get()
    {
        return m_iter;
    }

    const pointer& get() const
    {
        return m_iter;
    }

private:
    pointer m_iter;
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
