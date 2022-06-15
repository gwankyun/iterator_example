#pragma once
#include "common.hpp"
#include "LegacyBidirectionalIterator.hpp"

template<typename Iter>
struct LegacyRandomAccessIterator
    : public Indirection<LegacyRandomAccessIterator<Iter>, Iter>
    , public Increment<LegacyRandomAccessIterator<Iter>, Iter>
    , public Decrement<LegacyRandomAccessIterator<Iter>, Iter>
{
    //typedef LegacyBidirectionalIterator<T> Iter_t;
#ifdef __cpp_lib_concepts
    using iterator_concept = std::random_access_iterator_tag;
#endif
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
    typedef std::random_access_iterator_tag iterator_category;

    LegacyRandomAccessIterator() {}

    LegacyRandomAccessIterator(const LegacyRandomAccessIterator& other)
    : m_iter(other.m_iter)
    {}

    LegacyRandomAccessIterator& operator=(const LegacyRandomAccessIterator& other)
    {
        if (this != &other)
        {
            //m_iter = other.m_iter;
            Iter::assignment(m_iter, other.m_iter);
        }
        return *this;
    }

    ~LegacyRandomAccessIterator() {}

    LegacyRandomAccessIterator& operator+=(difference_type n)
    {
        Iter::addition_assignment(m_iter, n);
        return *this;
    }

    LegacyRandomAccessIterator& operator-=(difference_type n)
    {
        Iter::subtraction_assignment(m_iter, n);
        return *this;
    }

    pointer operator->()
    {
        //return m_iter;
        return Iter::member_access(m_iter);
    }

    reference operator[](difference_type n)
    {
        return Iter::subscript(m_iter, n);
    }

    reference operator[](difference_type n) const
    {
        return Iter::subscript(m_iter, n);
    }

    LegacyRandomAccessIterator(pointer ptr) : m_iter(ptr) {}

    LegacyRandomAccessIterator& operator=(const pointer ptr)
    {
        m_iter = ptr;
        return *this;
    }

    //int compare(const LegacyRandomAccessIterator& other)
    //{
    //    if (m_iter < other.m_iter)
    //    {
    //        return -1;
    //    }
    //    else if (m_iter == other.m_iter)
    //    {
    //        return 0;
    //    }
    //    else // if (m_iter > other.m_iter)
    //    {
    //        return 1;
    //    }
    //}

    difference_type difference(const LegacyRandomAccessIterator& other)
    {
        //return m_iter - other.m_iter;
        return Iter::subtraction(m_iter, other.m_iter);
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
inline bool operator==(const LegacyRandomAccessIterator<T>& lhs, const LegacyRandomAccessIterator<T>& rhs)
{
    //return lhs.compare(rhs) == 0;
    return lhs.difference(rhs) == 0;
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
