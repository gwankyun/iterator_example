#pragma once
#include "common.hpp"
#include "LegacyInputIterator.hpp"

template<typename Iter>
struct LegacyForwardIterator
    : public Indirection<LegacyForwardIterator<Iter>, Iter>
    , public Increment<LegacyForwardIterator<Iter>, Iter>
    , public MemberAccess<LegacyForwardIterator<Iter>, Iter>
    , public Assignment<LegacyForwardIterator<Iter>, Iter>
    , public Equality<LegacyInputIterator<Iter>, Iter>
{
#ifdef __cpp_lib_concepts
    using iterator_concept = std::forward_iterator_tag;
#endif

    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;

    typedef std::forward_iterator_tag iterator_category;

    LegacyForwardIterator() {}

    LegacyForwardIterator(const LegacyForwardIterator& other)
    : m_iter(other.m_iter)
    {}

    ~LegacyForwardIterator() {}

    LegacyForwardIterator(pointer ptr) : m_iter(ptr) {}

    LegacyForwardIterator& operator=(const pointer ptr)
    {
        m_iter = ptr;
        return *this;
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
inline bool operator==(
    const LegacyForwardIterator<T>& lhs,
    const LegacyForwardIterator<T>& rhs)
{
    return lhs == rhs;
}

template<typename T>
inline bool operator!=(
    const LegacyForwardIterator<T>& lhs,
    const LegacyForwardIterator<T>& rhs)
{
    return !(lhs == rhs);
}
